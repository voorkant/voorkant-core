#include <iostream>
#include <string>
#include <thread>
#include "Backend.hpp"
#include "HAEntity.hpp"
#include "logger.hpp"
#include "generated/domains.hpp"
#include "main.hpp"
#include <fnmatch.h>

using std::cerr;
using std::string;

HABackend::HABackend(){};

HABackend& HABackend::getInstance()
{
  static HABackend instance;
  return instance;
}

bool HABackend::connect(ConnectionDetails _conDetails)
{
  g_log << Logger::Debug << "[HABackend] Connecting to " << _conDetails.url << endl;

  wc = new WSConn(_conDetails.url);
  auto welcome = wc->recv();
  auto jwelcome = json::parse(welcome);

  json auth;
  auth["type"] = "auth";
  auth["access_token"] = _conDetails.token;
  wc->send(auth);
  json authresponse = json::parse(wc->recv());
  if (authresponse["type"] != "auth_ok") {
    g_log << Logger::Error << "Authentication failed, please check your HA_API_TOKEN" << endl;
    return false;
  }

  hasConnectCalled = true;
  return true;
};

bool HABackend::start()
{
  if (!hasConnectCalled) {
    // Should this be std::runtime_error?
    g_log << Logger::Error << "Connect() needs to be called before start()" << endl;
    return false;
  }
  if (wc == nullptr) {
    g_log << Logger::Error << "We expect that you'd do a Connect() first." << endl;
    return false;
  }
  loaded = false;
  std::unique_lock<std::mutex> lck(load_lock);
  ha = std::thread(&HABackend::threadrunner, this);
  ha.detach();
  while (!loaded) {
    usleep(200);
    load_cv.wait(lck);
  };
  return true;
};

string HABackend::createLongToken(string _name)
{
  json tokenrequest;
  tokenrequest["type"] = "auth/long_lived_access_token";
  tokenrequest["client_name"] = _name;
  tokenrequest["lifespan"] = 365;

  wc->send(tokenrequest);

  // TODO: should probably using a ref to fill the response and use bool as return type
  //{"id":1,"type":"result","success":true, "result":"TOKEN_HERE"}
  string response = wc->recv();
  json jresponse = json::parse(response);
  if (jresponse["success"] == true) {
    return jresponse["result"];
  }
  cerr << "Failed to create token: " << response << endl;
  return "NO_TOKEN";
}

json HABackend::doCommand(const string& _command, const json& _data)
{
  json request;
  request = _data;
  request["type"] = _command;
  wc->send(request);
  auto response = wc->recv();

  json jsonresponse = json::parse(response);
  if (jsonresponse["id"] != request["id"]) {
    throw std::runtime_error("Send out a command, but received something with a different ID.");
  }
  return jsonresponse;
}

void HABackend::threadrunner()
{
  json getdomains;
  getdomains["type"] = "get_services";
  wc->send(getdomains);

  auto msg = wc->recv();
  json getdomainjson = json::parse(msg);
  if (getdomainjson["id"] != getdomains["id"]) {
    throw std::runtime_error("Didn't receive response to getDomains while we expected it");
  }
  for (auto& [domain, services] : getdomainjson["result"].items()) {

    std::scoped_lock lk(domainslock);
    domains[domain] = std::make_shared<HADomain>(domain, services);
  }

  json subscribe;
  subscribe["type"] = "subscribe_events";
  wc->send(subscribe);

  json getstates;
  getstates["type"] = "get_states";
  wc->send(getstates);

  while (true) {
    auto msg = wc->recv();

    // cout<<msg<<endl;
    json j = json::parse(msg);

    {

      if (j["id"] == getstates["id"]) {
        std::scoped_lock lk(entitieslock);
        // response for initial getstates call
        for (auto evd : j["result"]) {
          auto entity_id = evd["entity_id"].get<std::string>();
          // FIXME: boost::split might be nice here, check if its header only?
          auto pos = entity_id.find(".");
          if (pos == std::string::npos) {
            throw std::runtime_error("entity ID [" + entity_id + "] contains no period, has no domain?");
          }

          auto domain = entity_id.substr(0, pos);

          // FIXME: we should check if the domain actually exists before just calling for it.
          entities[entity_id] = std::make_shared<HAEntity>(evd, domains[domain], this); // FIXME: we share `this` entirely unprotected from threading mistakes here
        }
        std::unique_lock<std::mutex> lck(load_lock);
        loaded = true;
        load_cv.notify_all();
      }
      else if (j["type"] == "event") {
        std::scoped_lock lk(entitieslock);
        //  something happened!
        auto event = j["event"];
        auto event_type = event["event_type"];
        auto evd = event["data"];
        auto entity_id = evd["entity_id"];
        auto new_state = evd["new_state"];

        if (event_type == "state_changed") {
          if (entities.count(entity_id) == 1) {
            auto ent = entities[entity_id];
            ent->update(new_state);
          }
          else {
            std::cerr << "Ignoring state change from " << entity_id << ". We have not received initial state yet." << std::endl;
          }
        }
        else {
          cerr << "Event type received that we didn't expect: " << event_type << endl;
        }
      }
      else {
        cerr << "Received message we don't expect: " << j["type"] << endl;
        cerr << j.dump(2) << endl;
        continue;
      }
    }
  }
}

map<string, std::shared_ptr<HAEntity>> HABackend::getEntities()
{
  return entities;
}

std::vector<std::shared_ptr<HAEntity>> HABackend::getEntitiesByDomain(const std::string& _domain)
{
  std::scoped_lock lk(entitieslock);
  std::vector<std::shared_ptr<HAEntity>> ret;
  for (auto& [id, entity] : entities) {
    if (entity->domain == _domain) {
      ret.push_back(entity);
    }
  }
  return ret;
}

std::vector<std::shared_ptr<HAEntity>> HABackend::getEntitiesByPattern(const std::string& _pattern)
{
  std::scoped_lock lk(entitieslock);
  std::vector<std::shared_ptr<HAEntity>> ret;
  for (auto& [id, entity] : entities) {
    if (fnmatch(_pattern.c_str(), entity->fullname.c_str(), FNM_CASEFOLD) == 0) {
      ret.push_back(entity);
    }
  }
  return ret;
}

std::shared_ptr<HAEntity> HABackend::getEntityByName(const std::string& _name)
{
  std::scoped_lock lk(entitieslock);

  return entities.at(_name);
}

json HABackend::getDashboardConfig(const std::string& _dashboard)
{
  json url;
  url["url_path"] = _dashboard;
  json dashboard_config = doCommand("lovelace/config", url);
  g_log << Logger::Debug << "Output:" << std::endl;
  g_log << Logger::Debug << dashboard_config.dump(2) << std::endl;
  return dashboard_config;
}

void HABackend::wsConnSend(json& _msg)
{
  wc->send(_msg);
}

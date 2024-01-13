#include <iostream>
#include <string>
#include <thread>
#include "Backend.hpp"
#include "HAEntity.hpp"
#include "main.hpp"

using std::cerr;
using std::cout;
using std::endl;
using std::string;
using std::thread;

HABackend::HABackend(){};

bool HABackend::Connect(string url, string token)
{
  cerr << "[HABackend] Connecting to " << url << endl;

  wc = new WSConn(url);
  auto welcome = wc->recv();
  auto jwelcome = json::parse(welcome);

  json auth;
  auth["type"] = "auth";
  auth["access_token"] = token;
  wc->send(auth);
  json authresponse = json::parse(wc->recv());
  if (authresponse["type"] != "auth_ok") {
    cerr << "Authentication failed, please check your HA_API_TOKEN" << endl;
    return false;
  }

  return true;
};

bool HABackend::Start()
{
  if (wc == nullptr) {
    cerr << "We expect that you'd do a Connect() first." << endl;
    return false;
  }
  loaded = false;
  std::unique_lock<std::mutex> lck(load_lock);
  ha = std::thread(&HABackend::threadrunner, this);
  ha.detach();
  cerr << "GOING TO WAIT" << endl;
  while (!loaded) {
    load_cv.wait(lck);
    usleep(200);
    cerr << "THIS IS BORING" << endl;
  };
  cerr << "START COMPLETED" << endl;
  return true;
};

string HABackend::CreateLongToken(string name)
{
  json tokenrequest;
  tokenrequest["type"] = "auth/long_lived_access_token";
  tokenrequest["client_name"] = name;
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
    cerr << "Adding domain: " << domain << endl;
    domains[domain] = std::make_shared<HADomain>(domain, services);
  }
  cerr << "We have " << domains.size() << "domains " << endl;

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

    std::vector<std::string> whatchanged;
    {

      if (j["id"] == getstates["id"]) {
        std::scoped_lock lk(stateslock);
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
          states[entity_id] = std::make_shared<HAEntity>(evd, domains[domain]);
          whatchanged.push_back(entity_id);
        }
        std::unique_lock<std::mutex> lck(load_lock);
        loaded = true;
        load_cv.notify_all();
      }
      else if (j["type"] == "event") {
        // std::scoped_lock lk(stateslock);
        //  something happened!
        auto event = j["event"];
        auto event_type = event["event_type"];
        auto evd = event["data"];
        auto entity_id = evd["entity_id"];
        auto old_state = evd["old_state"];
        auto new_state = evd["new_state"];

        if (event_type == "state_changed") {
          // states[entity_id]->update(new_state);
          whatchanged.push_back(entity_id);
        }
        else {
          cerr << "Event type received that we didn't expect: " << event_type << endl;
        }
      }
      else {
        cerr << "Received message we don't expect: " << j["type"] << endl;
        // not a message we were expecting
        continue;
      }
    }
    // cerr<<"\033[2Jhave "<<states.size()<< " states" << endl;
    // cerr<<"selected = "<<selected<<endl;
    // cerr<<endl;
    // for (auto &[k,v] : states) {
    //   cout<<k<<"="<<v->getState()<<endl;
    // }
    {
      std::scoped_lock lk(entrieslock);
      entries.clear();

      for (auto& [k, v] : states) {
        entries.push_back(k); // +":"+v->getState());
      }
    }

    uithread_refresh(this, whatchanged);
  }
}

std::vector<std::string> HABackend::GetEntries()
{
  std::scoped_lock lk(entrieslock);
  return entries;
}

std::shared_ptr<HAEntity> HABackend::GetState(const std::string& name)
{
  std::scoped_lock lk(stateslock);

  return states.at(name);
}

std::vector<HAService> HABackend::GetServicesForDomain(const string& domain)
{
  std::scoped_lock lk(domainslock);

  if (domains.count(domain)) {
    return domains[domain]->getServices();
  }

  throw std::runtime_error("Couldn't retrieve services for domain " + domain + " as domain does not exist");
}

void HABackend::WSConnSend(json& msg)
{
  wc->send(msg);
}

#pragma once

#include <string>
#include <mutex>

#include <poll.h>

#include <curl/curl.h>
#include <curl/easy.h>

#include <nlohmann/json.hpp>

using json = nlohmann::json;

std::string GetEnv(std::string key);
// void backToFrontPing();

class WSConn
{
public:
  WSConn(std::string url);
  ~WSConn() {
        // FIXME clean up here
  }

  std::string recv(void);
  void send(json& msg);

  std::mutex wshandlelock;
  CURL* wshandle;

  std::mutex msgidlock;
  int msgid = 0;

private:
  // call with wshandlelock held
  void send(std::string& msg);
};

class HAEntity
{
public:
  HAEntity(void) {

  }
  HAEntity(json _state) {
    state = _state;
  }
  ~HAEntity() {

  }

  void update(json _state) {
    state = _state;
  }

  std::string toString(void) {
    return state.dump(2);
  }

  std::vector<std::string> attrVector(void) {
    std::vector<std::string> ret;


    for (const auto &[k, v] : state["attributes"].items()) {
      ret.push_back(k+std::string(": ")+v.dump());
    }

    return ret;
  }

  std::string getState(void) {
    return state["state"];
  }

  std::string getInfo(void) {
    std::ostringstream ret;

    ret<<"state="<<getState()<<"  ";
    ret<<"domain="<<getDomain()<<"  ";
    // ret<<""
    return ret.str();
  }

  std::string getDomain(void) {
    auto id = state["entity_id"].get<std::string>();

    // FIXME: boost::split might be nice here, check if its header only?
    auto pos = id.find(".");

    if (pos == std::string::npos) {
      throw std::runtime_error("entity ID ["+id+"] contains no period, has no domain?");
    }

    return id.substr(0, pos);
  }
private:
  json state;
};

class HADomain
{
public:
  HADomain(void) {

  }
  HADomain(json _state) {
    state = _state;
  }
  ~HADomain() {

  }

  void update(json _state) {
    state = _state;
  }

  std::string toString(void) {
    return state.dump(2);
  }

  std::string getState(void) {
    return state["state"];
  }

  std::vector<std::string> getServices(void) {
    std::vector<std::string> ret;

    // cerr<<state.dump()<<endl;
    for (auto &[service,info] : state.items()) {
      ret.push_back(service);
    }

    return ret;
  }

private:
  json state;
};

extern void uithread_refresh(); // FIXME: I think the UI should be an object on which this is just a method?

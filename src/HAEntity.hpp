
#ifndef HAENTITY_HPP
#define HAENTITY_HPP


#include <nlohmann/json.hpp>

using std::string;
using std::map;

using json = nlohmann::json;


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

  json getJsonState(void) {
    return state;
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


#endif
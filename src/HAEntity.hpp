
#ifndef HAENTITY_HPP
#define HAENTITY_HPP

#include <nlohmann/json.hpp>
#include <iostream>
#include <string>
#include <sstream>
#include "ext/magic_enum/include/magic_enum/magic_enum_all.hpp"

using std::map;
using std::string;

using json = nlohmann::json;

// TODO: we need to generate this to keep this in sync with HA.
enum class EntityType
{
  Light,
  Switch,
  Climate,
  OTHER,
};

class HAEntity
{
public:
  string name;
  EntityType domain;
  string id;
  HAEntity(void); // do we need this?
  HAEntity(json _state);
  ~HAEntity(){};
  void update(json _state);
  std::string toString(void);

  std::vector<std::string> attrVector(void)
  {
    std::vector<std::string> ret;

    for (const auto& [k, v] : state["attributes"].items()) {
      ret.push_back(k + std::string(": ") + v.dump());
    }

    return ret;
  }

  std::string getState(void)
  {
    return state["state"];
  }

  json getJsonState(void)
  {
    return state;
  }

  std::string getInfo(void)
  {
    std::ostringstream ret;

    ret << "state=" << getState() << "  ";
    ret << "domain=" << magic_enum::enum_name(this->domain) << "  ";
    // ret<<""
    return ret.str();
  }

private:
  EntityType getDomainFromState();
  std::string getNameFromState();
  json state;
};

class HAService
{
public:
  string description;
  string name;
  string systemname;
  HAService(json _service);
  ~HAService(){};
};

class HADomain
{
public:
  HADomain(void);
  HADomain(json _state);
  ~HADomain(){};

  void update(json _state);
  std::string toString(void);
  std::vector<std::string> getServices(void);

private:
  std::vector<std::shared_ptr<HAService>> _services;
  json state;
};

#endif
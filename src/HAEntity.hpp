
#ifndef HAENTITY_HPP
#define HAENTITY_HPP

#include <nlohmann/json.hpp>
#include <iostream>
#include <string>
#include <sstream>
#include <set>
#include "ext/magic_enum/include/magic_enum/magic_enum_all.hpp"
#include "Observer.hpp"

using std::map;
using std::string;

using json = nlohmann::json;

// TODO: we need to generate this to keep this in sync with HA.
enum class EntityType
{
  Light,
  Switch,
  Fan,
  Camera,
  OTHER,
};

class HAService
{
public:
  string description;
  string name;
  HAService(json _service);
  ~HAService(){};
};

class HADomain
{
public:
  std::string name;
  HADomain(void);
  HADomain(std::string _name, json _state);
  ~HADomain(){};

  std::string toString(void);
  std::vector<std::shared_ptr<HAService>> services;

private:
  json state;
};

class HABackend; // so we can have a pointer to it

class HAEntity : public ISubject
{
public:
  string name;
  string domain;
  string fullname;
  string id;

  // HAEntity(json _state);
  HAEntity(json _state, std::shared_ptr<HADomain> _hadomain, HABackend* _backend);
  ~HAEntity(){};
  std::vector<std::shared_ptr<HAService>> getServices();
  void update(json _state); // FIXME: we're assuming that the domain stays the same.
  std::string toString(void);
  EntityType getEntityType(void);

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
    ret << "domain=" << domain << "  ";
    ret << "entitytype=" << magic_enum::enum_name(getEntityType());
    // ret<<""
    return ret.str();
  }

  void wsConnSend(json& _msg); // FIXME: this is a hack because HADomains::Light cannot get to the backend easily

  void attach(IObserver* _uientity) override;
  void detach(IObserver* _uientity) override;
  void notify() override;

protected:
  HABackend* backend;

private:
  std::set<IObserver*> observers;
  std::shared_ptr<HADomain> hadomain;
  std::string getDomainFromState();
  std::string getNameFromState();
  json state;
};

#endif
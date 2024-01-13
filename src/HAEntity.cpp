
#include "HAEntity.hpp"

using std::cerr;
using std::endl;

HAEntity::HAEntity(json _state)
{
  HAEntity(_state, nullptr);
}

HAEntity::HAEntity(json _state, std::shared_ptr<HADomain> _hadomain)
{
  state = _state;

  id = state["entity_id"];
  name = this->getNameFromState();
  domain = this->getDomainFromState();
  hadomain = _hadomain;
}

void HAEntity::update(json _state)
{
  state = _state;
}

std::vector<std::shared_ptr<HAService>> HAEntity::getServices()
{
  std::vector<std::shared_ptr<HAService>> ret;
  if (hadomain != nullptr) {
    if (hadomain->services.size())
      for (auto& service : hadomain->services) {
        ret.push_back(service);
      }
  }

  return ret;
}

std::string HAEntity::toString(void)
{
  return state.dump(2);
}

EntityType HAEntity::getEntityType(void)
{
  return magic_enum::enum_cast<EntityType>(domain, magic_enum::case_insensitive).value_or(EntityType::OTHER);
}

std::string HAEntity::getDomainFromState(void)
{
  auto id = state["entity_id"].get<std::string>();

  // FIXME: boost::split might be nice here, check if its header only?
  auto pos = id.find(".");

  if (pos == std::string::npos) {
    throw std::runtime_error("entity ID [" + id + "] contains no period, has no domain?");
  }

  return id.substr(0, pos);
}

std::string HAEntity::getNameFromState(void)
{
  if (state.contains("attributes") && state["attributes"].contains("friendly_name")) {
    return state["attributes"]["friendly_name"];
  }
  else {
    return "UNKNOWN_" + state["entity_id"].get<string>();
  }
}

HADomain::HADomain(std::string _name, json _state)
{
  state = _state;
  name = _name;
  for (auto& [service, info] : state.items()) {
    auto haservice = std::make_shared<HAService>(info);
    services.push_back(haservice);
  }
}

std::string HADomain::toString(void)
{
  return state.dump(2);
}

HAService::HAService(json _service)
{
  if (_service.contains("name")) {
    this->name = _service["name"].get<string>();
  }

  if (_service.contains("description")) {
    this->description = _service["description"].get<string>();
  }
}
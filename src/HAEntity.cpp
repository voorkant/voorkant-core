
#include "HAEntity.hpp"
#include "magic_enum_all.hpp"

using std::cerr;
using std::endl;

HAEntity::HAEntity(json _state)
{
  state = _state;

  id = state["entity_id"];
  name = this->getNameFromState();
  domain = this->getDomainFromState();
}

void HAEntity::update(json _state)
{
  state = _state;
}

std::string HAEntity::toString(void)
{
  return state.dump(2);
}

EntityType HAEntity::getDomainFromState(void)
{
  auto id = state["entity_id"].get<std::string>();

  // FIXME: boost::split might be nice here, check if its header only?
  auto pos = id.find(".");

  if (pos == std::string::npos) {
    throw std::runtime_error("entity ID [" + id + "] contains no period, has no domain?");
  }

  string domain = id.substr(0, pos);
  auto domainEnum = magic_enum::enum_cast<EntityType>(domain);
  if (domainEnum.has_value()) {
    return domainEnum.value();
  }
  return EntityType::OTHER;
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

HADomain::HADomain(json _state)
{
  state = _state;
}

void HADomain::update(json _state)
{
  state = _state;
}

std::string HADomain::toString(void)
{
  return state.dump(2);
}
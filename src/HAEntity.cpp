
#include "HAEntity.hpp"
using std::cerr;
using std::endl;

HAEntity::HAEntity(json _state)
{
    cerr << _state.dump();

    state = _state;

    id = state["entity_id"];
    if (state.contains("attributes") && state["attributes"].contains("friendly_name"))
    {
        name = state["attributes"]["friendly_name"];
    }
    else
    {
        name = state["entity_id"];
    }
    //   name = state["attributes"]["friendly_name"];
}

void HAEntity::update(json _state)
{
    state = _state;
}

std::string HAEntity::toString(void)
{
    return state.dump(2);
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
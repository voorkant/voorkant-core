#include "HAEntity.hpp"

HAEntity::HAEntity(json _state)
{
    state = _state;
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
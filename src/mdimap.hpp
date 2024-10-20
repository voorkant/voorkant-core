#pragma once

#include <cstdint> // FIXME: this works around a bug in frozen? (likely fixed in 1.2.0, we're using 1.1.1 here)

#include <frozen/unordered_map.h>
#include <frozen/string.h>

namespace voorkant
{
namespace mdi
{
  extern const frozen::unordered_map<frozen::string, frozen::string, 4> name2id;
}
}
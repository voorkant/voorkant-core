#pragma once

#include <cstdint> // FIXME: this works around a bug in frozen?

#include <frozen/unordered_map.h>
#include <frozen/string.h>

namespace voorkant {
namespace mdi{
extern const frozen::unordered_map<frozen::string, frozen::string, 4> name2id;
}
}
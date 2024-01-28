#pragma once

#include <string>
#include <mutex>

#include <poll.h>

#include <nlohmann/json.hpp>
#include "Backend.hpp"
#include "WSConn.hpp"

using std::string;

using json = nlohmann::json;

std::string GetEnv(std::string key);

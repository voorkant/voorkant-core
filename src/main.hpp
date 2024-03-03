#pragma once

#include <string>
#include <mutex>

#include <poll.h>
// NOLINTBEGIN(clang-diagnostic-error])
#include <curl/curl.h>
#include <curl/easy.h>
// NOLINTEND(clang-diagnostic-error])

#include <nlohmann/json.hpp>
#include "Backend.hpp"
#include "WSConn.hpp"

using std::string;

using json = nlohmann::json;

std::string getEnv(std::string _key);

#pragma once

#include <string>
#include <mutex>

#include <poll.h>

#include <curl/curl.h>
#include <curl/easy.h>

#include <nlohmann/json.hpp>
#include "Backend.hpp"
#include "WSConn.hpp"

using std::string;

using json = nlohmann::json;

std::string getEnv(std::string _key);

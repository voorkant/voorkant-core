#pragma once

#include <string>
#include <mutex>

#include <poll.h>

#include <curl/curl.h>
#include <curl/easy.h>

#include <nlohmann/json.hpp>
#include "WSConn.hpp"

using std::string;
using std::map;

using json = nlohmann::json;

std::string GetEnv(std::string key);
// void backToFrontPing();



//extern void uithread(WSConn& wc, int argc=0, char* argv[] = nullptr);

//extern void uithread_refresh(std::vector<std::string> whatchanged); // FIXME: I think the UI should be an object on which this is just a method?


///extern std::vector<std::string> getServicesForDomain(std::string domain); // REMOVE

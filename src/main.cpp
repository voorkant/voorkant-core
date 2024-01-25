#include <algorithm>
#include <exception>
#include <iostream>
#include <stdexcept>
#include <string>
#include <thread>
#include <unistd.h>

#include "main.hpp"
#include "WSConn.hpp"
#include "Backend.hpp"
#include "HAEntity.hpp"

#include "logger.hpp"

using std::cerr;
using std::endl;
using std::string;

extern void uithread(HABackend& backend, int /* argc */, char*[] /* argv[] */);

std::string GetEnv(std::string key)
{
  auto value = getenv(key.c_str());

  if (value == nullptr) {
    throw std::runtime_error("environment variable " + key + " not set, exiting");
  }

  return value;
}

int main(int argc, char* argv[])
{
  HABackend backend;
  g_log.setLogLevel(Logger::LogLevel::Debug);
  g_log.setDoDetails(true);
  g_log << Logger::LogLevel::Info << "Starting!" << std::endl;
  if (backend.Connect(GetEnv("HA_WS_URL"), GetEnv("HA_API_TOKEN"))) {
    g_log << Logger::LogLevel::Debug << "Connected to HA succesfully!" << std::endl;
    // we used to do this, which actually is quite pointless if main does nothing besides this (after connecting HA)
    //    std::thread ui(uithread, std::ref(backend), argc, argv);
    //    ui.join();

    // running the uithread in the main thread makes LVGL/SDL work on macOS
    uithread(backend, argc, argv);
    return 0;
  }

  return 1;
}

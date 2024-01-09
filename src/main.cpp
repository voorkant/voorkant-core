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
  if (backend.Connect(GetEnv("HA_WS_URL"), GetEnv("HA_API_TOKEN"))) {
    cerr << "Connect succesful. Starting." << endl;
    std::thread ui(uithread, std::ref(backend), argc, argv);
    ui.join();
  }
}

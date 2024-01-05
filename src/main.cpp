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
using std::cout;
using std::endl;
using std::string;

// static const uint32_t ID_SUBSCRIPTION = 1;
// static const uint32_t ID_GETSTATES = 2;
// static const uint32_t ID_START = 100;

std::string GetEnv(std::string key)
{
  auto value = getenv(key.c_str());

  if (value == nullptr)
  {
    throw std::runtime_error("environment variable " + key + " not set, exiting");
  }

  return value;
}

int main(int argc, char *argv[])
{
  string HA_URL = GetEnv("HA_WS_URL");
  cout << "Using " << HA_URL << endl;
  auto wc = WSConn(HA_URL);

  HABackend backend;
  if (backend.Connect(HA_URL, GetEnv("HA_API_TOKEN")))
  {
    cout<<"Connect succesful. Starting."<<endl;
    string token = backend.CreateLongToken("ruben");
    cout<<"Received long lived token:" <<token<<endl;
  }

  // Wait for backend to end?


  // these two really want a reference to eachother, instead of a shared ref to wc
  // python threading object would be nice here
  // std::thread ui(uithread, std::ref(wc), argc, argv);
  // std::thread ha(hathread, std::ref(wc));

  // ha.detach();
  // ui.join();
}

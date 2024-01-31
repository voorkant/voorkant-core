#ifndef WSCONN_HPP
#define WSCONN_HPP

#include <string>
#include <mutex>
#include <poll.h>
// NOLINTBEGIN
#include <curl/curl.h> // NOLINT(clang-diagnostic-error)
#include <curl/easy.h> // NOLINT(clang-diagnostic-error)
// NOLINTEND
#include <nlohmann/json.hpp>

using json = nlohmann::json;

class WSConn
{
public:
  WSConn(std::string url);
  ~WSConn()
  {
    // FIXME clean up here
  }

  std::string recv(void);
  void send(json& msg);

private:
  // call with wshandlelock held
  void sendString(std::string& msg);

  std::mutex wshandlelock;
  CURL* wshandle;

  std::mutex msgidlock;
  int msgid = 0;
};
#endif
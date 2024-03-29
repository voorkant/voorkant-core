#ifndef WSCONN_HPP
#define WSCONN_HPP

#include <string>
#include <mutex>
#include <poll.h>
#include <curl/curl.h>
#include <curl/easy.h>
#include <nlohmann/json.hpp>

using json = nlohmann::json;

class WSConn
{
public:
  WSConn(std::string _url);
  ~WSConn()
  {
    // FIXME clean up here
  }

  std::string recv(void);
  void send(json& _msg);

private:
  // call with wshandlelock held
  void sendString(std::string& _msg);

  std::mutex wshandlelock;
  CURL* wshandle;

  std::mutex msgidlock;
  int msgid = 0;
};

#endif
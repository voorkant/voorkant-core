#ifndef WSCONN_HPP
#define WSCONN_HPP

#include <condition_variable>
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

  std::string recv(void); // FIXME: refactor this to return json?
  void send(json& _msg);
  json sendAndWait(json& _msg);

  bool hasWaiter(int _id);
  void submitToWaiter(json& _msg);

private:
  // call with wshandlelock held
  void sendString(std::string& _msg);

  std::mutex wshandlelock;
  CURL* wshandle;

  std::mutex msgidlock;
  int msgid = 0;

  class Waiter
  {
  public:
    std::condition_variable cv;
    bool ready{false};
    std::mutex mutex;
    json response;

    void wait()
    {
      std::unique_lock lk(mutex);
      cv.wait(lk, [this] { return ready; });
    }

    void notify()
    {
      cv.notify_one();
    }
  };

  std::map<int, Waiter> waiters; // FIXME: I bet this map wants to be protected by a mutex
};

#endif
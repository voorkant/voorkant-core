
#include "WSConn.hpp"
#include "src/logger.hpp"
#include <csignal>
#include <iostream>
#include <stdexcept>

using std::cout;
using std::endl;

WSConn::WSConn(std::string _url)
{
  curl_global_init(CURL_GLOBAL_ALL);

  wshandle = curl_easy_init();

  curl_easy_setopt(wshandle, CURLOPT_CONNECT_ONLY, 2L);
  curl_easy_setopt(wshandle, CURLOPT_URL, _url.c_str());
  curl_easy_setopt(wshandle, CURLOPT_VERBOSE, 1L);
  auto res = curl_easy_perform(wshandle);
  if (res != CURLE_OK) {
    throw std::runtime_error(std::string("websocket connection failed: ") + curl_easy_strerror(res));
  }
}

std::string WSConn::recv(void)
{
  size_t recv;
  const struct curl_ws_frame* meta;
  struct pollfd pfd;

  char buffer[8192];

  std::string result;

  pfd.events = POLLIN;
  /* cerr<< */ curl_easy_getinfo(wshandle, CURLINFO_ACTIVESOCKET,
                                 &pfd.fd) /* <<endl */;

  CURLcode ret;

  // FIXME: handle frames > 64k
  while (true) {
    {
      std::scoped_lock lk(wshandlelock);
      ret = curl_ws_recv(wshandle, buffer, sizeof(buffer), &recv, &meta);
    }
    // cerr<<"CURLE_AGAIN"<<endl;
    // cerr<<"recv ret="<<ret<<endl;
    if (ret == CURLE_OK) {
      std::string chunk(buffer, recv); // FIXME: string_view?
      result = result + chunk;
      // cerr<<"bytesleft="<<(meta->bytesleft)<<endl;
      // cerr<<"result.size()="<<result.size()<<endl;
      if (meta->bytesleft == 0) {
        break;
      }
    }
    else if (ret == CURLE_AGAIN) {
      poll(&pfd, 1, 1000);
    }
    else {
      throw std::runtime_error(
        "got error from curl_ws_recv: " + std::string(curl_easy_strerror(ret))); // FIXME: does not hold wshandlelock, might even print the
                                                                                 // wrong error in theory
                                                                                 // confirmed: we end up in this code block if we kill HA.
    }
  }
  // cerr<<"ret="<<ret<<endl;
  // cerr<<"buffer="<<buffer<<endl;
  // cerr<<"recv="<<recv<<endl;
  // cout<<"RESULT:"<<endl;
  // cout<<result<<endl;
  // cout<<"END RESULT"<<endl;

  if (meta->flags & CURLWS_CLOSE) {
    uint16_t reason = 0;

    if (result.size() >= 2) {
      reason = ((unsigned char)result[0] << 8) + (unsigned char)result[1];
    }
    g_log << Logger::LogLevel::Error << "got CURL_WS_CLOSE, reason=" << reason << endl;
    throw std::runtime_error("HA websocket disconnected");
  }

  return result;
}

void WSConn::send(json& _msg)
{
  {
    std::scoped_lock lk(msgidlock);

    if (msgid) {
      // FIXME: at zero, we are authing, which does not get an id. this is a hack.
      _msg["id"] = msgid;
    }
    std::cerr << "WSConn::send: " << _msg.dump() << endl;

    msgid++;
  }

  auto jmsg = _msg.dump();
  sendString(jmsg);
}

// FIXME: reduce code duplication versus ::send, or maybe make waiting a bool arg?
json WSConn::sendAndWait(json& _msg)
{
  auto id = msgid;
  {
    std::scoped_lock lk(msgidlock);

    if (id) {
      // FIXME: at zero, we are authing, which does not get an id. this is a hack.
      _msg["id"] = id;
    }
    std::cerr << "WSConn::send: " << _msg.dump() << endl;

    msgid++;
  }

  auto jmsg = _msg.dump();

  waiters[id]; // create the waiter
  sendString(jmsg);
  waiters[id].wait();

  auto resp = waiters[id].response;
  waiters.erase(id);

  return resp;
}

void WSConn::sendString(std::string& _msg)
{
  std::scoped_lock lk(wshandlelock);
  size_t sent;
  curl_ws_send(wshandle, _msg.c_str(), _msg.length(), &sent, 0, CURLWS_TEXT);
}

bool WSConn::hasWaiter(int _id)
{
  return waiters.count(_id) > 0;
}

void WSConn::submitToWaiter(json& _msg)
{
  int id = _msg["id"];

  waiters[id].response = _msg;
  waiters[id].ready = true;
  waiters[id].notify();
}

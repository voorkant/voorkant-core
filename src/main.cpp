#include <algorithm>
#include <exception>
#include <iostream>
#include <stdexcept>
#include <string>
#include <thread>
#include <unistd.h>

#include "main.hpp"

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

  if (value == nullptr) {
    throw std::runtime_error("environment variable "+key+" not set, exiting");
  }

  return value;
}

WSConn::WSConn(std::string url) {
    curl_global_init(CURL_GLOBAL_ALL);

    wshandle = curl_easy_init();

    curl_easy_setopt(wshandle, CURLOPT_CONNECT_ONLY, 2L);
    curl_easy_setopt(wshandle, CURLOPT_URL, url.c_str());
    curl_easy_perform(wshandle);
}

std::string WSConn::recv(void) {
  size_t recv;
  struct curl_ws_frame *meta;
  struct pollfd pfd;

  char buffer[8192];

  std::string result;

  pfd.events = POLLIN;
      /* cerr<< */ curl_easy_getinfo(wshandle, CURLINFO_ACTIVESOCKET, &pfd.fd) /* <<endl */ ;

  CURLcode ret;

      // FIXME: handle frames > 64k
  while(true) {
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
      throw std::runtime_error("got error from curl_ws_recv: "+std::string(curl_easy_strerror(ret))); // FIXME: does not hold wshandlelock, might even print the wrong error in theory
    }
  }
      // cerr<<"ret="<<ret<<endl;
      // cerr<<"buffer="<<buffer<<endl;
      // cerr<<"recv="<<recv<<endl;
      // cout<<"RESULT:"<<endl;
      // cout<<result<<endl;
      // cout<<"END RESULT"<<endl;
  return result;
}

void WSConn::send(json& msg) {
  {
    std::scoped_lock lk(msgidlock);

    if (msgid) {
      // FIXME: at zero, we are authing, which does not get an id. this is a hack.
      msg["id"]=msgid;
    }

    msgid++;
  }

  auto jmsg = msg.dump();

  send(jmsg);
}

  std::mutex wshandlelock;
  CURL* wshandle;

  std::mutex msgidlock;
  int msgid = 0;

  // call with wshandlelock held
void WSConn::send(std::string& msg) {
  std::scoped_lock lk(wshandlelock);
  size_t sent;
  // cerr<<"sending: "<<msg<<endl;
  curl_ws_send(wshandle, msg.c_str(), msg.length(), &sent, 0, CURLWS_TEXT);
}


int main(int argc, char* argv[])
{
  auto wc = WSConn(GetEnv("HA_WS_URL"));

  std::thread ui(uithread, std::ref(wc), argc, argv);
  std::thread ha(hathread, std::ref(wc));

  ha.detach();
  ui.join();
}


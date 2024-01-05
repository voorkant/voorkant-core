
#include "WSConn.hpp"
#include <iostream>

using std::cout;
using std::endl;
 

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
  sendString(jmsg);
}


  // call with wshandlelock held
void WSConn::sendString(std::string& msg) {
  std::scoped_lock lk(wshandlelock);
  size_t sent;
  curl_ws_send(wshandle, msg.c_str(), msg.length(), &sent, 0, CURLWS_TEXT);
}
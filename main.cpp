#include <iostream>
#include <unistd.h>
#include <poll.h>
#include <nlohmann/json.hpp>

#include <curl/curl.h>
#include "curl/easy.h"

using std::cerr;
using std::cout;
using std::endl;
using std::string;
using std::map;

using json = nlohmann::json;

static const uint32_t ID_SUBSCRIPTION = 1;

class HAEntity
{
public:
  HAEntity(void) {

  }
  HAEntity(json _state) {
    state = _state;
  }
  ~HAEntity() {

  }

  void update(json _state) {
    state = _state;
  }

  std::string toString(void) {
    return state.dump();
  }

  std::string getState(void) {
    return state["state"];
  }
private:
  json state;
};

class WSConn
{
public:
  WSConn(std::string url) {
    wshandle = curl_easy_init();

    curl_easy_setopt(wshandle, CURLOPT_CONNECT_ONLY, 2L);
    curl_easy_setopt(wshandle, CURLOPT_URL, url.c_str());
    curl_easy_perform(wshandle);
  }
  ~WSConn() {
        // FIXME clean up here
  }

  std::string recv(void) {
    size_t recv;
    struct curl_ws_frame *meta;
    struct pollfd pfd;

    pfd.events = POLLIN;
        /* cerr<< */ curl_easy_getinfo(wshandle, CURLINFO_ACTIVESOCKET, &pfd.fd) /* <<endl */ ;

    CURLcode ret;

        // FIXME: handle frames > 64k
    while((ret = curl_ws_recv(wshandle, buffer, sizeof(buffer), &recv, &meta)) == CURLE_AGAIN) {
          // cerr<<"CURLE_AGAIN"<<endl;
      poll(&pfd, 1, 1000);
    }
        // cerr<<ret<<endl;
        // cerr<<buffer<<endl;
    return std::string(buffer, recv);

  }

  void send(std::string& msg) {
    size_t sent;
    curl_ws_send(wshandle, msg.c_str(), msg.length(), &sent, 0, CURLWS_TEXT);
  }

  CURL* wshandle;
  char buffer[64000];
};

int main(void) // int /* argc */, char* /* argv[] */*)
{

  curl_global_init(CURL_GLOBAL_ALL);
  auto wc = WSConn(std::string(getenv("HA_WS_URL")));

  auto welcome = wc.recv();

  auto jwelcome = json::parse(welcome);

  cerr<<"got welcome: "<<welcome<<endl; // FIXME check that it is the expected auth_required message

  json auth;

  auth["type"] = "auth";
  auth["access_token"] = getenv("HA_API_TOKEN");

  cerr<<auth.dump()<<endl;

  auto jauth = auth.dump();
  cerr<<jauth<<endl;
  wc.send(jauth);

  cerr<<wc.recv()<<endl; // FIXME assert auth_ok

  json subscribe;

  subscribe["id"] = ID_SUBSCRIPTION;
  subscribe["type"] = "subscribe_events";

  auto jsubscribe = subscribe.dump();

  wc.send(jsubscribe);

  map<string, std::shared_ptr<HAEntity>> states;

  while (true) {
    auto msg = wc.recv();

    json j = json::parse(msg);

    if (j["id"] != ID_SUBSCRIPTION) {
      continue;
    }

    auto event = j["event"];
    auto event_type = event["event_type"];
    auto evd = event["data"];
    auto entity_id = evd["entity_id"];

    auto old_state = evd["old_state"];
    auto new_state = evd["new_state"];

    cout << "event_type=" << event_type << ", ";
    cout << "entity_id=" << entity_id << ", ";
    cout << "state=" << new_state["state"];
    cout << endl;

    if (event_type == "state_changed") {
      states[entity_id] = std::make_shared<HAEntity>(new_state);
    }

    cerr<<"\033[2Jhave "<<states.size()<< " states" << endl;
    cerr<<endl;
    for (auto &[k,v] : states) {
      cout<<k<<"="<<v->getState()<<endl;
    }
  }
  return 0;
}

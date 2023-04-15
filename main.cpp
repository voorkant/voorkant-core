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
        cerr<<curl_easy_getinfo(wshandle, CURLINFO_ACTIVESOCKET, &pfd.fd)<<endl;

        CURLcode ret;

        // FIXME: handle frames > 64k
        while((ret = curl_ws_recv(wshandle, buffer, sizeof(buffer), &recv, &meta)) == CURLE_AGAIN) {
          cerr<<"CURLE_AGAIN"<<endl;
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

int main(int /* argc */, char* /* argv[] */*)
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

    subscribe["id"] = 1;
    subscribe["type"] = "subscribe_events";

    auto jsubscribe = subscribe.dump();

    wc.send(jsubscribe);

    while(true) { cerr<<wc.recv()<<endl; }


#if 0
    mqtt::client cli(ADDRESS, CLIENT_ID);

    mqtt::callback cb;
    cli.set_callback(cb);

    cerr<<"starting"<<endl;

    auto connOpts = mqtt::connect_options_builder() 
        // .keep_alive_interval(20)
        .clean_session()
        .finalize();

    try {
        cli.connect(connOpts);

        cerr<<"connected"<<endl;
    }
    catch (const mqtt::persistence_exception& exc) {
        std::cerr << "Persistence Error: " << exc.what() << " ["
            << exc.get_reason_code() << "]" << std::endl;
        return 1;
    }
    catch (const mqtt::exception& exc) {
        std::cerr << "Error: " << exc.what() << " ["
            << exc.get_reason_code() << "]" << std::endl;
        return 1;
    }

    cli.subscribe({ '#' }, 1);

    map<string, std::shared_ptr<HAEntity>> states;

    while (true) {
        auto msg = cli.consume_message();

        if (msg) {
            json j = json::parse(msg->to_string());

            auto event_type = j["event_type"];
            auto ev = j["event_data"];
            auto entity_id = ev["entity_id"];

            auto old_state = ev["old_state"];
            auto new_state = ev["new_state"];

            cout << "event_type=" << event_type << ", ";
            cout << "entity_id=" << entity_id << ", ";
            cout << "state=" << new_state["state"];
            cout << endl;

            if (event_type == "state_changed") {
                states[entity_id] = std::make_shared<HAEntity>(new_state);
            }
        }

        cerr<<"\033[2Jhave "<<states.size()<< " states" << endl;
        cerr<<endl;
        for (auto &[k,v] : states) {
            cout<<k<<"="<<v->getState()<<endl;
        }
    }
#endif
    return 0;
}
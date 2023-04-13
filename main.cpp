#include <iostream>
#include <unistd.h>
#include <nlohmann/json.hpp>

#include <curl/curl.h>

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

int main(int argc, char* argv[])
{

    curl_global_init(CURL_GLOBAL_ALL);
    auto handle = curl_easy_init();

    auto wsurl = getenv("HA_WS_URL");

    cerr<<"wsurl="<<wsurl<<endl;

    cerr<<curl_easy_setopt(handle, CURLOPT_URL, wsurl)<<endl;
    cerr<<curl_easy_setopt(handle, CURLOPT_CONNECT_ONLY, 2L)<<endl;
    cerr<<curl_easy_perform(handle)<<endl ;

    char buffer[64000];
    size_t recv;
    struct curl_ws_frame *meta;

    cerr<<curl_ws_recv(handle, buffer, sizeof(buffer), &recv, &meta);
    cerr<<curl_ws_recv(handle, buffer, sizeof(buffer), &recv, &meta);
    cerr<<curl_ws_recv(handle, buffer, sizeof(buffer), &recv, &meta);
    sleep(5);
    cerr<<curl_ws_recv(handle, buffer, sizeof(buffer), &recv, &meta);
    cerr<<buffer<<endl;


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
#include <cstring>

#include <mqtt/client.h>
#include <mqtt/callback.h>
#include <mqtt/connect_options.h>

#include <nlohmann/json.hpp>

#define PAYLOAD1 "bar"
#define PAYLOAD2 "foo"
#define TOPIC "/bla"
#define QOS 1
#define ADDRESS "127.0.0.1"
#define CLIENT_ID "habbieclient"

using std::cerr;
using std::cout;
using std::endl;
using std::string;
using std::map;

using json = nlohmann::json;

int main(int argc, char* argv[])
{
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
        // // First use a message pointer.

        // mqtt::message_ptr pubmsg = mqtt::make_message(PAYLOAD1);
        // pubmsg->set_qos();
        // cli.publish(TOPIC, pubmsg);

        // Now try with itemized publish.

        // cli.publish(TOPIC, PAYLOAD2, strlen(PAYLOAD2)+1, 0, false);

        // Disconnect
        
        // cli.disconnect();
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

    map<string, json> states;

    while (true) {
        auto msg = cli.consume_message();

        if (msg) {
            json j = json::parse(msg->to_string());

            // cout << msg->get_topic() << ": " << j.dump(4) << endl;
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
                states[entity_id] = new_state;
            }

            // cout << "changed:" << endl;
            // auto d = json::diff(ev["old_state"], ev["new_state"]);
            // cout << d.dump(4) << endl;
        }

        cerr<<"\033[2Jhave "<<states.size()<< " states" << endl;
        cerr<<endl;
        for (auto &[k,v] : states) {
            cout<<k<<"="<<v["state"]<<endl;
        }
    }

    return 0;
}
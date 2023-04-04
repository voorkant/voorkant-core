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

using std::cout;
using std::endl;

using json = nlohmann::json;

int main(int argc, char* argv[])
{
    mqtt::client cli(ADDRESS, CLIENT_ID);

    mqtt::callback cb;
    cli.set_callback(cb);

    auto connOpts = mqtt::connect_options_builder() 
        // .keep_alive_interval(20)
        .clean_session()
        .finalize();

    try {
        cli.connect(connOpts);

        // // First use a message pointer.

        // mqtt::message_ptr pubmsg = mqtt::make_message(PAYLOAD1);
        // pubmsg->set_qos();
        // cli.publish(TOPIC, pubmsg);

        // Now try with itemized publish.

        cli.publish(TOPIC, PAYLOAD2, strlen(PAYLOAD2)+1, 0, false);

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

    while (true) {
    	auto msg = cli.consume_message();

    	if (msg) {
			cout << msg->get_topic() << ": " << msg->to_string() << endl;
    	}

    	json j = json::parse(msg->to_string());
        
    }

    return 0;
}
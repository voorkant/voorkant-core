

#include <iostream>
#include <string>
#include <thread>
#include "Backend.hpp"
#include "HAEntity.hpp"

using std::cerr;
using std::cout;
using std::endl;
using std::string;
using std::thread;

HABackend::HABackend(){};

bool HABackend::Connect(string url, string token)
{
    // This should connect the WSConn and do the auth
    wc = new WSConn(url);
    auto welcome = wc->recv();
    auto jwelcome = json::parse(welcome);

    json auth;
    auth["type"] = "auth";
    auth["access_token"] = token;
    wc->send(auth);
    json authresponse = json::parse(wc->recv());
    if (authresponse["type"] != "auth_ok")
    {
        cerr << "Authentication failed, please check your HA_API_TOKEN" << endl;
        return false;
    }

    return true;
};

bool HABackend::Start()
{
    if (wc == nullptr)
    {
        cerr << "Do a damned connect first" << endl;
        return false;
    }
    cerr<<"In start"<<endl;
    ha = std::thread(&HABackend::threadrunner, this);
    cerr<<"Thred started"<<endl;
    ha.join();
    return true;
};


string HABackend::CreateLongToken(string name) {
    json tokenrequest;
    tokenrequest["type"] = "auth/long_lived_access_token";
    tokenrequest["client_name"] = name;
    tokenrequest["lifespan"] = 365;

    wc->send(tokenrequest);

    // TODO: should probably using a ref to fill the response and use bool as return type
    //{"id":1,"type":"result","success":true, "result":"TOKEN_HERE"}
    string response = wc->recv();
    json jresponse = json::parse(response);
    if (jresponse["success"] == true) {
        return jresponse["result"];
    }
    cerr<<"Failed to create token: "<<response<<endl;
    return "NO_TOKEN";

}

void HABackend::threadrunner()
{
    json subscribe;
    subscribe["type"] = "subscribe_events";
    wc->send(subscribe);

    json getstates;
    getstates["type"] = "get_states";
    wc->send(getstates);

    json getdomains;
    getdomains["type"] = "get_services";
    wc->send(getdomains);

    /* example ID_SUBSCRIPTION message:
    {
      "id": 1,
      "type": "event",
      "event": {
        "event_type": "state_changed",
        "data": {
          "entity_id": "sensor.shellyplug_s_bc6aa8_power",
          "old_state": {
    ...
          },
          "new_state": {
            "entity_id": "sensor.shellyplug_s_bc6aa8_power",
            "state": "9.89",
    ...
     */

    /* example ID_GETSTATES message:
    {
      "id": 2,
      "type": "result",
      "success": true,
      "result": [
        {
          "entity_id": "light.plafondlamp_kantoor_peter_level_light_color_on_off",
          "state": "on",
          "attributes": {
            "min_color_temp_kelvin": 2000,
            "max_color_temp_kelvin": 6535,

    */

    while (true)
    {
        auto msg = wc->recv();

        // cout<<msg<<endl;
        json j = json::parse(msg);

        std::vector<std::string> whatchanged;
        {
            std::scoped_lock lk(stateslock);
            if (j["id"] == getstates["id"])
            {
                // response for initial getstates call
                for (auto evd : j["result"])
                {
                    // cerr<<evd.dump()<<endl;
                    auto entity_id = evd["entity_id"];
                    states[entity_id] = std::make_shared<HAEntity>(evd);
                    whatchanged.push_back(entity_id);
                }
                // exit(1);
            }
            else if (j["id"] == getdomains["id"])
            {
                // response for initial getdomains call
                // cerr<<j.dump()<<endl;
                for (auto &[domain, _services] : j["result"].items())
                {
                    // cerr<<service.dump()<<endl;

                    // cout << "entity_id=" << entity_id << ", ";
                    // cout << "state=" << evd["state"];
                    // cout << endl;

                    domains[domain] = std::make_shared<HADomain>(_services);
                    // cerr<<"got services for domain "<<domain<<endl;
                }
                // exit(1);
            }
            else if (j["type"] == "event")
            {
                // something happened!
                auto event = j["event"];
                auto event_type = event["event_type"];
                auto evd = event["data"];
                auto entity_id = evd["entity_id"];

                auto old_state = evd["old_state"];
                auto new_state = evd["new_state"];

                // cout << "event_type=" << event_type << ", ";
                // cout << "entity_id=" << entity_id << ", ";
                // cout << "state=" << new_state["state"];
                // cout << endl;

                if (event_type == "state_changed")
                {
                    states[entity_id] = std::make_shared<HAEntity>(new_state);
                    whatchanged.push_back(entity_id);
                }
                else
                {
                    cerr << "Event type received that we didn't expect: " << event_type << endl;
                }
            }
            else
            {
                cerr << "Received message we don't expect: " << j["type"] << endl;
                // not a message we were expecting
                continue;
            }
        }
        // cerr<<"\033[2Jhave "<<states.size()<< " states" << endl;
        // cerr<<"selected = "<<selected<<endl;
        // cerr<<endl;
        // for (auto &[k,v] : states) {
        //   cout<<k<<"="<<v->getState()<<endl;
        // }
        {
            std::scoped_lock lk(entrieslock);
            entries.clear();

            for (auto &[k, v] : states)
            {
                entries.push_back(k); // +":"+v->getState());
            }
        }


        for (auto val : whatchanged)
        {
            cout << "What CHanged: " << val << endl;
        }
    }
}
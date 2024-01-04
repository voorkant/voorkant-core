#include <nlohmann/json.hpp>


#include <sstream>


// FIXME: logging should be centralised
#include <iostream>
using std::cerr;
using std::cout;
using std::endl;
// </FIXME>

#include "main.hpp"

using json = nlohmann::json;

using std::map;
using std::string;


// FIXME: combine states and stateslock so unlocked use becomes impossible
map<string, std::shared_ptr<HAEntity>> states;
std::mutex stateslock;

map<string, std::shared_ptr<HADomain>> domains;
std::mutex domainslock;



std::vector<std::string> entries;
std::mutex entrieslock;

// FIXME: leaking ref from inside a lock
// FIXME: don't copy entire vectors
// FIXME: arg wants to be ref
std::vector<std::string> getServicesForDomain(std::string domain) {
  if (domains.count(domain)) {
    return domains[domain]->getServices();
  }
  else {
    return {};
  }
}


void hathread(WSConn& wc) {
  auto welcome = wc.recv();
  auto jwelcome = json::parse(welcome);

  json auth;
  auth["type"] = "auth";
  auth["access_token"] = GetEnv("HA_API_TOKEN");
  wc.send(auth);

  json authresponse = json::parse(wc.recv());
  if (authresponse["type"] != "auth_ok") {
    cerr<<"Authentication failed, please check your HA_API_TOKEN"<<endl;
    return;
  }


  // cerr<<wc.recv()<<endl; // FIXME assert auth_ok

  json subscribe;

  subscribe["type"] = "subscribe_events";

  wc.send(subscribe);


  // json call;

  // call["type"]="call_service";
  // call["domain"]="light";
  // call["service"]="toggle";
  // call["target"]["entity_id"]="light.plafondlamp_kantoor_peter_level_light_color_on_off";

  // auto jcall = call.dump();

  // wc.send(jcall);

  json getstates;

  getstates["type"]="get_states";

  wc.send(getstates);

  json getdomains;

  getdomains["type"]="get_services";

  wc.send(getdomains);

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

  while (true) {
    auto msg = wc.recv();

    // cout<<msg<<endl;
    json j = json::parse(msg);

    std::vector<std::string> whatchanged;
    {
      std::scoped_lock lk(stateslock);

      if (j["id"] == getstates["id"]) {
        // response for initial getstates call
        for (auto evd : j["result"]) {
          // cerr<<evd.dump()<<endl;
          auto entity_id = evd["entity_id"];

          auto old_state = evd["old_state"];
          auto new_state = evd["new_state"];

          // cout << "entity_id=" << entity_id << ", ";
          // cout << "state=" << evd["state"];
          // cout << endl;

          states[entity_id] = std::make_shared<HAEntity>(evd);
          whatchanged.push_back(entity_id);
        }
        // exit(1);
      }
      else if (j["id"] == getdomains["id"]) {
        // response for initial getdomains call
        // cerr<<j.dump()<<endl;
        for (auto &[domain,_services] : j["result"].items()) {
          // cerr<<service.dump()<<endl;


          // cout << "entity_id=" << entity_id << ", ";
          // cout << "state=" << evd["state"];
          // cout << endl;

          domains[domain] = std::make_shared<HADomain>(_services);
          // cerr<<"got services for domain "<<domain<<endl;
        }
        // exit(1);
      }
      else if (j["type"] == "event") {
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

        if (event_type == "state_changed") {
          states[entity_id] = std::make_shared<HAEntity>(new_state);
          whatchanged.push_back(entity_id);
        }
      }
      else {
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

      for (auto &[k,v] : states) {
        entries.push_back(k); // +":"+v->getState());
      }
    }

    uithread_refresh(whatchanged);
  }
}

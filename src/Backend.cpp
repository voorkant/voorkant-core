

#include <iostream>
#include <string>
#include "Backend.hpp"


using std::string;
using std::cerr;
using std::endl;

HABackend::HABackend()
{
};

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

void HABackend::Start()
{
    if (wc == nullptr) {
        cerr<<"Do a damned connect first"<<endl;
    }
    // this should runt he HAthread that builds up the state, etc.
};
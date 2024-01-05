#ifndef BACKEND_HPP
#define BACKEND_HPP

#include <nlohmann/json.hpp>
#include <vector>
#include <map>
#include <thread>
#include "HAEntity.hpp"
#include "WSConn.hpp"

using std::string;

class Backend
{
};

class HABackend : Backend
{
public:
    HABackend();
    bool Connect(string url, string token);
    bool Start();
    string CreateLongToken(string name);

private:
    WSConn *wc = nullptr;
    std::thread ha;
    void threadrunner();

    std::vector<std::string> entries;
    std::mutex entrieslock;
    map<string, std::shared_ptr<HAEntity>> states;
    std::mutex stateslock;
    map<string, std::shared_ptr<HADomain>> domains;
    std::mutex domainslock;
};

#endif
#ifndef BACKEND_HPP
#define BACKEND_HPP

#include <nlohmann/json.hpp>
#include <sstream>

#include "WSConn.hpp"

using std::string;

class Backend {
};


class HABackend : Backend {
    public:
        HABackend();
        bool Connect(string url, string token);
        void Start();

private:
    WSConn *wc = nullptr;
    void hathread();
};


#endif
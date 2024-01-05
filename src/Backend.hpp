#include <nlohmann/json.hpp>
#include <sstream>

#include "WSConn.hpp"

using std::string;

class Backend {
};


class HABackend : Backend {
    public:
        HABackend(string url);

private:
    void hathread();
    WSConn wc;
};



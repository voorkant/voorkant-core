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
  std::vector<std::string> GetEntries();
  std::shared_ptr<HAEntity> GetState(const std::string& name);
  std::vector<std::shared_ptr<HAService>> GetServicesForDomain(const EntityType& domain);
  void WSConnSend(json& msg);

private:
  WSConn* wc = nullptr;
  std::thread ha;
  void threadrunner();

  std::vector<std::string> entries;
  std::mutex entrieslock;
  map<string, std::shared_ptr<HAEntity>> states; // FIXME: should this be called entities?
  std::mutex stateslock;
  map<EntityType, std::shared_ptr<HADomain>> domains;
  std::mutex domainslock;
};

#endif
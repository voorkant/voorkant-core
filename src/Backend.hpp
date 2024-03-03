#ifndef BACKEND_HPP
#define BACKEND_HPP

#include <nlohmann/json.hpp>
#include <vector>
#include <map>
#include <condition_variable>
#include <thread>
#include <unistd.h>
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
  struct ConnectionDetails
  {
    string url;
    string token;
  };
  bool connect(ConnectionDetails _conDetails);
  bool start();
  json doCommand(const std::string& _command, const json& _data);
  string createLongToken(string _name);
  std::shared_ptr<HAEntity> getEntityByName(const std::string& _name);
  std::vector<std::shared_ptr<HAEntity>> getEntitiesByDomain(const std::string& _domain);
  std::vector<std::shared_ptr<HAEntity>> getEntitiesByPattern(const std::string& _pattern);
  map<string, std::shared_ptr<HAEntity>> getEntities();
  void wsConnSend(json& _msg);

private:
  bool loaded;
  std::mutex load_lock;
  std::condition_variable load_cv;
  WSConn* wc = nullptr;
  std::thread ha;
  void threadrunner();

  map<string, std::shared_ptr<HAEntity>> entities;
  std::mutex entitieslock;
  map<string, std::shared_ptr<HADomain>> domains;
  std::mutex domainslock;
};

#endif
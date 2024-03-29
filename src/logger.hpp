#ifndef LOGGER_HPP
#define LOGGER_HPP

#include <deque>
#include <iostream>
#include <array>
#include <sstream>
#include <map>

using std::cerr;
using std::cout;
using std::endl;
using std::map;
using std::ostream;
using std::string;

class Logger
{
public:
  enum LogLevel
  {
    Error = 1,
    Warning = 2,
    Info = 3,
    Debug = 4,
  };
  struct Location
  {
    int linenr;
    std::string filename;
    std::string function;
  };

  Logger& operator<<(std::ostream& (&)(std::ostream&));
  Logger& operator<<(const char* _logline);
  Logger& operator<<(const std::string& _logline);
  Logger& operator<<(LogLevel); // allows us to do Logger<<LogLevel::Error<<"Someline";

  void writelog(LogLevel _level, const std::string& _logline, const Location _loc);

  void setLogLevel(LogLevel _whichlevel);
  void setDoDetails(bool _logDetails);
  void setLocation(const char* _filename, const int _linenr, const char* _method);

  std::string getForLogBox();

private:
  LogLevel level2log = LogLevel::Error;
  bool logDetails = false;
  std::deque<std::string> logBuffer;
  const size_t logBufferSize = 5;

  struct ThreadLocals
  {
    ThreadLocals() :
      level(LogLevel::Debug)
    {}
    std::string logline;
    LogLevel level;

    Location location;
  };
  ThreadLocals& getThreadLocal();
  static thread_local Logger::ThreadLocals tl;
};

Logger& getLogger(const char* _filename, const int _linenr, const char* _function);
#define g_log getLogger(__builtin_FILE(), __builtin_LINE(), __builtin_FUNCTION())
#endif

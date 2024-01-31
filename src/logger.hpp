#ifndef LOGGER_HPP
#define LOGGER_HPP

#include <iostream>
#include <array>
#include <sstream>
//#include <source_location>

using std::cerr;
using std::cout;
using std::endl;
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

  // Logger& operator<<(std::source_location loc);
  Logger& operator<<(std::ostream& (&)(std::ostream&));
  Logger& operator<<(const char* _logline);
  Logger& operator<<(const std::string& _logline);
  Logger& operator<<(LogLevel); // allows us to do Logger<<LogLevel::Error<<"Someline";

  // void writelog(LogLevel _level, const std::string& _logline, const std::source_location _loc);
  void writelog(LogLevel _level, const std::string& _logline, const int _linenr, const char* _file);

  void setLogLevel(LogLevel _whichlevel);
  void setDoDetails(bool _logDetails);

private:
  LogLevel level2log = LogLevel::Error;
  bool logDetails = false;

  struct ThreadLocals
  {
    ThreadLocals() :
      level(LogLevel::Debug)
    {}
    string logline;
    LogLevel level;
    //  std::source_location location;
  };
  ThreadLocals& getThreadLocal();
  static thread_local Logger::ThreadLocals tl;
};

// Logger& GetLogger(std::source_location loc = std::source_location::current());
Logger& GetLogger();
#define g_log GetLogger()
#endif

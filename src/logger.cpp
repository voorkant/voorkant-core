#include "logger.hpp"

thread_local Logger::ThreadLocals Logger::tl;

Logger& GetLogger(std::source_location loc)
{
  static Logger log;
  log << loc;
  return log;
}

void Logger::writelog(const LogLevel _level, const std::string& _line, const std::source_location _loc)
{
  if (level2log < _level) {
    return;
  }
  std::ostringstream line;

  std::array<char, 50> datetime{};
  datetime[0] = '\0';

  struct tm tm;
  time_t t;
  time(&t);
  localtime_r(&t, &tm);
  if (strftime(datetime.data(), datetime.size(), "%Y-%m-%d %H:%M:%S ", &tm) == 0) {
    datetime[0] = '\0';
  }

  line << datetime.data();
  switch (_level) {
  case Debug:
    line << "[DEBUG]";
    break;
  case Error:
    line << "[ERROR]";
    break;
  case Warning:
    line << "[WARNING]";
    break;
  case Info:
    line << "[INFO]";
    break;
  default:
    line << "[UNKNOWN]";
    break;
  }
  if (logDetails) {
    line << "[" << _loc.file_name() << ":" << _loc.line() << ':' << _loc.column() << "][" << _loc.function_name() << "]";
  }
  line << _line;

  if (_level == LogLevel::Error || _level == LogLevel::Warning) {
    std::cerr << line.str() << endl;
  }
  else {
    std::cout << line.str() << endl;
  }
}

Logger& Logger::operator<<(std::source_location loc)
{
  ThreadLocals& th = getThreadLocal();
  th.location = loc;
  return *this;
}

Logger& Logger::operator<<(ostream& (&)(ostream&))
{
  ThreadLocals& th = getThreadLocal();

  writelog(th.level, th.logline, th.location);
  th.logline.clear();
  th.level = LogLevel::Debug;
  return *this;
}

Logger& Logger::operator<<(const string& _logline)
{
  ThreadLocals& th = getThreadLocal();
  th.logline.append(_logline);
  return *this;
}

Logger& Logger::operator<<(const char* _logline)
{
  *this << string(_logline);
  return *this;
}

Logger& Logger::operator<<(LogLevel _level)
{
  ThreadLocals& th = getThreadLocal();
  th.level = _level;
  if (_level == LogLevel::Debug) {
    logDetails = true;
  }
  return *this;
}

Logger::ThreadLocals& Logger::getThreadLocal()
{
  return Logger::tl;
}

void Logger::setLogLevel(LogLevel _whichlevel)
{
  level2log = _whichlevel;
}

void Logger::setDoDetails(bool _logDetails)
{
  logDetails = _logDetails;
}
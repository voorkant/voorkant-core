#include "logger.hpp"

thread_local Logger::ThreadLocals Logger::tl;

void Logger::writelog(const std::string& _line, LogLevel _level)
{
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
    line << "[DEBUG] ";
    break;
  case Error:
    line << "[ERROR] ";
    break;
  case Warning:
    line << "[WARNING] ";
    break;
  case Info:
    line << "[INFO] ";
    break;
  default:
    line << "[UNKNOWN] ";
    break;
  }

  line << _line;

  if (_level == LogLevel::Error || _level == LogLevel::Warning) {
    std::cerr << line.str() << endl;
  }
  else {
    std::cout << line.str() << endl;
  }
}

Logger& Logger::operator<<(ostream& (&)(ostream&))
{
  ThreadLocals& th = getThreadLocal();

  writelog(th.logline, th.level);
  th.logline.clear();
  th.level = LogLevel::Info;
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
  return *this;
}

Logger::ThreadLocals& Logger::getThreadLocal()
{
  return Logger::tl;
}
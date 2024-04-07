#include "logger.hpp"
#include <iterator>

thread_local Logger::ThreadLocals Logger::tl;

Logger& getLogger(const char* _filename, const int _linenr, const char* _function)
{
  static Logger log;
  log.setLocation(_filename, _linenr, _function);
  return log;
}

void Logger::writelog(const LogLevel _level, const std::string& _line, const Location _loc)
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
  static std::map<LogLevel, std::string> loglevel2line = {
    {LogLevel::Debug, "[DEBUG]"},
    {LogLevel::Info, "[INFO]"},
    {LogLevel::Warning, "[WARNING]"},
    {LogLevel::Error, "[ERROR]"},
  };

  line << loglevel2line[_level];

  if (logDetails) {
    line << "[" << _loc.function << " in " << _loc.filename << ":" << _loc.linenr << "]";
  }
  line << " " << _line;

  std::cerr << line.str() << endl;
  logBuffer.push_back(line.str());
  if (logBuffer.size() > logBufferSize) {
    logBuffer.pop_front();
  }
  notify();
}

std::string Logger::getForLogBox()
{
  std::ostringstream ret;

  std::copy(logBuffer.begin(), logBuffer.end(), std::ostream_iterator<std::string>(ret, "\n"));

  return ret.str();
}

void Logger::setLocation(const char* _filename, const int _linenr, const char* _function)
{
  ThreadLocals& th = getThreadLocal();

  th.location.linenr = _linenr;
  th.location.filename = std::string(_filename);
  th.location.function = std::string(_function);
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

void Logger::attach(IObserver* _observer)
{
  observers.insert(_observer);
}
void Logger::detach(IObserver* _observer)
{
  observers.erase(_observer);
}

void Logger::notify()
{
  for (const auto& obs : observers) {
    obs->update();
  }
}
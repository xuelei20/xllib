#ifndef XUEL_LOGGER_H
#define XUEL_LOGGER_H

#include "noncopyable.h"
#include "LogStream.h"

namespace xuel
{

enum LogLevel
{
  TRACE = 0,
  DEBUG,
  INFO,
  WARN,
  ERROR,
  FAIL,
  SYSERR
};

extern LogLevel g_logLevel;

class Logger : noncopyable
{
public:
  Logger(LogLevel level, const char* srcFile, int line, const char* func);
  ~Logger();

  LogStream& stream() { return m_stream; }

  void writeToStdout(const char* data, size_t len);

  static void setLogLevel(LogLevel gLevel) { g_logLevel = gLevel; }

private:
  LogLevel m_level;
  const char* m_srcFile;
  int m_line;
  const char* m_func;
  LogStream m_stream;
};

#define LOGTRACE if (g_logLevel <= xuel::LogLevel::TRACE) \
  xuel::Logger(xuel::LogLevel::TRACE, __FILE__, __LINE__, __FUNCTION__).stream()
#define LOGDEBUG if (g_logLevel <= xuel::LogLevel::DEBUG) \
  xuel::Logger(xuel::LogLevel::DEBUG, __FILE__, __LINE__, __FUNCTION__).stream()
#define LOGINFO if (g_logLevel <= xuel::LogLevel::INFO) \
  xuel::Logger(xuel::LogLevel::INFO, __FILE__, __LINE__, __FUNCTION__).stream()
#define LOGWARN xuel::Logger(xuel::LogLevel::WARN, __FILE__, __LINE__, __FUNCTION__).stream()
#define LOGERROR xuel::Logger(xuel::LogLevel::ERROR, __FILE__, __LINE__, __FUNCTION__).stream()
#define LOGFAIL xuel::Logger(xuel::LogLevel::FAIL, __FILE__, __LINE__, __FUNCTION__).stream()
#define LOGSYSERR xuel::Logger(xuel::LogLevel::SYSERR, __FILE__, __LINE__, __FUNCTION__).stream()

} // namespace

#endif // XUEL_

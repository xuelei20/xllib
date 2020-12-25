#ifndef XUEL_LOGGER_H
#define XUEL_LOGGER_H

#include "noncopyable.h"
#include "LogStream.h"

namespace xuel
{

class Logger : noncopyable
{
public:
  enum LogLevel
  {
    TRACE,
    DEBUG,
    WARN,
    INFO,
    ERROR,
    FAIL
  };

  Logger(LogLevel level, const char* sourceFile, int line, const char* func);
  ~Logger();

  LogStream& stream() { return m_stream; }

  void writeToStdout(const char* data, size_t len);

private:
  LogLevel m_level;
  const char* m_sourceFile;
  int m_line;
  const char* m_func;
  LogStream m_stream;
};

#define LOGTRACE xuel::Logger(xuel::Logger::LogLevel::TRACE, __FILE__, __LINE__, __FUNCTION__).stream();
#define LOGDEBUG xuel::Logger(xuel::Logger::LogLevel::DEBUG, __FILE__, __LINE__, __FUNCTION__).stream();

} // namespace

#endif // XUEL_

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

  LogStream& stream();

private:
  LogLevel m_level;
  const char* m_sourceFile;
  int m_line;
  const char* m_func;
  LogStream m_stream;
};

} // namespace

#endif // XUEL_

#include "Logger.h"

using namespace xuel;

Logger::Logger(LogLevel level, const char* sourceFile, int line, const char* func) :
  m_level(level),
  m_sourceFile(sourceFile),
  m_line(line),
  m_func(func)
{
}

LogStream& Logger::stream()
{
  return m_stream;
}

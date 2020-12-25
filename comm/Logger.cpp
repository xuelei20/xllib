#include "Logger.h"

#include <stdio.h>

using namespace xuel;

Logger::Logger(LogLevel level, const char* sourceFile, int line, const char* func) :
  m_level(level),
  m_sourceFile(sourceFile),
  m_line(line),
  m_func(func)
{
}

Logger::~Logger()
{
  const LogStream::SmallBuffer& buffer = m_stream.getBuffer();
  writeToStdout(buffer.data(), buffer.len());
}

void Logger::writeToStdout(const char* data, size_t len)
{
  size_t n = fwrite(data, 1, len, stdout);
  //FIXME check n
}

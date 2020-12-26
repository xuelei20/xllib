#include "Logger.h"

#include <stdio.h>

using namespace xuel;

namespace xuel
{
LogLevel g_logLevel = LogLevel::INFO;
}

Logger::Logger(LogLevel level, const char* srcFile, int line, const char* func) :
  m_level(level),
  m_srcFile(srcFile),
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
  fwrite("\n", 1, 1, stdout);
}

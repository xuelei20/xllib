#include "Logger.h"
#include "CurrentThread.h"
#include "Timestamp.h"

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
  levelToStr();
}

Logger::~Logger()
{
  const LogStream::SmallBuffer& buffer = m_stream.getBuffer();
  writeToStdout(buffer.buff(), buffer.length());
}

void Logger::levelToStr()
{
  switch (m_level)
  {
    case TRACE:
      strncpy(m_levelStr, "TRACE ", sizeof(m_levelStr) - 1);
      break;
    case DEBUG:
      strncpy(m_levelStr, "DEBUG ", sizeof(m_levelStr) - 1);
      break;
    case INFO:
      strncpy(m_levelStr, "INFO  ", sizeof(m_levelStr) - 1);
      break;
    case WARN:
      strncpy(m_levelStr, "WARN  ", sizeof(m_levelStr) - 1);
      break;
    case ERROR:
      strncpy(m_levelStr, "ERROR ", sizeof(m_levelStr) - 1);
      break;
    case FAIL:
      strncpy(m_levelStr, "FAIL  ", sizeof(m_levelStr) - 1);
      break;
    case SYSERR:
      strncpy(m_levelStr, "SYSERR", sizeof(m_levelStr) - 1);
      break;
    default:
      strncpy(m_levelStr, "NOTDEF", sizeof(m_levelStr) - 1);
      break;
  }
}

void Logger::writeToStdout(const char* data, size_t len)
{
  char addbuff[128];
  snprintf(addbuff, sizeof(addbuff), "%s %d %s ", 
      Timestamp::format().c_str(), CurrentThread::getpid(), m_levelStr);
  fwrite(addbuff, 1, strlen(addbuff), stdout);

  size_t n = fwrite(data, 1, len, stdout);
  //FIXME check n

  snprintf(addbuff, sizeof(addbuff), " - %s:%d %s()\n", m_srcFile, m_line, m_func);
  fwrite(addbuff, 1, strlen(addbuff), stdout);
}

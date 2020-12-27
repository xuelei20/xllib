#include "LogFile.h"
#include "Timestamp.h"
#include "ProcessInfo.h"
#include "stringHelper.h"

#include <string.h>

using namespace xuel;

LogFile::LogFile() :
  m_file(new File(getLogName().c_str()))
{
}

std::string LogFile::getLogName()
{
  std::string logname;
  logname.reserve(128);

  logname = ProcessInfo::exeFullPath();

  char timebuff[32];
  Timestamp::userFormat(timebuff, sizeof(timebuff), ".%Y%m%d-%H%M%S");
  logname += timebuff;

  logname += stringHelper::format(".%s.%d.log", 
      ProcessInfo::hostName().c_str(), ProcessInfo::pid());

  return logname;
}

void LogFile::append(const char* data)
{
  if (nullptr != m_file)
    m_file->append(data, strlen(data));
}

void LogFile::flush()
{
  if (nullptr != m_file)
    m_file->flush();
}

#include "ProcessInfo.h"

#include <string.h>

#include <unistd.h>

using namespace xuel;

std::string ProcessInfo::hostName()
{
  char buff[256] = {0};
  if (::gethostname(buff, sizeof(buff)) == 0)
  {
    buff[sizeof(buff) - 1] = '\0';
    return buff;
  }
  else
  {
    return "unkownhost";
  }
}

pid_t ProcessInfo::pid()
{
  return ::getpid();
}

std::string ProcessInfo::exeFullPath()
{
  char path[1024];
  int rtn = readlink("/proc/self/exe", path, sizeof(path)); 
  if (rtn > 0)
  {
    return path;
  }
  return "";
}

std::string ProcessInfo::exePath()
{
  std::string fullPath = exeFullPath();
  const char* last = strrchr(fullPath.c_str(), '/');
  size_t len = last - fullPath.c_str();
  return fullPath.substr(0, len + 1);
}

std::string ProcessInfo::exeName()
{
  std::string fullPath = exeFullPath();
  const char* last = strrchr(fullPath.c_str(), '/');
  return last + 1;
}

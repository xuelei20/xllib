#ifndef XUEL_PROCESSINFO_H
#define XUEL_PROCESSINFO_H

#include "noncopyable.h"

#include <string>

namespace xuel
{

class ProcessInfo : noncopyable
{
public:
  static std::string hostName();
  static pid_t pid();
  static std::string exeFullPath();
  static std::string exePath();
  static std::string exeName();
};

} // namespace

#endif // XULE_

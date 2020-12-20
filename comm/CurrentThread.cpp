#include "CurrentThread.h"

#include <syscall.h>

using namespace xuel;

pid_t CurrentThread::getpid()
{
  pid_t pid = static_cast<pid_t>(syscall(SYS_gettid));
  return pid;
}

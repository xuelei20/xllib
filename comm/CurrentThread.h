#ifndef XUEL_CURRENTTHREAD_H
#define XUEL_CURRENTTHREAD_H

#include "noncopyable.h"

#include <unistd.h>

namespace xuel
{

class CurrentThread : noncopyable
{
public:
  // user define, using gettid(2)
  // Low efficiency, TODO: cache
  static pid_t getpid();
};

} // namespace

#endif // XUEL_

#ifndef XLLIB_CURRENTTHREAD_H
#define XLLIB_CURRENTTHREAD_H

#include "noncopyable.h"

#include <unistd.h>

namespace xllib
{

class CurrentThread : noncopyable
{
public:
  // user define, using gettid(2)
  // Low efficiency, TODO: cache
  static pid_t getpid();
};

} // namespace

#endif // XLLIB_

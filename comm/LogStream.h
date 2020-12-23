#ifndef XUEL_LOGSTREAM_H
#define XUEL_LOGSTREAM_H

#include "noncopyable.h"

namespace xuel
{

class LogStream : noncopyable
{
public:
  LogStream();

  LogStream& operator<<(int);

private:
  template<typename T>
  void formatInteger(T v);
};

} // namespace

#endif // XULE_

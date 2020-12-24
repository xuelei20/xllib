#ifndef XUEL_LOGSTREAM_H
#define XUEL_LOGSTREAM_H

#include "noncopyable.h"

#include <string.h>

namespace xuel
{

const int kSmallBuffSize = 4096;
const int kLargeBuffSize = 4096 * 1024;

template<int SIZE>
class FixBuffer : noncopyable
{
public:
  FixBuffer() :
    m_cur(0)
  {
  }

  // if larger than max size, will ignore
  void copy(const char* data, size_t size)
  {
    if (SIZE - m_cur > size)
    {
      memcpy(m_buff + m_cur, data, size);
      m_cur += size;
    }
  }

  void reset()
  {
    m_cur = 0;
  }

private:
  char m_buff[SIZE];
  int m_cur;
};

class LogStream : noncopyable
{
public:
  LogStream();

  LogStream& operator<<(int);
  LogStream& operator<<(const char*);

private:
  template<typename T>
  void formatInteger(T v);

  FixBuffer<kSmallBuffSize> m_buffer;
};

} // namespace

#endif // XULE_

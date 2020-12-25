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

  // if more than max size, will be ignored
  void append(const char* data, size_t len)
  {
    if (SIZE - m_cur > len)
    {
      memcpy(m_buff + m_cur, data, len);
      m_cur += len;
    }
  }

  void reset()
  {
    m_cur = 0;
  }

  int len() const { return m_cur; }
  const char* data() const { return m_buff; }

private:
  char m_buff[SIZE];
  int m_cur;
};

class LogStream : noncopyable
{
public:
  typedef FixBuffer<kSmallBuffSize> SmallBuffer;

  LogStream();

  LogStream& operator<<(int data);
  LogStream& operator<<(const char* data);

  const SmallBuffer& getBuffer() { return m_buffer; }

private:

  template<typename T>
  void formatInteger(T v);

  SmallBuffer m_buffer;
};

} // namespace

#endif // XULE_

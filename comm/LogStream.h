#ifndef XUEL_LOGSTREAM_H
#define XUEL_LOGSTREAM_H

#include "noncopyable.h"
#include "xldefine.h"

#include <string>
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

  void reset() { m_cur = 0; }
  int length() const { return m_cur; }
  const char* buff() const { return m_buff; }
  int avail() const { return sizeof(m_buff) - m_cur; }

private:
  char m_buff[SIZE];
  int m_cur;
};

class LogStream : noncopyable
{
public:
  typedef FixBuffer<kSmallBuffSize> SmallBuffer;

  LogStream& operator<<(short data);
  LogStream& operator<<(unsigned short data);
  LogStream& operator<<(int data);
  LogStream& operator<<(unsigned int data);
  LogStream& operator<<(long data);
  LogStream& operator<<(unsigned long data);
  LogStream& operator<<(long long data);
  LogStream& operator<<(unsigned long long data);

  LogStream& operator<<(float data);
  LogStream& operator<<(double data);

  LogStream& operator<<(const char* data);
  LogStream& operator<<(const unsigned char* data); 
  LogStream& operator<<(const std::string& data);

  LogStream& operator<<(char data); 
  LogStream& operator<<(bool data); 

  const SmallBuffer& getBuffer() { return m_buffer; }

private:
  template<typename T>
  void formatInteger(T v);

  SmallBuffer m_buffer;

  static const int kMaxNumberSize = 32;
};

class Fmt : noncopyable
{
public:
  template<typename T>
  Fmt(const char* fmt, T num);

  const char* buff() const { return m_buff; }
  int length() const { return m_length; } 

private:
  char m_buff[32];
  int m_length;
};

inline LogStream& operator<<(LogStream& stream, const Fmt& fmt)
{
  return stream << fmt.buff();
}

} // namespace

#endif // XULE_

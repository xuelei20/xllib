#include "LogStream.h"

#include <algorithm>
#include <stdio.h>

using namespace xuel;

namespace xuel
{
const char digits[] = "9876543210123456789";
const char* zero = digits + 9;
static_assert(sizeof(digits) == 20, "wrong number of digits");

// Efficient Integer to String Conversions, by Matthew Wilson.
template<typename T>
size_t convert(char buf[], T value)
{
  T i = value;
  char* p = buf;

  do
  {
    int lsd = static_cast<int>(i % 10);
    i /= 10;
    *p++ = zero[lsd];
  } while (i != 0);

  if (value < 0)
  {
    *p++ = '-';
  }
  *p = '\0';
  std::reverse(buf, p);

  return p - buf;
}
} // namesapce

LogStream& LogStream::operator<<(short data)
{
  *this << static_cast<int>(data);
  return *this;
}

LogStream& LogStream::operator<<(unsigned short data)
{
  *this << static_cast<int>(data);
  return *this;
}

LogStream& LogStream::operator<<(int data)
{
  formatInteger(data);
  return *this;
}

LogStream& LogStream::operator<<(unsigned int data)
{
  formatInteger(data);
  return *this;
}

LogStream& LogStream::operator<<(long data)
{
  formatInteger(data);
  return *this;
}

LogStream& LogStream::operator<<(unsigned long data)
{
  formatInteger(data);
  return *this;
}

LogStream& LogStream::operator<<(long long data)
{
  formatInteger(data);
  return *this;
}

LogStream& LogStream::operator<<(unsigned long long data)
{
  formatInteger(data);
  return *this;
}

LogStream& LogStream::operator<<(float data)
{
  *this << static_cast<double>(data);
  return *this;
}

// FIXME: replace this with Grisu3 by Florian Loitsch.
LogStream& LogStream::operator<<(double data)
{
  if (m_buffer.avail() > kMaxNumberSize)
  {
    char buff[kMaxNumberSize] = {0};
    int len = snprintf(buff, sizeof(buff), "%.12g", data);
    m_buffer.append(buff, len);
  }
  return *this;
}

LogStream& LogStream::operator<<(const char* data)
{
  if (data != nullptr)
  {
    m_buffer.append(data, strlen(data));
  }
  else
  {
    m_buffer.append("(nullptr)", 9);
  }
  return *this;
}

LogStream& LogStream::operator<<(const unsigned char* data)
{
  return operator<<(reinterpret_cast<const char*>(data));
}

LogStream& LogStream::operator<<(const std::string& data)
{
  m_buffer.append(data.c_str(), data.length());
  return *this;
}

LogStream& LogStream::operator<<(char data)
{
  m_buffer.append(&data, 1);
  return *this;
}

LogStream& LogStream::operator<<(bool data)
{
  m_buffer.append(data ? "1" : "0", 1);
  return *this;
}

template<typename T>
void LogStream::formatInteger(T v)
{
  if (m_buffer.avail() > kMaxNumberSize)
  {
    char buff[kMaxNumberSize] = {0};
    size_t use = convert(buff, v);
    m_buffer.append(buff, use);
  }
}

template<typename T>
Fmt::Fmt(const char* fmt, T num)
{
  static_assert(std::is_arithmetic<T>::value == true, "data type is not arithmetic");
  m_length = snprintf(m_buff, sizeof(m_buff), fmt, num);
  XL_ASSERT(m_length < sizeof(m_buff));
}

template Fmt::Fmt(const char* fmt, char);

template Fmt::Fmt(const char* fmt, short);
template Fmt::Fmt(const char* fmt, unsigned short);
template Fmt::Fmt(const char* fmt, int);
template Fmt::Fmt(const char* fmt, unsigned int);
template Fmt::Fmt(const char* fmt, long);
template Fmt::Fmt(const char* fmt, unsigned long);
template Fmt::Fmt(const char* fmt, long long);
template Fmt::Fmt(const char* fmt, unsigned long long);

template Fmt::Fmt(const char* fmt, float);
template Fmt::Fmt(const char* fmt, double);

#include "LogStream.h"

using namespace xuel;

LogStream::LogStream()
{

}

LogStream& LogStream::operator<<(int data)
{
  //TODO
  return *this;
}

LogStream& LogStream::operator<<(const char* data)
{
  m_buffer.copy(data, strlen(data));
  return *this;
}

template<typename T>
void LogStream::formatInteger(T v)
{

}

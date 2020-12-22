#ifndef XLLIB_FILE_H
#define XLLIB_FILE_H

#include "noncopyable.h"

#include <stdio.h>

namespace xuel
{

// not thread-safe
class AppendFile : noncopyable
{
public:
  AppendFile(const char* fileName);
  ~AppendFile();

  void append(const char* data, size_t size);

  void flush();

private:
  FILE* m_file;
};

} // namespace

#endif // XLLIB_

#ifndef XLLIB_FILE_H
#define XLLIB_FILE_H

#include "noncopyable.h"

#include <stdio.h>

namespace xuel
{

// not thread-safe
class File : noncopyable
{
public:
  File(const char* fileName, const char* mode = "a");
  ~File();

  void append(const char* data, size_t size);

  void flush();

private:
  FILE* m_file;
};

} // namespace

#endif // XLLIB_

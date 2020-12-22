#include "File.h"

#include <string.h>

using namespace xuel;

AppendFile::AppendFile(const char* fileName)
  : m_file(nullptr)
{
  m_file = fopen(fileName, "a");
}

AppendFile::~AppendFile()
{
  if (nullptr != m_file)
  {
    fclose(m_file);
  }
}

void AppendFile::append(const char* data, size_t size)
{
  size_t hasWrite = 0;
  while (hasWrite < size)
  {
    size_t curWrite = fwrite(data + hasWrite, 1, size, m_file);
    if (0 == curWrite)
    {
      int errno = ferror(m_file);
      if (errno)
      {
        char errstr[512];
        strerror_r(errno, errstr, sizeof(errstr));
        fprintf(stderr, "AppendFile::append fwrite failed: %s\n", errstr);
      }
    }
    hasWrite += curWrite;
  }
}

void AppendFile::flush()
{
  fflush(m_file);
}

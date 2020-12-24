#include "File.h"

#include <string.h>

using namespace xuel;

File::File(const char* fileName, const char* mode)
  : m_file(NULL)
{
  m_file = fopen(fileName, mode);
  if (NULL == m_file)
  {
    fprintf(stderr, "File::File fopen failed\n");
  }
}

File::~File()
{
  if (nullptr != m_file)
  {
    fclose(m_file);
  }
}

void File::append(const char* data, size_t size)
{
  size_t hasWrite = 0;
  while (hasWrite < size)
  {
    size_t curWrite = fwrite(data + hasWrite, size, 1, m_file);
    if (0 == curWrite)
    {
      int errno = ferror(m_file);
      if (errno)
      {
        char errstr[512];
        strerror_r(errno, errstr, sizeof(errstr));
        fprintf(stderr, "AppendFile::append fwrite failed: %s\n", errstr);
        break;
      }
    }
    hasWrite += curWrite;
  }
}

void File::flush()
{
  fflush(m_file);
}

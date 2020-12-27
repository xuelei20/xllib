#include "File.h"

#include <string.h>

using namespace xuel;

File::File(const char* fileName, const char* mode)
  : m_fp(nullptr)
{
  m_fp = fopen(fileName, mode);
  if (nullptr == m_fp)
  {
    fprintf(stderr, "File::File fopen failed\n");
  }
  setbuffer(m_fp, m_buff, sizeof(m_buff));
}

File::~File()
{
  if (nullptr != m_fp)
  {
    fclose(m_fp);
  }
}

void File::append(const char* data, size_t size)
{
  size_t hasWrite = 0;
  while (hasWrite < size)
  {
    size_t curWrite = fwrite(data + hasWrite, 1, size - hasWrite, m_fp);
    if (0 == curWrite)
    {
      int errno = ferror(m_fp);
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
  fflush(m_fp);
}

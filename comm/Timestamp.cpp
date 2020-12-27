#include "Timestamp.h"

#include <stdio.h>
#include <string.h>

#include <sys/time.h>

using namespace xuel;

int64_t Timestamp::now()
{
  struct timeval tv;
  gettimeofday(&tv, nullptr);
  return tv.tv_sec * kMicroSecondsPerSecond + tv.tv_usec;
}

std::string Timestamp::format(bool showMicro)
{
  struct timeval tv;
  gettimeofday(&tv, nullptr);

  struct tm cur;
  // gmtime_r(&tv.tv_sec, &cur);
  localtime_r(&tv.tv_sec, &cur);

  char buff[64] = {0};
  snprintf(buff, sizeof(buff), "%04d%02d%02d-%02d:%02d:%02d", 
    cur.tm_year+1900, cur.tm_mon+1, cur.tm_mday,
    cur.tm_hour, cur.tm_min, cur.tm_sec);
  if (showMicro)
  {
    char ubuff[8];
    snprintf(ubuff, sizeof(ubuff), ".%06d", static_cast<int>(tv.tv_usec));
    strcat(buff, ubuff);
  }

  return buff;
}

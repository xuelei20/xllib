#include "stringHelper.h"

using namespace xllib;

std::string& stringHelper::toUpper(std::string& str)
{
  std::string::iterator it;
  for (it = str.begin(); it != str.end(); ++it)
  {
    *it = toupper(*it);
  }
  return str;
}

std::string format(const char* fmt, ...)
{
  char buff[1024];

  va_list args;
  va_start(args, fmt);
  vsnprintf(buff, sizeof(buff)-1, fmt, args);
  va_end(args);

  return std::string(buff);
}

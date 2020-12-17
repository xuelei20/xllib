#ifndef XLLIB_STRING_H
#define XLLIB_STRING_H

#include "../base/noncopyable.h"

#include <string>
#include <stdarg.h>

namespace xllib
{

class stringHelper : noncopyable
{
public:
  static std::string& toUpper(std::string& str)
  {
    std::string::iterator it;
    for (it = str.begin(); it != str.end(); ++it)
    {
      *it = toupper(*it);
    }
    return str;
  }

  static std::string format(const char* fmt, ...)
  {
    char buff[1024];

    va_list args;
    va_start(args, fmt);
    vsnprintf(buff, sizeof(buff)-1, fmt, args);
    va_end(args);

    return std::string(buff);
  }

};

} // namespace
#endif // XLLIB_

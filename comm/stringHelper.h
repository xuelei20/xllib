#ifndef XLLIB_STRING_H
#define XLLIB_STRING_H

#include "noncopyable.h"

#include <string>
#include <stdarg.h>

namespace xllib
{

class stringHelper : noncopyable
{
public:
  static std::string& toUpper(std::string& str);

  static std::string format(const char* fmt, ...);
  
};

} // namespace
#endif // XLLIB_

#ifndef XUEL_STRING_H
#define XUEL_STRING_H

#include "noncopyable.h"

#include <string>
#include <stdarg.h>

namespace xuel
{

class stringHelper : noncopyable
{
public:
  static std::string& toUpper(std::string& str);

  static std::string format(const char* fmt, ...);
  
};

} // namespace
#endif // XUEL_

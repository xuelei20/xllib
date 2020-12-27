#ifndef XUEL_TIMESTAMP_H
#define XUEL_TIMESTAMP_H

#include "noncopyable.h"

#include <string>
#include <stdint.h>

namespace xuel
{

class Timestamp : noncopyable
{
public:
  static int64_t now();
  static std::string format(bool showMicro = true);
  static void userFormat(char* buff, int len, const char* fmt);

private:
  static const int kMicroSecondsPerSecond = 1000 * 1000;
};

} // namespace

#endif // XULE_

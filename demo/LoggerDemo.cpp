#include "../comm/Logger.h"

using namespace xuel;

int main()
{
  // Logger::setGlobalLevel(LogLevel::WARN);
  LOGTRACE << "hello trace";
  LOGDEBUG << "hello debug";
  unsigned char data[] = "nihao";
  LOGINFO << "hello info," << data;
  LOGWARN << "hello warn," << 3 << "int" << 56;
  LOGERROR << "hello error," << 1.234 << "," << 6.90;
  LOGFAIL << "hello fail," << 'c' << "," << true << false;
  LOGSYSERR << "hello syserr," << std::string("string");

  return 0;
}

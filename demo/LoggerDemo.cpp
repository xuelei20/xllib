#include "../comm/Logger.h"
#include <thread>

using namespace xuel;

void proc()
{
  LOGDEBUG << "new thread" << 1;
}

int main()
{
  Logger::setLogLevel(LogLevel::TRACE);
  LOGTRACE << "hello trace";
  LOGDEBUG << "hello debug";
  unsigned char data[] = "nihao";
  LOGINFO << "hello info," << data;
  LOGWARN << "hello warn," << 3 << "int" << 56;
  LOGERROR << "hello error," << 1.234 << "," << 6.90;
  LOGFAIL << "hello fail," << 'c' << "," << true << false;
  LOGSYSERR << "hello syserr," << std::string("string");

  LOGWARN << 0;
  LOGWARN << (void*)0;
  // LOGWARN << NULL; // warning
  // LOGWARN << nullptr; // not support
  
  LOGINFO << "format:" << Fmt("%.2f", 3.1415) << " ok";

  std::thread thr1(proc);
  thr1.join();

  return 0;
}

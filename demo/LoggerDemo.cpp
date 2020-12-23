#include "../comm/Logger.h"

using namespace xuel;

int main()
{
  Logger logger(Logger::LogLevel::INFO, __FILE__, __LINE__, __FUNCTION__);
  LogStream& stream = logger.stream();

  return 0;
}

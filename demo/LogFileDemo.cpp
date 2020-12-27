#include "../comm/LogFile.h"
#include "../comm/Logger.h"

using namespace xuel;

int main()
{
  LogFile file;
  file.append("hello,");
  file.append("append");
}

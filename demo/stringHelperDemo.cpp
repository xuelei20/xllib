#include "../comm/stringHelper.h"

#include <iostream>

int main()
{
  std::string str1("hello");
  xuel::stringHelper::toUpper(str1).append("add");
  std::cout << str1 << std::endl;

  std::string strformat = xuel::stringHelper::format("format%d, %s", 23, "this");
  std::cout << strformat << std::endl;
}

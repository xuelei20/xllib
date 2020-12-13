#include "../plat/xldefine.h"
#include <stdio.h>

int main()
{
  void *ptr = 0;
  // assert(ptr != 0);
  XL_ASSERT(ptr != 0);
  printf("hello assert\n");
}

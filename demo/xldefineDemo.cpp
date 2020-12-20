#include "../comm/xldefine.h"
#include <stdio.h>
#include <assert.h>

int main()
{
  void *ptr = 0;
  assert(ptr != 0);
  printf("hello assert\n");
}

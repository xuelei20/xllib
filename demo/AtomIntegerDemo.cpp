#include "AtomInteger.h"
#include <stdio.h>

int main()
{
  xllib::AtomInteger<int> num;
  num.set(3);
  int n = num.getAndAdd(2);
  int val = num.get();
  printf("%d, %d\n", n, val);

  xllib::AtomInteger<int> num2;
  num2.set(3);
  int n2 = num2.addAndGet(2);
  int val2 = num2.get();
  printf("%d, %d\n", n2, val2);

  return 0;
}

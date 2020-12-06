#include "stdio.h"

int add(int a, int b)
{
  return a+b;
}

int add(float a, float b) // c has no function overload (gcc compile error)
{
  return a+b;
}

int main()
{
  int sum = add(1, 2);
}

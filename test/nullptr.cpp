#include <stdio.h>

int main()
{
  char p[] = "hello";
  // int *a = (void*)p; // c++ can't convert
  
  FILE* fp = fopen("a.txt", "r");
  if (NULL == fp)
  {
    printf("fp is NULL\n");
  }
  if (nullptr == fp)
  {
    printf("fp is nullptr\n");
  }

  return 0;
}

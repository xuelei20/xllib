// g++ coredump.cpp -g
// ./a.out-----Segmentation fault(core dumped)
// 1.gdb a.out core
// 2.r
// 3.bt
#include <stdio.h>

class Foo
{
public:
  void print()
  {
    printf("Foo::print\n");
  }
  void printMember()
  {
    printf("m_n:%d\n", m_n);
  }
private:
  int m_n;
};

void testNull(void *ptr)
{
  int a = 0;
  int b = a + 4;
  Foo *pobj = (Foo *)ptr;
  pobj->print(); // ok
  pobj->printMember(); // core dump
  int c = b - 3;
  printf("testNull\n");
}

int main()
{
  char a = 'a';
  Foo *foo = NULL;
  testNull(foo);
  char b = 'b';
  return 0;
}

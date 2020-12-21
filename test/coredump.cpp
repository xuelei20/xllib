// g++ coredump.cpp -g
// ./a.out-----Segmentation fault(core dumped)
// 1.gdb a.out core
// 2.r
// 3.bt
#include <vector>
#include <string>
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
  std::vector<std::string> veclog;
  veclog.push_back("hello log1");
  veclog.push_back("this is log2");
  int a = 0;
  Foo *pobj = (Foo *)ptr;
  pobj->print(); // ok
  pobj->printMember(); // core dump
  printf("testNull\n");
}

int main()
{
  Foo *foo = NULL;
  testNull(foo);
  return 0;
}

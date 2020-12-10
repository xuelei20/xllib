#include "../comm/ThreadPool.h"

#include <unistd.h>
#include <stdio.h>

void add()
{
  int a = 1;
  int b = 2;
  int c = a + b;
  printf("a+b=%d\n", c);
}

void mul()
{
  int a = 1;
  int b = 2;
  int c = a * b;
  printf("a*b=%d\n", c);
}

class Foo
{
public:
  void print()
  {
    printf("hello\n");
  }
};

void testClassThread()
{
  Foo foo;
  std::thread thr(&Foo::print, foo);
  thr.join();
}

void testThreadPool()
{
  xllib::ThreadPool threadPool(1);
  threadPool.start();

  std::function<void()> func = std::bind(add);
  threadPool.postTask(func);
  threadPool.postTask(func);
  std::function<void()> func2 = std::bind(mul);
  threadPool.postTask(func2);

  sleep(2); //wait do work
  threadPool.stop();
}

int main()
{
  testThreadPool();
  sleep(2);

  return 0;
}

#include "../comm/ThreadPool.h"
#include "Thread.h"

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
  Foo(int n) :
    m_num(n)
  {
  }
  void print()
  {
    printf("hello %d\n", m_num);
  }
private:
  int m_num;
};

// void testClassThread()
// {
  // Foo foo(1);
  // std::thread thr(&Foo::print, foo);
  // thr.join();
// }

void testThreadPool()
{
  xuel::ThreadPool threadPool;
  threadPool.start(2);

  std::function<void()> func = std::bind(add);
  threadPool.post(func);
  threadPool.post(func);

  {
    Foo foo(2); // life time?
    std::function<void()> func2 = std::bind(&Foo::print, foo);
    threadPool.post(func2);
  }

  sleep(5); //wait do work
  threadPool.stop();
}

void testPrimaryThreadPool()
{
  xuel::ThreadPool threadPool;
  threadPool.start(1);

  std::function<void()> func = std::bind(add);
  threadPool.post(func);
  sleep(5);
  threadPool.stop();
}

void test()
{
  printf("hello pool\n");
}

int main()
{
  testThreadPool();
  sleep(2);

  return 0;
}

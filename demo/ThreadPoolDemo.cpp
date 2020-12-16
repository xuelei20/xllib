#include "../comm/ThreadPool.h"

#include <thread>

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

void testClassThread()
{
  Foo foo(1);
  std::thread thr(&Foo::print, foo);
  thr.join();
}

void testThreadPool()
{
  xllib::ThreadPool& threadPool = xllib::ThreadPool::instance();
  threadPool.start(2);

  std::function<void()> func = std::bind(add);
  threadPool.postTask(func);
  threadPool.postTask(func);

  {
    Foo foo(2); // life time?
    std::function<void()> func2 = std::bind(&Foo::print, foo);
    threadPool.postTask(func2);
  }

  sleep(5); //wait do work
}

void test()
{
  printf("hello pool\n");
}

void testThreadPool2()
{
  xllib::ThreadPool& pool = xllib::ThreadPool::instance();
  xllib::TaskQueue::Task task = std::bind(test);
  pool.postTask(task);
  sleep(1);
  pool.stop();
}

int main()
{
  testThreadPool();
  testThreadPool2();
  sleep(2);

  return 0;
}

#include "../plat/Thread.h"
#include <unistd.h>
#include <thread>
#include <functional>
#include <iostream>

void *pointerArgRtn(void *arg)
{
  while (1)
  {
    printf("pointerArgRtn\n");
    sleep(1);
  }
}

void poniterArg(void *arg)
{
  while (1)
  {
    sleep(1);
  }
}

void loopNon()
{
  for (int i=0; i<20; i++)
  {
    printf("loopNon\n");
    sleep(1);
  }
}

void add(int a, int b)
{
  while (1)
  {
    printf("loopNon\n");
    sleep(1);
  }
}

class Foo
{
public:
  static void *poniterArgRtn(void *)
  {
    return NULL;
  }
  int add(int a, int b)
  {
    int c = a + b;
    printf("a+b=%d\n", c);
    return c;
  }
};

void testPthread()
{
  pthread_t pid;
  pthread_create(&pid, NULL, pointerArgRtn, NULL);
  pthread_join(pid, NULL);
}

void testStdThread()
{
  std::thread thr1(loopNon);

  Foo foo;
  std::thread thr2(std::bind(&Foo::add, foo, 4, 9));

  thr1.join();
  thr2.join();
}

void testXLThread()
{
  xllib::Thread thr1(loopNon);
  thr1.start();
  // std::cout << thr1.getName() << std::endl;

  Foo foo;
  xllib::Thread thr2(std::bind(&Foo::add, foo, 34, 9));
  thr2.start();

  thr1.join();
}

int main()
{
  // testStdThread();
  // testPthread();
  testXLThread();

  return 0;
}

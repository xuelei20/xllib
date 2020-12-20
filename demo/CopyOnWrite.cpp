#include "Mutex.h"

#include <vector>
#include <memory>
#include <thread>

#include <stdio.h>
#include <unistd.h>

// version1: effective
class Foo
{
public:
  void doit();
};

xllib::Mutex g_mutex;
std::vector<Foo> g_foos;

void post(const Foo& foo)
{
  xllib::MutexGuard guard(g_mutex);
  g_foos.push_back(foo);
}

void traverse()
{
  xllib::MutexGuard guard(g_mutex);
  std::vector<Foo>::iterator it;
  for (it = g_foos.begin(); it != g_foos.end(); ++it)
  {
    it->doit();
  }
}

void Foo::doit()
{
  // Foo f;
  printf("doit\n");
  // post(f); // deadlock
}

void test()
{
  Foo foo;
  post(foo);
  traverse();
}

typedef std::vector<Foo> FooList;
typedef std::shared_ptr<FooList> FooListPtr;
FooListPtr g_shareFoos;

void post_cow(const Foo& foo)
{
  printf("post_cow\n");
  xllib::MutexGuard guard(g_mutex);
  if (!g_shareFoos.unique()) // write, when there's other is reading
  {
    // copy-on-write(copy-on-other-reading exactly)
    g_shareFoos.reset(new FooList(*g_shareFoos));
    printf("copy on other reading (whole list)\n");
  }
  g_shareFoos->push_back(foo);
}

void traverse_cow()
{
  printf("traverse_cow\n");
  FooListPtr foos;
  {
    xllib::MutexGuard guard(g_mutex);
    foos = g_shareFoos; // when reading, reference count +1
  }
  std::vector<Foo>::iterator it;
  for (it = g_shareFoos->begin(); it != g_shareFoos->end(); ++it)
  {
    it->doit();
  }
  sleep(2); // for example, add sleep
}

void test_cow()
{
  g_shareFoos.reset(new FooList);

  std::thread thr1([]()
  {
    while (1)
    {
      Foo foo;
      post_cow(foo);
      sleep(1);
    }
  });

  std::thread thr2([]()
  {
    while (1)
    {
      traverse_cow();
    }
  });

  thr1.join();
  thr2.join();

}

int main()
{
  // test();
  test_cow();
  return 0;
}

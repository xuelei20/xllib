#include "Mutex.h"

#include <thread>

#include <unistd.h>

xuel::Mutex g_mutex;
int g_num = 0;

void add()
{
  xuel::MutexGuard guard(g_mutex); 
  for (int i=0; i<5; i++)
  {
    g_num = i;
    printf("add, g_num = %d\n", i);
    sleep(1);
  }
}

void show()
{
  sleep(1);
  xuel::MutexGuard guard(g_mutex);
  printf("del, g_num = %d\n", g_num);
}

int main()
{
  add();
  std::thread thr2(show);
  thr2.join();
  return 0;
}

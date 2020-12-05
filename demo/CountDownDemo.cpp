#include "../base/CountDown.h"

#include <thread>

#include <unistd.h>

xllib::CountDown g_cdown(10);

void doLongWork()
{
  for (int i=0; i<10; ++i)
  {
    printf("long work\n");
    g_cdown.down();
    sleep(1);
  }
}

void doOtherWork()
{
  g_cdown.wait();
  printf("sub work\n");
}

int main()
{
  doLongWork();
  //subthread wait for mainthread
  std::thread thr1(doOtherWork);
  std::thread thr2(doOtherWork);
  thr1.join();
  thr2.join();

  return 0;
}

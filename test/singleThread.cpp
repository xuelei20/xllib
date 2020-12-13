#include <stdio.h>
#include <thread>

void busy()
{
  while (1)
  {
    printf("busy\n");
  }
}

int main()
{
  std::thread thr(busy); // if add one thread, 2 CPU core will be use.
  busy();
  thr.join();
  return 0;
}

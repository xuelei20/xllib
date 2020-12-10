#include "../comm/BlockingQueue.h"

#include <thread>
#include <string>
#include <iostream>
#include <queue>

#include <unistd.h>

xllib::BlockingQueue<std::string> g_blockqueue;

void Producer()
{
  for (int i=0; i<10; i++)
  {
    char szName[20] = {0};
    snprintf(szName, sizeof(szName)-1, "name%d", i);
    std::string strName(szName); // wrong use
    g_blockqueue.put(strName);
    sleep(1);
  }
}

void Consumer()
{
  while (1)
  {
    std::string name = g_blockqueue.take();
    std::cout << name << std::endl;
    //sleep(2);
  }
}

int main()
{
  std::thread thrPro1(Producer);
  std::thread thrPro2(Producer);
  std::thread thrCon(Consumer);
  thrPro1.join();
  thrPro2.join();
  thrCon.join();

  return 0;
}

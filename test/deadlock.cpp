#include <iostream>
#include <thread>
#include <unistd.h>
#include <pthread.h>
using namespace std;

pthread_mutex_t g_mutex = PTHREAD_MUTEX_INITIALIZER;

void funcA()
{
  pthread_mutex_lock(&g_mutex);
  while (true)
  {
    cout << __FUNCTION__ << endl;
    sleep(1);
  }
  pthread_mutex_unlock(&g_mutex);
}

void func1()
{
  pthread_mutex_lock(&g_mutex);
  while (true)
  {
    cout << __FUNCTION__ << endl;
    sleep(1);
    funcA();
  }
  pthread_mutex_unlock(&g_mutex);
}

void func2()
{
  pthread_mutex_lock(&g_mutex);
  while (true)
  {
    cout << __FUNCTION__ << endl;
    sleep(1);
  }
  pthread_mutex_unlock(&g_mutex);
}


int main()
{
  thread thr1(func1);
  thread thr2(func2);
  thr1.join();
  thr2.join();
  return 0;
}

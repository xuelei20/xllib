#include <iostream>
#include <thread>
#include <unistd.h>
#include <pthread.h>
using namespace std;

pthread_mutex_t g_mutex = PTHREAD_MUTEX_INITIALIZER;

void show()
{
  pthread_mutex_lock(&g_mutex);
  while (true)
  {
    cout << __FUNCTION__ << endl;
    sleep(1);
  }
  pthread_mutex_unlock(&g_mutex);
}

void Thread1func()
{
  pthread_mutex_lock(&g_mutex);
  while (true)
  {
    cout << __FUNCTION__ << endl;
    sleep(1);
    show();
  }
  pthread_mutex_unlock(&g_mutex);
}

void Thread2func()
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
  thread thr1(Thread1func);
  thread thr2(Thread2func);
  thr1.join();
  thr2.join();
  return 0;
}

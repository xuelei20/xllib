//std::string std::vector std::shared_ptr ... is not thread-safe.
#include <iostream>
#include <string>
#include <thread>
#include <mutex>
#include <unistd.h>
#include "../base/Mutex.h"
using namespace std;

const int loopnum = 200;

class TestClass
{
public:
  void func1()
  {
    for (int i=0; i<loopnum; i++)
    {
//      xllib::MutexLockGuard guard(m_mutex);
      str += "hellosafe ";
    }
  }

  void func2()
  {
    for (int i=0; i<loopnum; i++)
    {
//      xllib::MutexLockGuard guard(m_mutex);
      str += "nihao ";
    }
  }
  void show()
  {
    cout << str << endl;
  }

private:
  string str;
  mutex m_mutex;
};

TestClass a;

void funcA()
{
  a.func1();
  a.func2();
}
void funcB()
{
  a.func2();
}

int main()
{
  thread thr1(funcA);
  thread thr2(funcB);
  thr1.join();
  thr2.join();
  a.show();
  return 0;
}

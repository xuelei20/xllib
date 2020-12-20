//std::string std::vector std::shared_ptr ... is not thread-safe.
#include <iostream>
#include <string>
#include <thread>
#include <mutex>
#include <unistd.h>
#include "../base/Mutex.h"
using namespace std;

const int loopnum = 200;

class StringClass
{
public:
  void func1()
  {
    for (int i=0; i<loopnum; i++)
    {
//      xuel::MutexLockGuard guard(m_mutex);
      str += "hellosafe ";
    }
  }

  void func2()
  {
    for (int i=0; i<loopnum; i++)
    {
//      xuel::MutexLockGuard guard(m_mutex);
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

StringClass a;

void funcA()
{
  a.func1();
  a.func2();
}
void funcB()
{
  a.func2();
}

void testString()
{
  thread thr1(funcA);
  thread thr2(funcB);
  thr1.join();
  thr2.join();
  a.show();
}

class A
{
public:
  A(string name) : m_name(name)
  {
  }
  void out()
  {
    cout << "out:" << m_name << endl;
  }
  ~A()
  {
    cout << "~A():" << m_name << endl;
  }

private:
  string m_name;
};

shared_ptr<A> g_ptr(new A("global"));
std::mutex g_mutex;

void doit(const shared_ptr<A> &pa)
{
  pa->out();
}

void readSharedPtr()
{
  shared_ptr<A> localPtr;
  { //less lock range
    xuel::MutexLockGuard guard(g_mutex);
    localPtr = g_ptr; //read global ptr
  }
  doit(localPtr); //use local, don't need lock(to shared_ptr, not A obj)
}

void writeSharedPtr()
{
  shared_ptr<A> newpa(new A("localnew"));
  shared_ptr<A> saveptr(g_ptr);
  { //less lock range
    xuel::MutexLockGuard guard(g_mutex);
    g_ptr = newpa; //write to global ptr
    cout << "lock range\n";
  }
  doit(newpa); //use new, don't need lock(to shared_ptr, not A obj)
}

int main()
{
  //testString();
  //readSharedPtr();
  writeSharedPtr();
  return 0;
}

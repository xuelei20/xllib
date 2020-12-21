#include <functional>
#include <iostream>
#include <thread>
#include <unistd.h>
using namespace std;
using namespace placeholders;

int add(int a, int b, int c)
{
  int total = a+b+c;
  cout << a << " " << b << " " << c << ",a+b+c=" << total << endl;
  return total;
}

int mul(int a, int b, int c)
{
  int total = a*b*c;
  cout << a << " " << b << " " << c << ",a*b*c=" << total << endl;
  return total;
}
typedef std::function<int(int,int,int)> callfunIIII;

void funCall(int a, int b, int c, callfunIIII f)
{
  f(a, b, c);
}

class A
{
public:
  A(int a) : m_a(a)
  {
  }
  double funA(int a, double b)
  {
    cout << "m_a=" << m_a << ";";
    cout << a << " " << b << ",a+b=" << a + b << endl;
    return a+b;
  }
private:
  int m_a;
};

int test()
{
  std::function<int(int,int,int)> funadd = add;
  funadd(1,2,3);

  // std::function<int(int,int)> funadd2 = add; // compile error
  std::function<int()> funcadd2 = std::bind(&add, 3, 2, 1);
  funcadd2();

  auto func1 = std::bind(&add, _1, 20, 30);
  func1(10);

  std::function<int(int,int,int)> func2 = std::bind(&add, _2, _1, _3);
  func2(11, 22, 33);

  cout << "LINE:" << __LINE__ << endl;
  std::function<int(int,int,int)> func22 = std::bind(&add, 11, _2, _3);
  func22(0, 22, 33);

  funCall(111, 222, 333, func2);
  funCall(111, 222, 333, std::bind(&mul, _1, _2, _3));

  A obja(99);
  function<double(int,double)> func3 = bind(&A::funA, &obja, _1, _2); //obj addr is first param
  func3(10, 22.2);

  return 0;
}

class Foo
{
public:
  void add(int n)
  {
    a = n;
    while (1)
    {
      cout << "add" << endl;
      sleep(1);
    }
  }
  void sub()
  {
    while (1)
    {
      cout << "sub" << endl;
      cout << a;
      sleep(1);
    }
  }
  int a;
};

typedef std::function<void()> MsgFun;
MsgFun m_msgFun;

void msgLoop()
{
  while (true)
  {
    m_msgFun();
    cout << "func" << endl;
    sleep(1);
  }
}

void setMsgFun(MsgFun func)
{
  m_msgFun = func;
}


int test2()
{
  // Foo foo;
  // std::function<void()> funloop = std::bind(&Foo::add, &foo, 20);
  Foo *pfoo = new Foo;
  setMsgFun(std::bind(&Foo::sub, pfoo));
  std::thread thr(msgLoop);
  sleep(3); // pfoo is release, core dump
  return 0;
}

int main()
{
  test2();
  sleep(100);
  return 0;
}

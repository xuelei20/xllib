#include <functional>
#include <iostream>
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

int main()
{
  auto func1 = std::bind(&add, _1, 20, 30);
  func1(10);

  std::function<int(int,int,int)> func2 = std::bind(&add, _2, _1, _3);
  func2(11, 22, 33);

  std::function<int(int,int,int)> func22 = std::bind(&add, _1, 20, _3);
  func22(11, 0, 33);

  funCall(111, 222, 333, func2);
  funCall(111, 222, 333, std::bind(&mul, _1, _2, _3));

  A obja(99);
  function<double(int,double)> func3 = bind(&A::funA, &obja, _1, _2);
  func3(10, 22.2);

  return 0;
}

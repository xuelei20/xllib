#include <iostream>
#include <vector>
#include <string>

class Foo
{
public:
  Foo(int num) : n(num) {}
  int n;
};

void testFoo()
{
  std::vector<Foo> vec;
  vec.push_back(Foo(2));
  vec.push_back(Foo(3));
  Foo f(4);
  vec.push_back(std::move(f));
  f.n = 5;
  for (auto a : vec)
  {
    std::cout << a.n << std::endl;
  }
  std::cout << f.n << std::endl;
}

void testStr()
{
  std::string str = "Hello";
  std::vector<std::string> v;
  //调用常规的拷贝构造函数，新建字符数组，拷贝数据
  v.push_back(str);
  std::cout << "After copy, str is \"" << str << "\"\n";
  //调用移动构造函数，掏空str，掏空后，最好不要使用str
  v.push_back(std::move(str));
  std::cout << "After move, str is \"" << str << "\"\n";
  std::cout << "The contents of the vector are \"" << v[0]
           << "\", \"" << v[1] << "\"\n";
}

int main()
{
  testFoo();
  testStr();
  return 0;
}

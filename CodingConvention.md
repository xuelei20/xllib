```
######### 我的代码风格
///////// Foo.h
#ifndef XLLIB_FOO_H
#define XLLIB_FOO_H

#include "myheader.h"

#include <string>
#include <stdio.h>

#inclue <unistd.h>

#include "third.h"

namespace xllib
{

class Foo : noncopyable
{
public:
  // comment
  Foo(int num, std::string& name);
  // comment
  void setName(const std::string& name); // param: const & obj
  // comment
  std::string getName() const; // return: don't need &, but need const
  // comment
  void showInfo();

private:
  int m_num;
  std::string m_name;
  std::shared_ptr<Person> m_person;
};

} // namespace
#endif // XLLIB_

///////// Foo.cpp
#include "Foo.h"
#include "other.h"

Foo::Foo(int num, std::string& name)
  : m_num(num)
  , m_name(name)
{
}

void Foo::showInfo()
{
}
```
追求简单、健壮，在这个基础上再优化效率。

ModernC++
|        不用        |                        替代者                         |
| :---------------: | :--------------------------------------------------: |
|   char buff[32]   |                     std::string                      |
|       new[]       |                     std::vector                      |
|   原始指针 Foo*    | 引用& 或 智能指针std::shared_ptr/scoped_ptr/unique_ptr |
|        继承        |                       数据成员                        |
| 多态/虚函数 或 回调 |               std::function、std::bind               |
|        异常        |                      返回值和log                      |
|    手动资源管理     |                         RAII                         |

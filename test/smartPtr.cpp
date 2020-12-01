#include <memory>
#include <iostream>
using namespace std;

class Foo
{
public:
  void print()
  {
    cout << "print\n";
  }
};

void save(const shared_ptr<Foo> &pFoo)
{
  pFoo->print();
}

int main()
{
  shared_ptr<Foo> pFoo(new Foo); //one
  save(pFoo); //const refrence

  shared_ptr<void> pVoid(new Foo); //can hold any type ptr, and can release safe.
  pVoid.reset(new Foo());

  return 0;
}

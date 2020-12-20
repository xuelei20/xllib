#include "Singleton.h"

#include <stdio.h>

class Factory
{
public:
  void show()
  {
    printf("show %d\n", m_num);
  }
  
  int m_num;

// private:
  // Factory(); // if it's private, can't construct.
  // ~Factory();
};

void singletonOnce()
{
  Factory *pFac = xuel::SingletonOnce<Factory>::instance();
  pFac->m_num = 10;
  pFac->show();

  Factory *pFac2 = xuel::SingletonOnce<Factory>::instance();
  pFac2->show();
}

void singleton()
{
  Factory *pFac = xuel::SingletonOnce<Factory>::instance();
  pFac->show();

  Factory *pFac1 = xuel::Singleton<Factory>::instance();
  pFac1->m_num = 20;
  pFac1->show();

  Factory *pFac2 = xuel::Singleton<Factory>::instance();
  pFac2->show();

  pFac->show();
}

class SingletonC11
{
public:
  static SingletonC11* instance()
  {
    static SingletonC11 inst;
    return &inst;
  }
  void show()
  {
    printf("%d\n", m_n);
  }
private:
  SingletonC11()
  {}
  int m_n;
};

int main()
{
  // singletonOnce();
  // singleton();
  SingletonC11 *pSingle = SingletonC11::instance();
  pSingle->show(); 

  return 0;
}

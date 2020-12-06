#include "../plat/Singleton.h"

#include "stdio.h"

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
  Factory *pFac = xllib::SingletonOnce<Factory>::instance();
  pFac->m_num = 10;
  pFac->show();

  Factory *pFac2 = xllib::SingletonOnce<Factory>::instance();
  pFac2->show();
}

void singleton()
{
  Factory *pFac = xllib::SingletonOnce<Factory>::instance();
  pFac->show();

  Factory *pFac1 = xllib::Singleton<Factory>::instance();
  pFac1->m_num = 20;
  pFac1->show();

  Factory *pFac2 = xllib::Singleton<Factory>::instance();
  pFac2->show();

  pFac->show();
}

int main()
{
  singletonOnce();
  singleton();
  return 0;
}

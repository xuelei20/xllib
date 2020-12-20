// use linux api
#ifndef XLLIB_CONDITION_H
#define XLLIB_CONDITION_H

#include "../comm/noncopyable.h"
#include "Mutex.h"

namespace xllib
{

class Condition : noncopyable
{
public:
  Condition()
  {
    pthread_cond_init(&m_cond, NULL);
  }

  ~Condition()
  {
    pthread_cond_destroy(&m_cond);
  }

  void wait(Mutex& mutex)
  {
    pthread_cond_wait(&m_cond, mutex.getInnerMutex());
  }

  void notify()
  {
    pthread_cond_signal(&m_cond);
  }

  void notifyAll()
  {
    pthread_cond_broadcast(&m_cond);
  }

private:
  pthread_cond_t m_cond;
};

}

#endif

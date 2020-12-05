// thread-safe
#ifndef XLLIB_COUNTDOWN_H
#define XLLIB_COUNTDOWN_H

#include "noncopyable.h"
#include "Mutex.h"
#include "Condition.h"

namespace xllib
{

class CountDown : noncopyable
{
public:
  explicit CountDown(int count) 
    : m_count(count)
  {
  }

  void wait()
  {
    MutexGuard guard(m_mutex);
    while (m_count > 0)
    {
      m_cond.wait(m_mutex); //unlock, wait for notify...lock
    }
  }

  void down()
  {
    MutexGuard guard(m_mutex);
    --m_count;
    if (0 == m_count)
    {
      m_cond.notifyAll();
    }
  }

private:
  Mutex m_mutex;
  Condition m_cond;
  int m_count;
};

}
#endif

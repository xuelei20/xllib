// thread-safe
#ifndef XLLIB_BLOCKINGQUEUE_H
#define XLLIB_BLOCKINGQUEUE_H

#include "../base/noncopyable.h"
#include "../plat/Mutex.h"
#include "../plat/Condition.h"

#include <queue>

namespace xllib
{

template<typename T>
class BlockingQueue : noncopyable
{
public:
  BlockingQueue()
  {
  }

  void put(T& data)
  {
    MutexGuard guard(m_mutex);
    m_datas.push(data);
    m_cond.notify();
  }

  T take()
  {
    MutexGuard guard(m_mutex);
    while (m_datas.empty()) // must use while, must in lock
    {
      m_cond.wait(m_mutex); // auto unlock, and if return auto lock
    }
    // must not be empty
    T data = m_datas.front();
    m_datas.pop(); // WARNING: after pop, can't use T& reference!
    return data;
  }

private:
  std::queue<T> m_datas;
  Mutex m_mutex;
  Condition m_cond;
};

}
#endif

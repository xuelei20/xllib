// thread-safe
#ifndef XUEL_BLOCKINGQUEUE_HPP
#define XUEL_BLOCKINGQUEUE_HPP

#include "noncopyable.h"

#include <mutex>
#include <condition_variable>
#include <queue>
#include <assert.h>

namespace xuel
{

template<typename T>
class BlockingQueue : noncopyable
{
public:
  void put(const T& data)
  {
    std::unique_lock<std::mutex> lock(m_mutex);
    m_datas.push(data);
    m_cond.notify_one();
  }

  T take()
  {
    std::unique_lock<std::mutex> lock(m_mutex);
    while (m_datas.empty()) // must use while, must in lock
    {
      m_cond.wait(lock); // auto unlock, and if return auto lock
    }
    assert(!m_datas.empty());
    T data(std::move(m_datas.front())); // after move, the obj data is empty. 
    m_datas.pop(); // I will not use the obj data.
    return data;
  }

private:
  std::queue<T> m_datas;
  std::mutex m_mutex;
  std::condition_variable m_cond;
};

} // namespace
#endif // XUEL_

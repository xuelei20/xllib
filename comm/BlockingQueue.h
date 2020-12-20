// thread-safe
#ifndef XUEL_BLOCKINGQUEUE_H
#define XUEL_BLOCKINGQUEUE_H

#include "noncopyable.h"

#include <mutex>
#include <condition_variable>
#include <queue>

namespace xuel
{

template<typename T>
class BlockingQueue : noncopyable
{
public:
  void put(T& data);
  T take();

private:
  std::queue<T> m_datas;
  std::mutex m_mutex;
  std::condition_variable m_cond;
};

} // namespace
#endif // XUEL_

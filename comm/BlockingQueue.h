// thread-safe
#ifndef XLLIB_BLOCKINGQUEUE_H
#define XLLIB_BLOCKINGQUEUE_H

#include "noncopyable.h"

#include <mutex>
#include <condition_variable>
#include <queue>

namespace xllib
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
#endif // XLLIB_

#include "BlockingQueue.h"

using namespace xuel;

template<typename T>
void BlockingQueue<T>::put(T& data)
{
  std::unique_lock<std::mutex> lock(m_mutex);
  m_datas.push(data);
  m_cond.notify_one();
}

template<typename T>
T BlockingQueue<T>::take()
{
  std::unique_lock<std::mutex> lock(m_mutex);
  while (m_datas.empty()) // must use while, must in lock
  {
    m_cond.wait(lock); // auto unlock, and if return auto lock
  }
  // must not be empty
  T data = m_datas.front();
  m_datas.pop(); // WARNING: after pop, can't use T& reference!
  return data;
}


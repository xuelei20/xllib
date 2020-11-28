#ifndef XLLIB_MUTEX
#define XLLIB_MUTEX

#include <mutex>

namespace xllib
{

class MutexLockGuard
{
public:
  MutexLockGuard(std::mutex &mutex)
    : m_mutex(mutex)
  {
    m_mutex.lock();
  }
  ~MutexLockGuard()
  {
    m_mutex.unlock();
  }

private:
  std::mutex &m_mutex;
};

}
#endif

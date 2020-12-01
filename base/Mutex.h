#ifndef XLLIB_MUTEX
#define XLLIB_MUTEX

#include <mutex>

namespace xllib
{

class MutexGuard
{
public:
  MutexGuard(std::mutex &mutex)
    : m_mutex(mutex)
  {
    m_mutex.lock();
  }
  ~MutexGuard()
  {
    m_mutex.unlock();
  }

private:
  std::mutex &m_mutex;
};

}
#endif

#include <mutex>

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

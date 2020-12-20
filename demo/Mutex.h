// use linux api
#ifndef XLLIB_MUTEX_H
#define XLLIB_MUTEX_H

#include "../comm/noncopyable.h"

#include <pthread.h>
#include <assert.h>

namespace xllib
{

class Mutex : noncopyable
{
public:
  Mutex()
    : m_holder(0)
  {
    pthread_mutex_init(&m_mutex, NULL);
  }

  ~Mutex()
  {
    assert(0 == m_holder);
    pthread_mutex_destroy(&m_mutex);
  }

private:
  friend class MutexGuard;
  friend class Condition;

  void lock()
  {
    pthread_mutex_lock(&m_mutex);
    // m_holder = currentThreadId(); // must later lock
  }

  void unlock()
  {
    // m_holder = 0; // must before unlock
    pthread_mutex_unlock(&m_mutex);
  }

  pthread_mutex_t* getInnerMutex()
  {
    return &m_mutex;
  }

  pthread_mutex_t m_mutex;
  pid_t m_holder;
};

class MutexGuard : noncopyable
{
public:
  explicit MutexGuard(Mutex& mutex)
    : m_mutex(mutex)
  {
    m_mutex.lock();
  }

  ~MutexGuard()
  {
    m_mutex.unlock();
  }

private:
  Mutex& m_mutex; // references
};

// Prevent misuse like:
// MutexLockGuard(mutex_);
// A tempory object doesn't hold the lock for long!
#define MutexGuard(x) error "Missing guard object name!"

}
#endif

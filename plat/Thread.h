#ifndef XLLIB_THREAD_H
#define XLLIB_THREAD_H

#include "../base/noncopyable.h"

#include <functional>

#include <pthread.h>

namespace xllib
{

void *xllibStartThread(void *arg);

class Thread : noncopyable
{
public:
  typedef std::function<void()> ThreadFunc;
  explicit Thread(ThreadFunc func, const std::string &name = "")
    : m_func(std::move(func))
    , m_name(name)
    , m_tid(0)
    , m_running(false)
  {
  }
  ~Thread()
  {
    if (m_running)
    {
      pthread_detach(m_tid);
    }
  }

  void start()
  {
    pthread_create(&m_tid, NULL, xllibStartThread, this);
  }

  int join()
  {
    int rtn = pthread_join(m_tid, NULL);
    m_running = false;
    return rtn;
  }

  void runInThread()
  {
    if (m_func)
    {
      m_func();
    }
  }

private:
  ThreadFunc m_func;
  std::string m_name;
  pthread_t m_tid;
  bool m_running;
};

void *xllibStartThread(void *arg)
{
  Thread *pthr = static_cast<Thread *>(arg);
  pthr->runInThread();
  return NULL;
}

}

#endif

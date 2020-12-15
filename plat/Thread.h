#ifndef XLLIB_THREAD_H
#define XLLIB_THREAD_H

#include "../base/noncopyable.h"
#include "../plat/xldefine.h"
#include "../plat/AtomInteger.h"

#include <functional>

#include <pthread.h>
#include <unistd.h>
#include <syscall.h>
#include <string.h>

namespace xllib
{

void *globalThreadFunc(void *arg);

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
    setDefaultName();
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
    pthread_create(&m_tid, NULL, globalThreadFunc, this);
    // printf("m_tid:%ld\n", m_tid);
  }

  int join()
  {
    int rtn = pthread_join(m_tid, NULL);
    m_running = false;
    return rtn;
  }

  // don't support stop()/suspend()/destory()/cancel(), it's not normal exit.

  void runInThread()
  {
    if (m_func)
    {
      m_func();
    }
  }

  std::string getName() const
  {
    return m_name;
  }

  // user define, using gettid(2)
  // Low efficiency, TODO: cache
  static pid_t currentThreadId()
  {
    pid_t pid = static_cast<pid_t>(syscall(SYS_gettid));
    return pid;
  }

private:
  void setDefaultName()
  {
    int num = m_num.incrementAndGet();
    if (m_name.empty())
    {
      char name[32];
      snprintf(name, sizeof(name)-1, "xllibThread%d", num);
      m_name = name;
    }
  }

private:
  ThreadFunc m_func;
  std::string m_name;
  pthread_t m_tid;
  bool m_running;
  AtomInt32 m_num;
};

void *globalThreadFunc(void *arg)
{
  Thread *pthr = static_cast<Thread *>(arg);
  XL_ASSERT(pthr != NULL);
  pthr->runInThread();
  return NULL;
}

}

#endif

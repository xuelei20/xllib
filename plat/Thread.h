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
  explicit Thread(ThreadFunc func, const std::string &name = std::string())
    : m_func(std::move(func))
    , m_name(name)
    , m_pthread(0)
    , m_running(false)
  {
    setDefaultName();
  }

  ~Thread()
  {
    if (m_running)
    {
      pthread_detach(m_pthread);
    }
  }

  void start()
  {
    pthread_create(&m_pthread, NULL, globalThreadFunc, this);
  }

  int join()
  {
    int rtn = pthread_join(m_pthread, NULL);
    m_running = false;
    printf("thread[%s] exit.\n", m_name.c_str());
    return rtn;
  }

  // don't support stop()/suspend()/destory()/cancel(), it will unnormal exit.

  void runInThread()
  {
    pid_t pid = currentThreadId();
    printf("new thread[%s], pid:%d.\n", m_name.c_str(), pid);
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
      snprintf(name, sizeof(name)-1, "xlThread%d", num);
      m_name = name;
    }
  }

private:
  ThreadFunc m_func;
  std::string m_name;
  pthread_t m_pthread;
  bool m_running;
  static AtomInt32 m_num;
};

AtomInt32 Thread::m_num;

void *globalThreadFunc(void *arg)
{
  Thread *pthr = static_cast<Thread *>(arg);
  XL_ASSERT(pthr != NULL);
  pthr->runInThread();
  return NULL;
}

}

#endif

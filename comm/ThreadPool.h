// not completed
#ifndef XLLIB_THREADPOOL_H
#define XLLIB_THREADPOOL_H

#include "../base/noncopyable.h"
#include "../plat/Thread.h"
#include "../plat/xldefine.h"
#include "BlockingQueue.h"

#include <vector>
#include <memory>

#include <unistd.h>

namespace xllib
{

class ThreadPool : noncopyable
{
public:
  typedef std::function<void()> Task;

  ThreadPool(const std::string& name = "xlThreadPool")
    : m_name(name)
    , m_threadNum(0)
    , m_running(false)
  {
  }

  void start(int threadNum)
  {
    m_threadNum = threadNum;
    XL_ASSERT(!m_running);

    m_running = true;
    for (int i=0; i<m_threadNum; ++i)
    {
      m_threads.emplace_back(new xllib::Thread(
        std::bind(&ThreadPool::doTask, this))); // WARNING: cant' in construct pass this pointer!
      m_threads[i]->start();
    }
  }

  void stop()
  {
    if (!m_running)
      return;

    m_running = false;
    for (int i=0; i<m_threadNum; ++i)
    {
      Task task = std::bind([](){});
      post(task);
    }
    for (int i=0; i<m_threadNum; ++i)
    {
      m_threads[i]->join();
    }
  }

  void post(Task func)
  {
    m_tasks.put(func);
  }

private:
  void doTask()
  {
    while (m_running)
    {
      Task func = m_tasks.take();
      if (func)
      {
        // sleep(1); // for test life time
        func();
      }
    }
  }

private:
  std::string m_name;
  int m_threadNum;
  bool m_running;
  std::vector<std::unique_ptr<xllib::Thread>> m_threads;
  xllib::BlockingQueue<Task> m_tasks;
};

} // namespace

#endif // XLLIB_

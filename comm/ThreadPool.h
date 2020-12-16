// not completed
#ifndef XLLIB_THREADPOOL_H
#define XLLIB_THREADPOOL_H

#include "../base/noncopyable.h"
// #include "../plat/Thread.h"
#include "../plat/xldefine.h"
#include "TaskQueue.h"

#include <vector>
#include <memory>
#include <iostream>
#include <thread>

#include <unistd.h>

namespace xllib
{

class ThreadPool : noncopyable
{
public:
  static ThreadPool& instance()
  {
    static ThreadPool inst;
    return inst;
  }

  void start(int threadNum)
  {
    m_threadNum = threadNum;
    XL_ASSERT(!m_running);

    m_running = true;
    for (int i=0; i<m_threadNum; ++i)
    {
      // m_threads.emplace_back(new std::thread(doWork));
      m_threads.emplace_back(new std::thread(
        &ThreadPool::doTask, this)); // WARNING: cant' in construct pass this pointer!
    }
  }

  void stop()
  {
    if (!m_running)
      return;

    m_running = false;
    for (int i=0; i<m_threadNum; ++i)
    {
      TaskQueue::Task task = std::bind([](){});
      postTask(task);
    }
    for (int i=0; i<m_threadNum; ++i)
    {
      m_threads[i]->join();
    }
  }

  void postTask(TaskQueue::Task& func)
  {
    m_tasks.put(func);
  }

private:
  ThreadPool()
    : m_threadNum(0)
    , m_running(false)
  {
  }

  void doTask()
  {
    while (m_running)
    {
      TaskQueue::Task func = m_tasks.take();
      if (func)
      {
        // sleep(1); // for test life time
        func();
      }
    }
  }

private:
  int m_threadNum;
  bool m_running;
  std::vector<std::unique_ptr<std::thread>> m_threads;
  TaskQueue m_tasks;
};

} // namespace

#endif // XLLIB_

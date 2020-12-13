// not completed
#ifndef XLLIB_THREADPOOL_H
#define XLLIB_THREADPOOL_H

#include "../base/noncopyable.h"
#include "../plat/Thread.h"
#include "../plat/xldefine.h"
#include "TaskQueue.h"

#include <vector>
#include <memory>
#include <iostream>

#include <unistd.h>

namespace xllib
{

class ThreadPool : noncopyable
{
public:
  ThreadPool(int threadNum) :
    m_threadNum(threadNum),
    m_running(false)
  {
  }
  ~ThreadPool()
  {
  }

  void start()
  {
    XL_ASSERT(!m_running);

    m_running = true;
    for (int i=0; i<m_threadNum; ++i)
    {
      // m_threads.emplace_back(new std::thread(doWork));
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
  std::vector<std::unique_ptr<xllib::Thread>> m_threads;
  TaskQueue m_tasks;
};

}

#endif

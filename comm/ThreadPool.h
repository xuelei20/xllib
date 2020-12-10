#ifndef XLLIB_THREADPOOL_H
#define XLLIB_THREADPOOL_H

#include "../base/noncopyable.h"
#include "TaskQueue.h"

#include <vector>
#include <thread>
#include <memory>
#include <iostream>

namespace xllib
{

void doWork()
{
  std::cout << "doWork" << std::endl;
}

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
    if (m_running)
      return;

    m_running = true;
    for (int i=0; i<m_threadNum; ++i)
    {
      // m_threads.emplace_back(new std::thread(doWork));
      m_threads.emplace_back(new std::thread(&ThreadPool::doTask, this)); // WARNING: cant' in construct pass this pointer!
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
      func();
    }
  }

private:
  int m_threadNum;
  bool m_running;
  std::vector<std::unique_ptr<std::thread>> m_threads;
  TaskQueue m_tasks;
};

}

#endif

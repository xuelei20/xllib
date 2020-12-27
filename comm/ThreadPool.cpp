#include "ThreadPool.h"
#include "xldefine.h"

using namespace xuel;

ThreadPool::ThreadPool(const std::string& name)
  : m_name(name)
  , m_threadNum(0)
  , m_running(false)
{
}

void ThreadPool::start(int threadNum)
{
  m_threadNum = threadNum;
  XL_ASSERT(!m_running);

  m_running = true;
  for (int i=0; i<m_threadNum; ++i)
  {
    m_threads.emplace_back(new std::thread(
      &ThreadPool::doTask, this)); // WARNING: cant' in construct pass this pointer!
  }
}

void ThreadPool::stop()
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

void ThreadPool::post(Task func)
{
  m_tasks.put(func);
}

void ThreadPool::doTask()
{
  printf("new thread(pid:%d)\n", xuel::CurrentThread::getpid());
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

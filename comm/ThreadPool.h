// not completed
#ifndef XUEL_THREADPOOL_H
#define XUEL_THREADPOOL_H

#include "noncopyable.h"
#include "BlockingQueue.hpp"
#include "CurrentThread.h"

#include <vector>
#include <memory>
#include <thread>
#include <functional>
// #include <atomic>

namespace xuel
{

class ThreadPool : noncopyable
{
public:
  typedef std::function<void()> Task;

  ThreadPool(const std::string& name = "xlThreadPool");

  void start(int threadNum);
  
  void stop();
  
  void post(Task func);
  
private:
  void doTask();

  std::string m_name;
  int m_threadNum;
  bool m_running;
  std::vector<std::unique_ptr<std::thread>> m_threads;
  xuel::BlockingQueue<Task> m_tasks;
};

} // namespace

#endif // XUEL_

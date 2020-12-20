// not completed
#ifndef XLLIB_THREADPOOL_H
#define XLLIB_THREADPOOL_H

#include "noncopyable.h"
#include "BlockingQueue.h"
#include "CurrentThread.h"

#include <vector>
#include <memory>
#include <thread>
#include <functional>
// #include <atomic>

namespace xllib
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
  xllib::BlockingQueue<Task> m_tasks;
};

} // namespace

#endif // XLLIB_

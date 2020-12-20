#ifndef XLLIB_TASKQUEUE_H
#define XLLIB_TASKQUEUE_H

#include "../comm/noncopyable.h"
#include "../comm/BlockingQueue.h"

#include <functional>

namespace xllib
{

class TaskQueue : noncopyable
{
public:
  typedef std::function<void()> Task;
  void put(Task& func)
  {
    m_taskQueue.put(func);
  }

  Task take()
  {
    return m_taskQueue.take();
  }

private:
  BlockingQueue<Task> m_taskQueue;
};

}
#endif

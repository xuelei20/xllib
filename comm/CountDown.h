// thread-safe
#ifndef XLLIB_COUNTDOWN_H
#define XLLIB_COUNTDOWN_H

#include "noncopyable.h"

#include <mutex>
#include <condition_variable>

namespace xllib
{

class CountDown : noncopyable
{
public:
  explicit CountDown(int count);

  void wait();

  void down();

private:
  std::mutex m_mutex;
  std::condition_variable m_cond;
  int m_count;
};

}
#endif

#include "CountDown.h"

using namespace xllib;

CountDown::CountDown(int count) 
  : m_count(count)
{
}

void CountDown::wait()
{
  std::unique_lock<std::mutex> lock(m_mutex);
  while (m_count > 0)
  {
    m_cond.wait(lock); //unlock, wait for notify...lock
  }
}

void CountDown::down()
{
  std::unique_lock<std::mutex> lock(m_mutex);
  --m_count;
  if (0 == m_count)
  {
    m_cond.notify_all();
  }
}

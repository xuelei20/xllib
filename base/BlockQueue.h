#include <queue>
#include <mutex>
#include <condition_variable>

namespace xllib
{

template<typename T>
class BlockQueue
{
public:
  void enqueue(T &data)
  {
    std::unique_lock<std::mutex> ulock(m_mutex);
    m_datas.push(data);
    m_cond.notify_one();
  }

  T &dequeue()
  {
    std::unique_lock<std::mutex> ulock(m_mutex);
    while (m_datas.empty()) // must use while, must in lock
    {
      m_cond.wait(ulock); // auto unlock, and if return auto lock
    }
    T &data = m_datas.front();
    m_datas.pop();
    return data;
  }

private:
  std::queue<T> m_datas;
  std::mutex m_mutex;
  std::condition_variable m_cond;
};

}

// list some way
#ifndef XLLIB_SINGLETON_H
#define XLLIB_SINGLETON_H

#include "../base/noncopyable.h"
#include "Mutex.h"

namespace xllib
{

// verison1: thread-unsafe
class SingletonSimple : noncopyable
{
public:
  static SingletonSimple* instance()
  {
    if (0 == m_instance)
    {
      m_instance = new SingletonSimple();
    }
    return m_instance;
  }

private:
  SingletonSimple(); // must be private
  ~SingletonSimple();

  static SingletonSimple* m_instance;
};
SingletonSimple* SingletonSimple::m_instance = 0;

// version2: use template, and thread-safe
template<typename T>
class SingletonT
{
public:
  static T* instance()
  {
    MutexGuard guard(m_mutex); // every time will lock, ineffective.
    if (0 == m_data)
    {
      m_data = new T();
    }
    return m_data;
  }

private:
  static Mutex m_mutex;
  static T* m_data;
};
template<typename T>
T* SingletonT<T>::m_data = 0;

// version3: double checked locking(DCL). unreliable!
template<typename T>
class SingletonDCL
{
public:
  static T* instance()
  {
    if (0 == m_data)
    {
      MutexGuard guard(m_mutex); 
      if (0 == m_data)
      {
        m_data = new T(); // condition-race problem!
      }
      return m_data;
    }
  }

private:
  static Mutex m_mutex;
  static T* m_data;
};
template<typename T>
T* SingletonDCL<T>::m_data = 0;

// https://www.jianshu.com/p/d9334d992cbe?utm_campaign=maleskine&utm_content=note&utm_medium=seo_notes&utm_source=recommendation
// version4: use memory barrier

// version5: pthread_once (before c++11)
class SingletonOnce
{
};

}

#endif

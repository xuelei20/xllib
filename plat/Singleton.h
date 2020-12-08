// list some way
#ifndef XLLIB_SINGLETON_H
#define XLLIB_SINGLETON_H

#include "../base/noncopyable.h"
#include "Mutex.h"

namespace xllib
{

// verison1: thread-unsafe. not ok
class SingletonSimple : noncopyable
{
public:
  static SingletonSimple* instance()
  {
    if (0 == m_data)
    {
      m_data = new SingletonSimple();
    }
    return m_data;
  }

private:
  SingletonSimple(); // must be private
  ~SingletonSimple();

  static SingletonSimple* m_data;
};
SingletonSimple* SingletonSimple::m_data = 0;

// version2: use template, and thread-safe. ok but ineffective
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

// version3: double checked locking(DCL). unreliable! wrong
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

// version5: pthread_once (before c++11). ok
template<typename T>
class SingletonOnce
{
public:
  static T* instance()
  {
    pthread_once(&m_once, &init); // the "init" function only execute once.
    return m_data;
  }

private:
  // SingletonOnce(); // useless
  // ~SingletonOnce();

  static void init()
  {
    m_data = new T;
  }

  static T* m_data;
  static pthread_once_t m_once;
};
template<typename T>
T* SingletonOnce<T>::m_data = 0;

template<typename T>
pthread_once_t SingletonOnce<T>::m_once = PTHREAD_ONCE_INIT;

// version6: c++11. ok
template<typename T>
class Singleton
{
public:
  static T* instance()
  {
    static T data; // thread-safe?
    return &data;
  }
};

// version7: c++11, reference. ok
template<typename T>
class SingletonRef
{
public:
  static T& instance()
  {
    static T data;
    return data;
  }
};

}

#endif

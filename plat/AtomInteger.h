#ifndef XLLIB_ATOMINTEGER_H
#define XLLIB_ATOMINTEGER_H

#include "../base/noncopyable.h"

#include <stdint.h>

namespace xllib
{

template<typename T>
class AtomInteger : noncopyable
{
public:
  AtomInteger()
    : m_value(0)
  {
  }

  void set(T n)
  {
    __sync_lock_test_and_set(&m_value, n);
  }

  T get()
  {
    return __sync_val_compare_and_swap(&m_value, 0, 0);
  }

  T getAndAdd(T n)
  {
    return __sync_fetch_and_add(&m_value, n);
  }

  T addAndGet(T n)
  {
    return __sync_add_and_fetch(&m_value, n);
  }

  T incrementAndGet()
  {
    return addAndGet(1);
  }

  T derementAndGet()
  {
    return addAndGet(-1);
  }

private:
  T m_value;
};

typedef AtomInteger<int32_t> AtomInt32;
typedef AtomInteger<int64_t> AtomInt64;

}

#endif

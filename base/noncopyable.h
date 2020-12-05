#ifndef XLLIB_NONCOPYABLE_H
#define XLLIB_NONCOPYABLE_H

namespace xllib
{
  
class noncopyable
{
public:
  noncopyable(const noncopyable&) = delete;
  void operator=(const noncopyable&) = delete;

protected:
  noncopyable() = default;
  ~noncopyable() = default;
};

}

#endif

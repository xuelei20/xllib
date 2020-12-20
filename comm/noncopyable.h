#ifndef XUEL_NONCOPYABLE_H
#define XUEL_NONCOPYABLE_H

namespace xuel
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

} // namespace

#endif // XUEL_

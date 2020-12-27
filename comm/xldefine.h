#ifndef XL_DEFINE_H
#define XL_DEFINE_H

#include <assert.h>

#define XL_STRNCPY(szDest, szSource) \
{ \
  memset((szDest), 0, sizeof(szDest)); \
  strncpy((szDest), (szSource), sizeof(szDest) - 1); \
}

// TODO: multi platform
#define XL_ASSERT(expr) \
  assert(expr)

#endif

#ifndef XLDEFINE_H
#define XLDEFINE_H

#include <assert.h>

#define XL_STRNCPY(szDest, szSource) \
{ \
memset((szDest), 0, sizeof(szDest)); \
strncpy((szDest), (szSource), sizeof(szDest) - 1); \
}

#define XL_ASSERT(expr) \
{ \
assert(expr); \
}

#endif

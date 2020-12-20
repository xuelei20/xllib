#ifndef XLDEFINE_H
#define XLDEFINE_H

#define XL_STRNCPY(szDest, szSource) \
{ \
memset((szDest), 0, sizeof(szDest)); \
strncpy((szDest), (szSource), sizeof(szDest) - 1); \
}

#endif

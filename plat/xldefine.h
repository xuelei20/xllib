
#define XL_STRNCPY(szDest, szSource) \
{ \
memset((szDest), 0, sizeof(szDest)); \
strncpy((szDest), (szSource), sizeof(szDest) - 1); \
}

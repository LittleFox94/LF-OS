#ifndef _STRING_H_INCLUDED
#define _STRING_H_INCLUDED

#include <stdint.h>

#ifdef __cplusplus
extern "C"
{
#endif

void *memcpy(char *dest, const char *src, size_t size);

int strcmp(const char *s1, const char *s2);

int strlen(const char* s);

void *memset(void *dest, int val, size_t n);

#ifdef __cplusplus
}
#endif

#endif

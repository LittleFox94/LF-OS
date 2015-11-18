#include <string.h>

extern "C"
{
    void *memcpy(char *dest, const char *src, size_t size)
    {
        while(size > 0)
        {
            *dest = *src;
            dest++;
            src++;
            size--;
        }

        return dest;
    }

    int strcmp(const char*a, const char*b)
    {
        while(*a == *b && *a)
        {
            a++;
            ++b;
        }
        return *(const unsigned char*)a - *(const unsigned char*)b;
    }

    int strlen(const char* s)
    {
        int i = 0;
        while(*s) {
            s++;
            i++;
        }

        return i;
    }

    void *memset(void *dest, int val, size_t n)
    {
        for(size_t i = 0; i < n; i++)
        {
            *((char*)dest) = (char)val;
            dest = (void*)((uint32_t)dest + i);
        }

        return dest;
    }
}

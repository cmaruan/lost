#include <string.h>

char*
strcpy(char* dest, const char* src)
{
        size_t len = strlen(src);
        return memcpy(dest, src, len);
}
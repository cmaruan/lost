#ifndef _STDIO_H
#define _STDIO_H 1

#include <stdarg.h>
#include <sys/cdefs.h>

#define EOF (-1)

#ifdef __cplusplus
extern "C" {
#endif
int putchar(int);
int puts(const char *);

int printf(const char *__restrict fmt, ...);
int sprintf(char *, const char *__restrict fmt, ...);
int vprintf(char *, const char *__restrict fmt, va_list ap);
int svprintf(char *, const char *__restrict fmt, va_list ap);

#ifdef __cplusplus
}
#endif

#endif

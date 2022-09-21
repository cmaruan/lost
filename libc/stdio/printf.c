#include <limits.h>
#include <stdarg.h>
#include <stdbool.h>
#include <stdio.h>
#include <string.h>

static bool
print(const char *data, size_t length)
{
        const unsigned char *bytes = (const unsigned char *)data;
        for (size_t i = 0; i < length; i++)
                if (putchar(bytes[i]) == EOF)
                        return false;
        return true;
}

int
svprintf(char *buffer, const char *__restrict fmt, va_list ap)
{
        char *b = buffer;
        size_t size;
        const char *str;
        for (const char *p = fmt; *p != '\0'; p++) {
                if (*p != '%') {
                        *b++ = *p;
                        continue;
                }
                p++;
                switch (*p) {
                case 's':  // %s: string
                        str = va_arg(ap, const char *);
                        size = strlen(str);
                        strcpy(b, str);
                        b += size;
                        break;
                default:
                        strcpy(b, "** unknown format: X **");
                        b += 23;
                        b[-4] = *p;
                }
        }
        *b = '\0';
        return b - buffer;
}

int
printf(const char *restrict format, ...)
{
        va_list parameters;
        va_start(parameters, format);
        char buffer[1024];
        int written = svprintf(buffer, format, parameters);
        print(buffer, strlen(buffer));

        // while (*format != '\0') {
        //         size_t maxrem = INT_MAX - written;

        //         if (format[0] != '%' || format[1] == '%') {
        //                 if (format[0] == '%')
        //                         format++;
        //                 size_t amount = 1;
        //                 while (format[amount] && format[amount] != '%')
        //                         amount++;
        //                 if (maxrem < amount) {
        //                         // TODO: Set errno to EOVERFLOW.
        //                         return -1;
        //                 }
        //                 if (!print(format, amount))
        //                         return -1;
        //                 format += amount;
        //                 written += amount;
        //                 continue;
        //         }

        //         const char *format_begun_at = format++;

        //         if (*format == 'c') {
        //                 format++;
        //                 char c = (char)va_arg(parameters,
        //                                       int /* char promotes to int
        //                                       */);
        //                 if (!maxrem) {
        //                         // TODO: Set errno to EOVERFLOW.
        //                         return -1;
        //                 }
        //                 if (!print(&c, sizeof(c)))
        //                         return -1;
        //                 written++;
        //         }
        //         else if (*format == 's') {
        //                 format++;
        //                 const char *str = va_arg(parameters, const char *);
        //                 size_t len = strlen(str);
        //                 if (maxrem < len) {
        //                         // TODO: Set errno to EOVERFLOW.
        //                         return -1;
        //                 }
        //                 if (!print(str, len))
        //                         return -1;
        //                 written += len;
        //         }
        //         else {
        //                 format = format_begun_at;
        //                 size_t len = strlen(format);
        //                 if (maxrem < len) {
        //                         // TODO: Set errno to EOVERFLOW.
        //                         return -1;
        //                 }
        //                 if (!print(format, len))
        //                         return -1;
        //                 written += len;
        //                 format += len;
        //         }
        // }

        va_end(parameters);
        return written;
}

#include <kernel/tty.h>
#include <stddef.h>
#include <stdio.h>

size_t
loop_for(size_t max)
{
        volatile size_t count = 0;
        while (count < max) count++;
        return count;
}

char *
strfill(char *str, size_t n, char c)
{
        for (size_t i = 0; i < n; i++) {
                str[i] = c;
        }
        return str;
}

void
kernel_main(void)
{
        /* Initialize terminal interface */
        tty_initialize();
        printf("         Welcome to LOST           \n");
        printf("::: Learn Operting System Today :::\n");
        printf("-----------------------------------\n");
        printf("[K] Hello <%s>\n", "kernel");
        char buff[80];
        for (size_t i = 0; i < 10; i++) {
                strfill(buff, 80, 'a' + i);
                tty_write(buff, 80);
                loop_for(100000000ULL);
        }
}
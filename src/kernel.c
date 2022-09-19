#include "kernel.h"

#include "string.h"
#include "vga.h"

void vga_term_writes(const char *str) {
    // Write c string to vga terminal
    vga_term_write(str, strlen(str));
}

size_t loop_for(size_t max) {
    volatile size_t count = 0;
    while (count < max) count++;
    return count;
}

char *strfill(char *str, size_t n, char c) {
    for (size_t i = 0; i < n; i++) str[i] = c;
    return str;
}

void kernel_main(void) {
    /* Initialize terminal interface */
    vga_term_init();

    vga_term_writes("         Welcome to LOST           \n");
    vga_term_writes("::: Learn Operting System Today :::\n");
    vga_term_writes("-----------------------------------\n");
    char buff[80];
    for (size_t i = 0; i < 10; i++) {
        strfill(buff, 80, 'a' + i);
        vga_term_write(buff, 80);
        // vga_term_writes("\n");
        loop_for(100000000ULL);
    }
}
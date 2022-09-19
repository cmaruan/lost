#include "kernel.h"

#include "kio.h"

size_t strlen(const char *str) {
    size_t len = 0;
    for (; str[len]; len++)
        ;
    return len;
}

void vga_term_writes(const char *str) { vga_term_write(str, strlen(str)); }

void kernel_main(void) {
    /* Initialize terminal interface */
    vga_term_init();

    vga_term_writes("         Welcome to LOST           \n");
    vga_term_writes("::: Learn Operting System Today :::\n");
    vga_term_writes("-----------------------------------\n");
    vga_term_writes("$ ");
}
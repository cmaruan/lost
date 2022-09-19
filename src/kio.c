#include "kio.h"
struct vga_terminal {
    size_t cursor_row;
    size_t cursor_column;
    uint8_t color;
    uint16_t *buffer;
};

#define VGA_MEMORY_ADDRESS 0xB8000
#define VGA_WIDTH 80
#define VGA_HEIGHT 25

static struct vga_terminal s_terminal;

// Private API
static inline uint8_t s_vga_entry_color(enum vga_color fg, enum vga_color bg) {
    return fg | bg << 4;
}

static inline uint16_t s_vga_entry(unsigned char uc, uint8_t color) {
    return (uint16_t)uc | (uint16_t)color << 8;
}
static inline void s_vga_term_put_entry_at(char c, uint8_t color, size_t x,
                                           size_t y) {
    size_t index = y * VGA_WIDTH + x;
    s_terminal.buffer[index] = s_vga_entry(c, color);
}
static inline void s_vga_term_advance_cursor() {
    if (++s_terminal.cursor_column == VGA_WIDTH) {
        s_terminal.cursor_column = 0;
        if (++s_terminal.cursor_row == VGA_HEIGHT) {
            s_terminal.cursor_row = 0;
        }
    }
}
// Public API
void vga_term_init() {
    s_terminal.buffer = (uint16_t *)VGA_MEMORY_ADDRESS;
    s_terminal.cursor_column = 0;
    s_terminal.cursor_row = 0;
    if (s_terminal.color == 0) {
        s_terminal.color =
            s_vga_entry_color(VGA_COLOR_LIGHT_GREY, VGA_COLOR_BLACK);
    }
    for (size_t i = 0; i < VGA_WIDTH * VGA_HEIGHT; i++) {
        s_terminal.buffer[i] = s_vga_entry(' ', s_terminal.color);
    }
}
void vga_term_putchar(char c) {
    if (c == '\n') {
        s_terminal.cursor_column = 0;
        s_terminal.cursor_row++;
    } else {
        s_vga_term_put_entry_at(c, s_terminal.color, s_terminal.cursor_column,
                                s_terminal.cursor_row);
        s_vga_term_advance_cursor();
    }
}
void vga_term_write(const char *string, size_t size) {
    for (size_t i = 0; i < size; i++) {
        vga_term_putchar(string[i]);
    }
}
void vga_term_set_color(enum vga_color foreground, enum vga_color background) {
    s_terminal.color = s_vga_entry_color(foreground, background);
}

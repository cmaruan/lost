HOST=i686-elf

AR=$(HOST)-ar
AS=$(HOST)-as
CC=$(HOST)-gcc

GRUBFILE=/opt/grub/usr/local/bin/grub-file
GRUBMKRESCUE=/opt/grub/usr/local/bin/grub-mkrescue

CFLAGS=-O2 -g
CPPFLAGS=

# Configure the cross-compiler to use the desired system root.
SYSROOT="$(shell pwd)/sysroot"
CC+=--sysroot=$(SYSROOT)



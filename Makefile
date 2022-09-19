
CC=i686-elf-gcc
AS=i686-elf-as 
GRUBFILE=/opt/grub/usr/local/bin/grub-file
GRUBMKRESCUE=/opt/grub/usr/local/bin/grub-mkrescue
PWD=$(shell pwd)
INCLUDE=include/
CFLAGS=-std=gnu99 -ffreestanding -O0 -Wall -Wextra -I$(INCLUDE)

OBJS=$(patsubst %.c,%.o,$(wildcard src/*.c))

boot.o: src/boot.s
	$(AS) src/boot.s -o boot.o 

%.o: src/%.c
	$(CC) -c $< -o $@ $(CFLAGS)

lost.bin: boot.o $(OBJS)
	$(CC) -T linker.ld -o lost.bin -ffreestanding -O2 -nostdlib boot.o $(OBJS) -lgcc

clean:
	rm -rf *.o 
	rm -rf src/*.o
	rm -rf lost.*


run: lost.bin
	qemu-system-i386 -kernel lost.bin


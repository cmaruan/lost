
CC=i686-elf-gcc
AS=i686-elf-as 
GRUBFILE=/opt/grub/usr/local/bin/grub-file
GRUBMKRESCUE=/opt/grub/usr/local/bin/grub-mkrescue
PWD=$(shell pwd)
INCLUDE=include/
CFLAGS=-std=gnu99 -ffreestanding -O2 -Wall -Wextra -I$(INCLUDE)

boot.o: src/boot.s
	$(AS) src/boot.s -o boot.o 

kio.o: src/kio.c
	$(CC) -c src/kio.c -o kio.o $(CFLAGS)

kernel.o: src/kernel.c 
	$(CC) -c src/kernel.c -o kernel.o $(CFLAGS)

lost.bin: boot.o kernel.o linker.ld kio.o
	$(CC) -T linker.ld -o lost.bin -ffreestanding -O2 -nostdlib boot.o kernel.o kio.o -lgcc



run: lost.bin
	qemu-system-i386 -kernel lost.bin


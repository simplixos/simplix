##################################
#	BasicOS Kernel Makefile
##################################

CC=../cross/os-toolchain/bin/i686-elf-gcc
AS=nasm

INCLUDE=include/
CFLAGS=-std=gnu99 -I$(INCLUDE) -ffreestanding -nostdlib -O2 -Wall -Wextra
ASFLAGS=-felf
LDFLAGS=-T linker.ld

CSOURCES= ./kernel/common.c ./kernel/vga.c ./kernel/gdt.c ./kernel/page.c ./kernel/kernel.c
ASMSOURCES= ./kernel/boot.s

COBJECTS=$(CSOURCES:.c=.o)
ASMOBJECTS=$(ASMSOURCES:.s=.o)

KERNEL=basicos.bin

all: $(CSOURCES) $(ASMSOURCES) $(KERNEL)

$(KERNEL): $(COBJECTS) $(ASMOBJECTS)
	$(CC) $(LDFLAGS) $(CFLAGS) $(COBJECTS) $(ASMOBJECTS) -o $@

.cpp.o:
	$(CC) $(CFLAGS) $< -o $@

.s.o:
	$(AS) $(ASFLAGS)  $< -o $@

clean:
	rm -f $(COBJECTS) $(ASMOBJECTS) $(KERNEL) ../basicos.iso


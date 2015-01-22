###############################################################################
#	BasicOS Kernel Makefile						      #
#									      #
# 	License:							      #
#	BasicOS Operating System - An experimental operating system	      #
#	Copyright (C) 2015 Aun-Ali Zaidi				      #
#									      #
#	This program is free software: you can redistribute it and/or modify  #
#	it under the terms of the GNU General Public License as published by  #
#	the Free Software Foundation, either version 3 of the License, or     #
#	(at your option) any later version.				      #
#									      #
#	This program is distributed in the hope that it will be useful,	      #
#	but WITHOUT ANY WARRANTY; without even the implied warranty of	      #
#	MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the	      #
#	GNU General Public License for more details.			      #
#									      #
#	You should have received a copy of the GNU General Public License     #
#	along with this program. If not, see <http://www.gnu.org/licenses/>.  #
###############################################################################

CC=../cross/os-toolchain/bin/i686-elf-gcc
AS=nasm

INCLUDE=include/
CFLAGS=-std=gnu99 -I$(INCLUDE) -ffreestanding -nostdlib -O2 -Wall -Wextra
ASFLAGS=-felf
LDFLAGS=-T linker.ld

CSOURCES= ./kernel/common.c ./kernel/vga.c ./kernel/gdt.c ./kernel/idt.c ./kernel/irq.c ./kernel/int.c ./kernel/page.c ./kernel/kernel.c
ASMSOURCES= ./kernel/boot.s ./kernel/idt_asm.s ./kernel/isr.s

COBJECTS=$(CSOURCES:.c=.o)
ASMOBJECTS=$(ASMSOURCES:.s=.o)

KERNEL=basicos.bin

all: $(CSOURCES) $(ASMSOURCES) $(KERNEL)

$(KERNEL): $(COBJECTS) $(ASMOBJECTS)
	$(CC) $(LDFLAGS) $(CFLAGS) $(ASMOBJECTS) $(COBJECTS) -o $@

.cpp.o:
	$(CC) $(CFLAGS) $< -o $@

.s.o:
	$(AS) $(ASFLAGS)  $< -o $@

clean:
	rm -f $(COBJECTS) $(ASMOBJECTS) $(KERNEL) ../basicos.iso


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
AS=../cross/os-toolchain/bin/nasm

INCLUDE=include/
LIBDIR=sysroot/lib/
CFLAGS=-m32 -std=gnu99 -I$(INCLUDE) -L$(LIBDIR) $(LIBS) -ffreestanding -nostdlib -O2 -Wall -Wextra
ASFLAGS=-felf32
LDFLAGS=-T linker.ld

CFLAGS_DEV=-g -std=gnu99 -I$(INCLUDE) -L$(LIBDIR) $(LIBS) -ffreestanding -nostdlib -O2 -Wall -Wextra
ASFLAGS_DEV=-g -felf32

CSOURCES= ./kernel/arch/x86/io.c ./kernel/common.c ./kernel/vga.c ./kernel/arch/x86/tty.c ./kernel/sample.c ./kernel/arch/x86/gdt.c ./kernel/arch/x86/idt.c ./kernel/arch/x86/panic.c ./kernel/arch/x86/irq.c ./kernel/arch/x86/int.c ./kernel/arch/x86/page.c ./hw/cpu/cpuid.c ./kernel/kernel.c
ASMSOURCES= ./kernel/arch/x86/boot.s ./kernel/arch/x86/idt_asm.s ./kernel/arch/x86/isr.s ./kernel/test.s
LIBS=

COBJECTS=$(CSOURCES:.c=.o)
ASMOBJECTS=$(ASMSOURCES:.s=.o)

CSOURCES_DEV= ./kernel/arch/x86/io.c ./kernel/common.c ./kernel/vga.c ./kernel/arch/x86/tty.c ./kernel/sample.c ./kernel/arch/x86/gdt.c ./kernel/arch/x86/idt.c ./kernel/arch/x86/panic.c ./kernel/arch/x86/irq.c ./kernel/arch/x86/int.c ./kernel/arch/x86/page.c ./hw/cpu/cpuid.c ./kernel/kernel.c
ASMSOURCES_DEV= ./kernel/arch/x86/boot.s ./kernel/arch/x86/idt_asm.s ./kernel/arch/x86/isr.s ./kernel/test.s

COBJECTS_DEV=$(CSOURCES_DEV:.c=.od)
ASMOBJECTS_DEV=$(ASMSOURCES_DEV:.s=.sod)

KERNEL_DEV=basicosdev.bin
KERNEL_STABLE=basicosstable.bin

all: dev stable

dev: $(CSOURCES) $(ASMSOURCES) $(KERNEL_DEV)

stable: $(CSOURCES) $(ASMSOURCES) $(KERNEL_STABLE)

$(KERNEL_DEV): $(COBJECTS_DEV) $(ASMOBJECTS_DEV)
	$(CC) $(LDFLAGS) $(CFLAGS_DEV) $(ASMOBJECTS_DEV) $(COBJECTS_DEV) -o $@

$(KERNEL_STABLE): $(COBJECTS) $(ASMOBJECTS)
	rm -f basicosstable.bin
	$(CC) $(LDFLAGS) $(CFLAGS) $(ASMOBJECTS) $(COBJECTS) -o $@

%.s.o: %.s
	$(AS) $(ASFLAGS)  $< -o $@

%.od: %.c
	$(CC) $(CFLAGS_DEV) -c $< -o $@

%.sod: %.s
	$(AS) $(ASFLAGS_DEV)  $< -o $@

clean:
	rm -f $(COBJECTS) $(ASMOBJECTS) $(COBJECTS_DEV) $(ASMOBJECTS_DEV) $(KERNEL_DEV) ../basicos.iso


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
STRIP=../cross/os-toolchain/bin/i686-elf-strip

INCLUDE=include/
LIBDIR=sysroot/lib/
OBJ_DIR=obj
BIN_DIR=../bin

CFLAGS=-m32 -std=gnu99 -I$(INCLUDE) -L$(LIBDIR) $(LIBS) -ffreestanding -nostdlib -O2 -Wall -Wextra
ASFLAGS=-felf32
LDFLAGS=-T linker.ld

CFLAGS_DEV=-g -std=gnu99 -I$(INCLUDE) -L$(LIBDIR) $(LIBS) -ffreestanding -nostdlib -O2 -Wall -Wextra
ASFLAGS_DEV=-g -felf32

ifeq ($(ARCH),x86)
CSOURCES= 	kernel/arch/x86/io.c \
		kernel/common.c \
		kernel/vga.c \
		kernel/arch/x86/tty.c \
		kernel/sample.c \
		kernel/arch/x86/gdt.c \
		kernel/arch/x86/idt.c \
		kernel/arch/x86/panic.c \
		kernel/arch/x86/irq.c \
		kernel/arch/x86/int.c \
		kernel/arch/x86/page.c \
		hw/cpu/cpuid.c \
		kernel/kernel.c	\

ASMSOURCES= 	kernel/arch/x86/boot.s \
		kernel/arch/x86/idt_asm.s \
		kernel/arch/x86/isr.s \
		kernel/test.s	\

else ifeq ($(ARCH),x86_64) #64 bit support
CSOURCES= 	kernel/arch/x86_64/io.c \
		kernel/common.c kernel/vga.c \
		kernel/arch/x86_64/tty.c \
		kernel/sample.c \
		kernel/arch/x86_64/gdt.c \
		kernel/arch/x86_64/idt.c \
		kernel/arch/x86_64/panic.c \
		kernel/arch/x86_64/irq.c \
		kernel/arch/x86_64/int.c \
		kernel/arch/x86_64/page.c \
		hw/cpu/cpuid.c \
		kernel/kernel.c	\

ASMSOURCES= 	kernel/arch/x86_64/boot.s \
		kernel/arch/x86_64/idt_asm.s \
		kernel/arch/x86_64/isr.s \
		kernel/test.s	\
else #not come here
endif

ifeq ($(ARCH),x86)
CSOURCES_DEV= 	kernel/arch/x86/io.c \
		kernel/common.c \
		kernel/vga.c \
		kernel/arch/x86/tty.c \
		kernel/sample.c \
		kernel/arch/x86/gdt.c \
		kernel/arch/x86/idt.c \
		kernel/arch/x86/panic.c \
		kernel/arch/x86/irq.c \
		kernel/arch/x86/int.c \
		kernel/arch/x86/page.c \
		hw/cpu/cpuid.c \
		kernel/kernel.c	\

ASMSOURCES_DEV= kernel/arch/x86/boot.s \
		kernel/arch/x86/idt_asm.s \
		kernel/arch/x86/isr.s \
		kernel/test.s	\

else ifeq ($(ARCH),x86_64) #64 bit support
CSOURCES_DEV= 	kernel/arch/x86_64/io.c \
		kernel/common.c kernel/vga.c \
		kernel/arch/x86_64/tty.c \
		kernel/sample.c \
		kernel/arch/x86_64/gdt.c \
		kernel/arch/x86_64/idt.c \
		kernel/arch/x86_64/panic.c \
		kernel/arch/x86_64/irq.c \
		kernel/arch/x86_64/int.c \
		kernel/arch/x86_64/page.c \
		hw/cpu/cpuid.c \
		kernel/kernel.c	\

ASMSOURCES_DEV= kernel/arch/x86_64/boot.s \
		kernel/arch/x86_64/idt_asm.s \
		kernel/arch/x86_64/isr.s \
		kernel/test.s	\
else #not come here
endif

KERNEL_DEV=$(BIN_DIR)/basicosdev.bin
KERNEL_STABLE=$(BIN_DIR)/basicosstable.bin


COBJECTS_DEV = $(patsubst %.c,obj/%.od,$(CSOURCES_DEV)) # developer objects named with .od extension
ASMOBJECTS_DEV = $(patsubst %.s,obj/%.sod,$(ASMSOURCES_DEV))# developer ASM objects named with .sod extension

COBJECTS = $(patsubst %.c,obj/%.os,$(CSOURCES)) # stable objects named with .os extension
ASMOBJECTS = $(patsubst %.s,obj/%.sos,$(ASMSOURCES))# stable ASM objects named with .os extension

$(COBJECTS_DEV): | obj
$(ASMOBJECTS_DEV): | obj
obj:
	@mkdir -p $@

$(COBJECTS): | obj
$(ASMOBJECTS): | obj
obj:
	@mkdir -p $@


all: dev stable

dev: $(CSOURCES) $(ASMSOURCES) $(KERNEL_DEV)

stable: $(CSOURCES) $(ASMSOURCES) $(KERNEL_STABLE)

$(KERNEL_DEV): $(COBJECTS_DEV) $(ASMOBJECTS_DEV)
	$(CC) $(LDFLAGS) $(CFLAGS_DEV) $(ASMOBJECTS_DEV) $(COBJECTS_DEV) -o $@

$(KERNEL_STABLE): $(COBJECTS) $(ASMOBJECTS)
	rm -f $(KERNEL_STABLE)
	$(CC) $(LDFLAGS) $(CFLAGS) $(ASMOBJECTS) $(COBJECTS) -o $@
	$(STRIP) -s -g -v $(KERNEL_STABLE)

obj/%.os: %.c
	@mkdir -p $(@D)
	$(CC) $(CFLAGS) -c $< -o $@

obj/%.sos: %.s
	@mkdir -p $(@D)
	$(AS) $(ASFLAGS)  $< -o $@

obj/%.od: %.c
	@mkdir -p $(@D)
	$(CC) $(CFLAGS_DEV) -c $< -o $@

obj/%.sod: %.s
	@mkdir -p $(@D)
	$(AS) $(ASFLAGS_DEV)  $< -o $@

clean:
	rm -f $(COBJECTS) $(ASMOBJECTS) $(COBJECTS_DEV) $(ASMOBJECTS_DEV) $(KERNEL_DEV) $(BIN_DIR)/basicosdev.bin \
	$(BIN_DIR)/basicosstable.bin $(BIN_DIR)/basicos.iso


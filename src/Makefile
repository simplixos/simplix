###############################################################################
#	SimplixOS Kernel Makefile					      #
#									      #
# 	License:							      #
#	SimplixOS Operating System - An experimental operating system	      #
#	Copyright (C) 2015 Aun-Ali Zaidi and its contributors.		      #
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

ifndef ARCH
$(error ARCH is not defined! Exiting!)
endif

CC=../cross/os-toolchain/bin/i686-simplix-gcc
AS=../cross/os-toolchain/bin/nasm
STRIP=../cross/os-toolchain/bin/i686-simplix-strip

INCLUDE=include/
INC_LIBC_DIR=lib/libc/include/
INC_LIBPOSIX_DIR=lib/libposix/include/

LIBDIR=lib/bin/
LIBS=-lc -lposix

OBJ_DIR=obj
BIN_DIR=../bin

LIBC_DIR=lib/libc
LIBPOSIX_DIR=lib/libposix

CFLAGS=-m32 -std=gnu99 -I$(INCLUDE) -I$(INC_LIBC_DIR) -I$(INC_LIBPOSIX_DIR) -L$(LIBDIR) $(LIBS) -ffreestanding -nostdlib -O2 -Wall -Wextra -fstack-protector-all -D_bos_k_libc
ASFLAGS=-felf32
# Architecture specific linker file. Specified in kernel/arch/$(ARCH)/linker-$(ARCH).ld
LDFLAGS=-T $(LINK_SPEC)

CFLAGS_DBG=-g -std=gnu99 -I$(INCLUDE) -I$(INC_LIBC_DIR) -I$(INC_LIBPOSIX_DIR) -L$(LIBDIR) $(LIBS) -ffreestanding -nostdlib -O2 -Wall -Wextra -fstack-protector-all -D_bos_k_libc
ASFLAGS_DBG=-g -felf32

include kernel/Makefile.inc
include kernel/arch/x86/Makefile.inc
include hw/Makefile.inc

CSOURCES_DBG=$(CSOURCES)
ASMSOURCES_DBG=$(ASMSOURCES)

ifeq ($(TESTS),1)
CFLAGS+= -DTESTS
CFLAGS_DBG+= -DTESTS
endif

KERNEL_DBG=$(BIN_DIR)/simplixos_dbg.bin
KERNEL_STABLE=$(BIN_DIR)/simplixos_stable.bin

COBJECTS_DBG = $(patsubst %.c,obj/%.od,$(CSOURCES_DBG)) # debug objects named with .od extension
ASMOBJECTS_DBG = $(patsubst %.s,obj/%.sod,$(ASMSOURCES_DBG))# debug ASM objects named with .sod extension

COBJECTS = $(patsubst %.c,obj/%.os,$(CSOURCES)) # stable objects named with .os extension
ASMOBJECTS = $(patsubst %.s,obj/%.sos,$(ASMSOURCES))# stable ASM objects named with .sos extension

# add static libs here and provide a rule below
LIBC=$(LIBDIR)libc.a
LIBPOSIX=$(LIBDIR)libposix.a

$(COBJECTS_DBG): | obj
$(ASMOBJECTS_DBG): | obj
obj::
	@test -d $@ || mkdir $@

$(COBJECTS): | obj
$(ASMOBJECTS): | obj
obj::
	@test -d $@ || mkdir $@

all: debug stable

debug: $(CSOURCES) $(ASMSOURCES) $(KERNEL_DBG)

stable: $(CSOURCES) $(ASMSOURCES) $(KERNEL_STABLE)

$(KERNEL_DBG): $(COBJECTS_DBG) $(ASMOBJECTS_DBG) $(LIBC) $(LIBPOSIX)
	$(CC) $(LDFLAGS) $(CFLAGS_DBG) $(ASMOBJECTS_DBG) $(COBJECTS_DBG) $(LIBC) $(LIBPOSIX) -o $@

$(KERNEL_STABLE): $(COBJECTS) $(ASMOBJECTS) $(LIBC) $(LIBPOSIX)
	rm -f $(KERNEL_STABLE)
	$(CC) $(LDFLAGS) $(CFLAGS) $(ASMOBJECTS) $(COBJECTS) $(LIBC) $(LIBPOSIX) -o $@
	$(STRIP) -s -g -v $(KERNEL_STABLE)

obj/%.os: %.c
	@mkdir -p $(@D)
	$(CC) $(CFLAGS) -c $< -o $@

obj/%.sos: %.s
	@mkdir -p $(@D)
	$(AS) $(ASFLAGS)  $< -o $@

obj/%.od: %.c
	@mkdir -p $(@D)
	$(CC) $(CFLAGS_DBG) -c $< -o $@

obj/%.sod: %.s
	@mkdir -p $(@D)
	$(AS) $(ASFLAGS_DBG)  $< -o $@

$(LIBC):
	@cd $(LIBC_DIR) && $(MAKE) all

$(LIBPOSIX):
	@cd $(LIBPOSIX_DIR) && $(MAKE) all

clean:
	@cd $(LIBC_DIR) && $(MAKE) clean
	@cd $(LIBPOSIX_DIR) && $(MAKE) clean
	rm -rf $(COBJECTS) $(ASMOBJECTS) $(KERNEL_STABLE) $(COBJECTS_DBG) $(ASMOBJECTS_DBG) $(KERNEL_DBG) $(OBJ_DIR) $(BIN_DIR)

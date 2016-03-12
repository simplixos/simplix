###############################################################################
#	SimplixOS Kernel Makefile					      #
#									      #
# 	License:							      #
#	SimplixOS Operating System - An experimental operating system	      #
#	Copyright (C) 2016 Aun-Ali Zaidi and its contributors.		      #
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

# Verbosity Control
# TODO: Change it to support the use of different verbosity flags.
ifdef V
cmd = $1
else
cmd = @$(if $(value 2),echo "$2";)$1
endif

CC=../cross/os-toolchain/bin/i686-simplix-gcc
AS=../cross/os-toolchain/bin/nasm
STRIP=../cross/os-toolchain/bin/i686-simplix-strip
OBJCOPY=../cross/os-toolchain/bin/i686-simplix-objcopy
MV=mv

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
	$(call cmd, \
	$(CC) $(LDFLAGS) $(CFLAGS_DBG) $(ASMOBJECTS_DBG) $(COBJECTS_DBG) $(LIBC) $(LIBPOSIX) -o $@, \
	CC 	$(KERNEL_DBG))
	$(call cmd, \
	$(OBJCOPY) --add-section .copyright=../scripts/copyright --set-section-flags .copyright=noload $(KERNEL_DBG) $(KERNEL_DBG)1, \
	OBJCOPY $(KERNEL_DBG) $(KERNEL_DBG)1)
	$(call cmd, \
	$(MV) $(KERNEL_DBG)1 $(KERNEL_DBG), \
	MV	$(KERNEL_DBG)1 $(KERNEL_DBG))

$(KERNEL_STABLE): $(COBJECTS) $(ASMOBJECTS) $(LIBC) $(LIBPOSIX)
	$(call cmd, \
	rm -f $(KERNEL_STABLE), \
	RM 	$(KERNEL_STABLE))
	$(call cmd, \
	$(CC) $(LDFLAGS) $(CFLAGS) $(ASMOBJECTS) $(COBJECTS) $(LIBC) $(LIBPOSIX) -o $@, \
	CC 	$(KERNEL_STABLE))
	$(call cmd, \
	$(OBJCOPY) --add-section .copyright=../scripts/copyright --set-section-flags .copyright=noload $(KERNEL_STABLE) $(KERNEL_STABLE)1, \
	OBJCOPY $(KERNEL_STABLE) $(KERNEL_STABLE)1)
	$(call cmd, \
	$(MV) $(KERNEL_STABLE)1 $(KERNEL_STABLE), \
	MV	$(KERNEL_STABLE)1 $(KERNEL_STABLE))
	$(call cmd, \
	$(STRIP) $(KERNEL_STABLE), \
	STRIP  $(KERNEL_STABLE))

obj/%.os: %.c
	@mkdir -p $(@D)
	$(call cmd, \
	$(CC) $(CFLAGS) -c $< -o $@, \
	CC 	$<)

obj/%.sos: %.s
	@mkdir -p $(@D)
	$(call cmd, \
	$(AS) $(ASFLAGS)  $< -o $@, \
	AS 	$<)

obj/%.od: %.c
	@mkdir -p $(@D)
	$(call cmd, \
	$(CC) $(CFLAGS_DBG) -c $< -o $@, \
	CC 	$<)

obj/%.sod: %.s
	@mkdir -p $(@D)
	$(call cmd, \
	$(AS) $(ASFLAGS_DBG)  $< -o $@, \
	AS 	$<)

$(LIBC):
	@echo "Building libc:"
	@cd $(LIBC_DIR) && $(MAKE) all V=$(V)

$(LIBPOSIX):
	@echo "Building libposix:"
	@cd $(LIBPOSIX_DIR) && $(MAKE) all V=$(V)

clean:
	@cd $(LIBC_DIR) && $(MAKE) clean
	@cd $(LIBPOSIX_DIR) && $(MAKE) clean
	$(call cmd, \
	rm -rf $(COBJECTS) $(ASMOBJECTS) $(KERNEL_STABLE) $(COBJECTS_DBG) $(ASMOBJECTS_DBG) $(KERNEL_DBG) $(OBJ_DIR) $(BIN_DIR), \
	CLEAN kernel/ hw/cpuid/ ../bin/)

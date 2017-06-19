###############################################################################
#	SimplixOS Kernel Makefile					      #
#									      #
#	License:							      #
#	SimplixOS Operating System - An experimental operating system	      #
#	Copyright (C) 2015-17 Aun-Ali Zaidi and its contributors.	      #
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

#--------------------------------#
#       Included Makefiles       #
#--------------------------------#

include kernel/Makefile.inc
include kernel/arch/x86/Makefile.inc

#----------------------------------#
#        Makefile Variables        #
#----------------------------------#

## Directories ##

BASE_DIR = $(CURDIR)/
BINARY_DIR = $(BASE_DIR)../bin
INCLUDE_DIR = $(BASE_DIR)include
LIBRARY_DIR = $(BASE_DIR)lib
LIBRARY_BIN_DIR = $(LIBRARY_DIR)/bin
OBJECT_DIR = $(BASE_DIR)obj
SCRIPT_DIR= $(BASE_DIR)../scripts

LIBC_DIR = $(LIBRARY_DIR)/libc
LIBC_BIN = $(LIBRARY_BIN_DIR)/libc.a
INCLUDE_LIBC_DIR = $(LIBRARY_DIR)/libc/include

LIBPOSIX_DIR = $(LIBRARY_DIR)/libposix
LIBPOSIX_BIN = $(LIBRARY_BIN_DIR)/libposix.a
INCLUDE_LIBPOSIX_DIR = $(LIBRARY_DIR)/libposix/include

## Tools ##

CC=$(BASE_DIR)../cross/os-toolchain/bin/i686-simplix-gcc
AS=$(BASE_DIR)../cross/os-toolchain/bin/nasm
LD=$(BASE_DIR)../cross/os-toolchain/bin/i686-simplix-ld
STRIP=$(BASE_DIR)../cross/os-toolchain/bin/i686-simplix-strip
OBJCOPY=$(BASE_DIR)../cross/os-toolchain/bin/i686-simplix-objcopy
MV=mv

## Flags ##

CFLAGS_BASE	= -std=gnu99 -ffreestanding -nostdlib -fstack-protector-all
CFLAGS_DEFS	+= -D_simplix_k_libc -D_BUILD_TIME_=$(shell date "+%s")
CFLAGS_INC	= -I$(INCLUDE_DIR) -I$(INCLUDE_LIBC_DIR) -I$(INCLUDE_LIBPOSIX_DIR)
CFLAGS_LIBS	= -L$(LIBRARY_BIN_DIR) -lc -lposix
CFLAGS_OPT	= -O2
CFLAGS_WARN	= -Wall -Wextra

ifeq ($(TESTS),1)
CFLAGS_DEFS += -DTESTS
endif

CFLAGS = $(CFLAGS_OPT) $(CFLAGS_INC) $(CFLAGS_BASE) $(CFLAGS_WARN) $(CFLAGS_DEFS)
CFLAGS_DEBUG = -g $(CFLAGS)

ASFLAGS = -felf32
ASFLAGS_DEBUG = -g $(ASFLAGS)

# Architecture specific linker file.
LINK_SPEC = $(BASE_DIR)kernel/arch/$(ARCH)/linker-$(ARCH).ld
LDFLAGS = -T $(LINK_SPEC)

OBJFLAGS = --add-section .copyright=$(SCRIPT_DIR)/copyright --set-section-flags .copyright=noload

#---------------------------------#
#       Sources and Objects       #
#---------------------------------#

CSOURCES_DEBUG = $(CSOURCES)
ASMSOURCES_DEBUG = $(ASMSOURCES)

KERNEL_DEBUG = $(BINARY_DIR)/simplixos_dbg.bin
KERNEL_STABLE = $(BINARY_DIR)/simplixos_stable.bin

# Debug objects named with .od extension
COBJECTS_DEBUG = $(patsubst %.c,obj/%.od,$(CSOURCES_DEBUG))
ASMOBJECTS_DEBUG = $(patsubst %.s,obj/%.sod,$(ASMSOURCES_DEBUG))# debug ASM objects named with .sod extension

COBJECTS = $(patsubst %.c,obj/%.os,$(CSOURCES)) # stable objects named with .os extension
ASMOBJECTS = $(patsubst %.s,obj/%.sos,$(ASMSOURCES))# stable ASM objects named with .sos extension

$(COBJECTS): | obj
$(ASMOBJECTS): | obj
obj::
	@test -d $@ || mkdir $@

$(COBJECTS_DEBUG): | obj
$(ASMOBJECTS_DEBUG): | obj
obj::
	@test -d $@ || mkdir $@

#--------------------------------#
#             Targets            #
#--------------------------------#

all: stable debug

stable: $(ASMSOURCES) $(CSOURCES) $(KERNEL_STABLE)

debug: $(ASMSOURCES) $(CSOURCES) $(KERNEL_DEBUG)

$(KERNEL_STABLE): $(ASMOBJECTS) $(COBJECTS) $(LIBC_BIN) $(LIBPOSIX_BIN)
	$(call cmd, \
	$(LD) $(LDFLAGS) $(ASMOBJECTS) $(COBJECTS) $(LIBC_BIN) $(LIBPOSIX_BIN) -o $@, \
	LD      $(subst $(BASE_DIR),,$(KERNEL_STABLE)))
	$(call cmd, \
	$(OBJCOPY) $(OBJFLAGS) $(KERNEL_STABLE) $(KERNEL_STABLE), \
	OBJCOPY $(subst $(BASE_DIR),,$(KERNEL_STABLE)))
	$(call cmd, \
	$(STRIP) $(KERNEL_STABLE), \
	STRIP   $(subst $(BASE_DIR),,$(KERNEL_STABLE)))

$(KERNEL_DBG): $(ASMOBJECTS_DBG) $(COBJECTS_DBG) $(LIBC) $(LIBPOSIX)
	$(call cmd, \
	$(LD) $(LDFLAGS) $(ASMOBJECTS_DBG) $(COBJECTS_DBG) $(LIBC) $(LIBPOSIX) -o $@, \
	LD      $(subst $(BASE_DIR),,$(KERNEL_DBG)))
	$(call cmd, \
	$(OBJCOPY) $(OBJFLAGS) $(KERNEL_DBG) $(KERNEL_DBG), \
	OBJCOPY $(subst $(BASE_DIR),,$(KERNEL_DBG)))

obj/%.os: %.c
	@mkdir -p $(@D)
	$(call cmd, \
	$(CC) $(CFLAGS) -c $< -o $@, \
	CC      $(subst obj/,,$@))

obj/%.sos: %.s
	@mkdir -p $(@D)
	$(call cmd, \
	$(AS) $(ASFLAGS)  $< -o $@, \
	AS      $(subst obj/,,$@))

obj/%.od: %.c
	@mkdir -p $(@D)
	$(call cmd, \
	$(CC) $(CFLAGS_DBG) -c $< -o $@, \
	CC      $(subst obj/,,$@))

obj/%.sod: %.s
	@mkdir -p $(@D)
	$(call cmd, \
	$(AS) $(ASFLAGS_DBG)  $< -o $@, \
	AS      $(subst obj/,,$@))

$(LIBC_BIN):
	@echo "Building libc:"
	@cd $(LIBC_DIR) && $(MAKE) all V=$(V)

$(LIBPOSIX_BIN):
	@echo "Building libposix:"
	@cd $(LIBPOSIX_DIR) && $(MAKE) all V=$(V)

clean:
	@cd $(LIBC_DIR) && $(MAKE) clean
	@cd $(LIBPOSIX_DIR) && $(MAKE) clean
	$(call cmd, \
	rm -rf $(COBJECTS) $(ASMOBJECTS) $(KERNEL_STABLE) $(COBJECTS_DBG) $(ASMOBJECTS_DBG) $(KERNEL_DBG) $(OBJ_DIR) $(BIN_DIR), \
	CLEAN   kernel/ hw/cpuid/ ../bin/)

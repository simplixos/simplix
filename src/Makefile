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

ifeq ($(DEBUG),1)
CFLAGS += -g
endif

ASFLAGS = -felf32

ifeq ($(DEBUG),1)
ASFLAGS += -g
endif

# Architecture specific linker file.
LINK_SPEC = $(BASE_DIR)kernel/arch/$(ARCH)/linker-$(ARCH).ld
LDFLAGS = -T $(LINK_SPEC)

OBJFLAGS = --add-section .copyright=$(SCRIPT_DIR)/copyright --set-section-flags .copyright=noload

#---------------------------------#
#       Sources and Objects       #
#---------------------------------#

KERNEL = $(BINARY_DIR)/simplixos_kernel.bin

KERNEL_COBJECTS = $(patsubst %.c,obj/%.o,$(KERNEL_CSOURCES)) # C objects named with .o extension
KERNEL_ASMOBJECTS = $(patsubst %.s,obj/%.so,$(KERNEL_ASMSOURCES)) # ASM objects named with .so extension

$(KERNEL_COBJECTS): | obj
$(KERNEL_ASMOBJECTS): | obj
obj::
	@test -d $@ || mkdir $@

#--------------------------------#
#             Targets            #
#--------------------------------#

all: kernel

kernel: $(KERNEL_ASMSOURCES) $(KERNEL_CSOURCES) $(KERNEL)

$(KERNEL): $(KERNEL_ASMOBJECTS) $(KERNEL_COBJECTS) $(LIBC_BIN) $(LIBPOSIX_BIN)
	$(call cmd, \
	$(LD) $(LDFLAGS) $(KERNEL_ASMOBJECTS) $(KERNEL_COBJECTS) $(LIBC_BIN) $(LIBPOSIX_BIN) -o $@, \
	LD      $(subst $(BASE_DIR),,$(KERNEL)))
	$(call cmd, \
	$(OBJCOPY) $(OBJFLAGS) $(KERNEL) $(KERNEL), \
	OBJCOPY $(subst $(BASE_DIR),,$(KERNEL)))
	$(call cmd, \
	$(STRIP) $(KERNEL), \
	STRIP   $(subst $(BASE_DIR),,$(KERNEL)))

obj/%.o: %.c
	@mkdir -p $(@D)
	$(call cmd, \
	$(CC) $(CFLAGS) -c $< -o $@, \
	CC      $(subst obj/,,$@))

obj/%.so: %.s
	@mkdir -p $(@D)
	$(call cmd, \
	$(AS) $(ASFLAGS)  $< -o $@, \
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
	rm -rf $(KERNEL_COBJECTS) $(KERNEL_ASMOBJECTS) $(KERNEL) $(OBJ_DIR) $(BIN_DIR), \
	CLEAN   kernel/ hw/cpuid/ ../bin/)

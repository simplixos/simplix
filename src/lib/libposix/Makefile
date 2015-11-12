###############################################################################
#       SimplixOS Kernel LibPOSIX Makefile                                    #
#                                                                             #
#       License:                                                              #
#       SimplixOS Operating System - An experimental operating system         #
#       Copyright (C) 2015 Aun-Ali Zaidi and its contributors.                #
#                                                                             #
#       This program is free software: you can redistribute it and/or modify  #
#       it under the terms of the GNU General Public License as published by  #
#       the Free Software Foundation, either version 3 of the License, or     #
#       (at your option) any later version.                                   #
#                                                                             #
#       This program is distributed in the hope that it will be useful,       #
#       but WITHOUT ANY WARRANTY; without even the implied warranty of        #
#       MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the          #
#       GNU General Public License for more details.                          #
#                                                                             #
#       You should have received a copy of the GNU General Public License     #
#       along with this program. If not, see <http://www.gnu.org/licenses/>.  #
###############################################################################

CC=../../../cross/os-toolchain/bin/i686-simplix-gcc
AR=../../../cross/os-toolchain/bin/i686-simplix-ar
RANLIB=../../../cross/os-toolchain/bin/i686-simplix-ranlib

LIBC_DIR=../lib/
LIBC_INC_DIR=../libc/include/
LIBS=-lc

INC_DIR=include/
OS_INC_DIR=../../include/

CFLAGS=-O2 -std=gnu99 -L$(LIBK_DIR) $(LIBS) -ffreestanding -fbuiltin -Wall -Wextra -I$(INC_DIR) -I$(LIBC_INC_DIR) -I$(OS_INC_DIR) -D__bos_libk -I../../include

SOURCES= src/_uname.c \

OBJDIR=obj/
BIN_DIR=../bin

OBJS = $(patsubst %.c,obj/%.libposix.o,$(SOURCES)) # objects named with .a extension

$(OBJS): | obj

# TODO: Need to find a better way
obj:
	@test -d $@ || mkdir $@

BIN=libposix.a

#FIXME : dev and stable support

all: $(SOURCES) $(BIN)

$(BIN): $(OBJS)
	$(AR) rcsv $@ $(OBJS)
	@test -d $(BIN_DIR) || mkdir $(BIN_DIR)
	$(RANLIB) $(BIN)
	@cp $(BIN) $(BIN_DIR)/

obj/%.libposix.o: %.c
	@test -d $(@D) || mkdir $(@D)
	$(CC) -c $< -o $@ $(CFLAGS)

clean:
	rm -rf $(OBJS) $(OBJDIR)$(BIN) $(OBJDIR) $(BIN_DIR)/$(BIN) $(BIN)

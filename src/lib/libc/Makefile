###############################################################################
#       BasicOS Kernel LibC Makefile                                          #
#                                                                             #
#       License:                                                              #
#       BasicOS Operating System - An experimental operating system           #
#       Copyright (C) 2015 Aun-Ali Zaidi and its contributors                 #
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

include src/stdio/Makefile.obj
include src/stdlib/Makefile.obj
include src/string/Makefile.obj

CC=../../../cross/os-toolchain/bin/i686-elf-gcc
AR=../../../cross/os-toolchain/bin/i686-elf-ar
RANLIB=../../../cross/os-toolchain/bin/i686-elf-ranlib

INC_DIR=include/
OS_INC_DIR=../../include/

CFLAGS=-O2 -std=gnu99 -ffreestanding -nostdlib -fbuiltin -Wall -Wextra -I$(OS_INC_DIR) -I$(INC_DIR) -D_x86 -I../../include

OBJDIR=obj/
BIN_DIR=../bin

OBJS = $(patsubst %.c,obj/%.libc.o,$(SOURCES)) # objects named with .a extension

$(OBJS): | obj

obj:
	@test -d $@ || mkdir $@
	@mkdir obj/src

BIN=libc.a

#FIXME : dev and stable support

all: $(SOURCES) $(BIN)

$(BIN): $(OBJS)
	$(AR) rcsv $@ $(OBJS)
	@test -d $(BIN_DIR) || mkdir $(BIN_DIR)
	$(RANLIB) $(BIN)
	@cp $(BIN) $(BIN_DIR)/

obj/%.libc.o: %.c
	@test -d $(@D) || mkdir $(@D)
	$(CC) -c $< -o $@ $(CFLAGS)

clean:
	rm -rf $(OBJS) $(OBJDIR)$(BIN) $(OBJDIR) $(BIN_DIR)/$(BIN)

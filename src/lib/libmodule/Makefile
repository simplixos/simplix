###############################################################################
#       BasicOS Kernel LibModule Makefile                                     #
#                                                                             #
#       License:                                                              #
#       BasicOS Operating System - An experimental operating system           #
#       Copyright (C) 2015 Aun-Ali Zaidi                                      #
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

LIBDIR=../libk/obj/
LIBS=-lk

CFLAGS=-O2 -std=gnu99 -L$(LIBDIR) $(LIBS) -ffreestanding -fbuiltin -Wall -Wextra -D__bos_libk -I../include

SOURCES=./src/modloader.c \
	./src/mod_elf.c

OBJDIR=obj

OBJS = $(patsubst %.c,obj/%.libmod.o,$(SOURCES)) # objects named with .a extension
$(OBJS): | obj

obj:
	@mkdir -p $@

BIN=obj/libmod.a

#FIXME : dev and stable support

all: $(BIN)

$(BIN): $(OBJS) $(BIN)
	$(AR) rcsv $@ $(OBJS)
	#cp $(BIN) $(OBJDIR)/$(BIN)

obj/%.libmod.o: %.c
	@mkdir -p $(@D)
	$(CC) -c $< -o $@ $(CFLAGS)

clean:
	rm -rf $(OBJS) $(BIN) $(OBJDIR)/$(BIN) $(OBJDIR)

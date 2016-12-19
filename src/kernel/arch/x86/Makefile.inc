###############################################################################
#       SimplixOS Kernel kernel/arch/x86/ Subdir Makefile                     #
#                                                                             #
#       License:                                                              #
#       SimplixOS Operating System - An experimental operating system         #
#       Copyright (C) 2016 Aun-Ali Zaidi and its contributors.                #
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

ifeq ($(ARCH),x86)
LINK_SPEC=kernel/arch/x86/linker-x86.ld

CFLAGS+= -D_x86
CFLAGS_DBG+= -D_x86

CSOURCES+=	kernel/arch/x86/x86_init.c \
		kernel/arch/x86/io.c \
		kernel/arch/x86/tty.c \
		kernel/arch/x86/gdt.c \
		kernel/arch/x86/idt.c \
		kernel/arch/x86/panic.c \
		kernel/arch/x86/irq.c \
		kernel/arch/x86/int.c \
		kernel/arch/x86/page.c \
		kernel/arch/x86/serial.c \
		kernel/arch/x86/phy_allocator.c \
		kernel/arch/x86/symtab.c \
		kernel/arch/x86/phy_page_alloc_test.c

ASMSOURCES+=	kernel/arch/x86/boot.s \
		kernel/arch/x86/idt_asm.s \
		kernel/arch/x86/isr.s
endif

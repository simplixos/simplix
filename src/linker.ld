/***********************************************************************
 * BasicOS Operating System
 * 
 * File: linker.ld
 * 
 * Description:
 * 	Script used to link the BasicOS kernel.
 * 
 * License:
 * BasicOS Operating System - An experimental operating system.
 * Copyright (C) 2015 Aun-Ali Zaidi
 *
 * This program is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the
 * GNU General Public License for more details.
 * 
 * You should have received a copy of the GNU General Public License
 * along with this program. If not, see <http://www.gnu.org/licenses/>.
 * 
 ***********************************************************************/

OUTPUT_FORMAT("elf32-i386")
OUTPUT_ARCH(i386)
ENTRY(start)

SECTIONS
{
        . = 0x100000;

        .setup :
        {
                *(.setup)
        }

        . += 0xC0000000;

        .text : AT(ADDR(.text) - 0xC0000000)
        {
                *(.text)
        }

        .data ALIGN (4096) : AT(ADDR(.data) - 0xC0000000)
        {
                *(.data)
                *(.rodata*)
        }

        .bss ALIGN (4096) : AT(ADDR(.bss) - 0xC0000000)
        {
                *(COMMON*)
                *(.bss*)
        }
}

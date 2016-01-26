/***********************************************************************
 * SimplixOS Operating System
 *
 * File: include/bos/k/arch/x86/gdt.h
 *
 * Description:
 * 	Defines GDT constants and related structs.
 *
 * License:
 * SimplixOS Operating System - An experimental operating system.
 * Copyright (C) 2016 Aun-Ali Zaidi and its contributors.
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

#ifndef GDT_H
#define GDT_H

#include <bos/k/common.h>
#include <bos/k/vga.h>

/** GDT Pointer Structures **/

// Defines the structures of a GDT entry and of a GDT pointer
struct gdt_entry
{
	unsigned short limit_low;
	unsigned short base_low;
	unsigned char base_middle;
	unsigned char access;
	unsigned char granularity;
	unsigned char base_high;
} __attribute__((packed));

struct gdt_ptr
{
	unsigned short limit;
	unsigned int base;
} __attribute__((packed));

// We'll need at least 3 entries in our GDT...

struct gdt_entry gdt[5];
struct gdt_ptr gp;

/** GDT Functions **/

// Very simple: fills a GDT entry using the parameters
void gdt_set_gate(int num, unsigned long base, unsigned long limit, uint8_t access, uint8_t gran);

// Sets 5 gates and installs the real GDT through the assembler function
void gdt_install();

// ExASM: Flushes changes to the GDT.
void gdt_flush();

#endif // GDT_H

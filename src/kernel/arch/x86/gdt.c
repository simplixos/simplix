/***********************************************************************
 * SimplixOS Operating System
 *
 * File: kernel/arch/x86/gdt.c
 *
 * Description:
 * 	Functions that manage and setup the GDT.
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

#include <bos/k/arch/x86/gdt.h>

// Very simple: fills a GDT entry using the parameters
void gdt_set_gate(int num, unsigned long base, unsigned long limit, unsigned char access, unsigned char gran)
{
        gdt[num].base_low = (base & 0xFFFF);
        gdt[num].base_middle = (base >> 16) & 0xFF;
        gdt[num].base_high = (base >> 24) & 0xFF;

        gdt[num].limit_low = (limit & 0xFFFF);
        gdt[num].granularity = ((limit >> 16) & 0x0F);

        gdt[num].granularity |= (gran & 0xF0);
        gdt[num].access = access;
}

// Sets our 5 gates and installs the real GDT through the assembler function
void gdt_install()
{
        gp.limit = (sizeof(struct gdt_entry) * 5) - 1;
        gp.base = (unsigned int)&gdt;

        gdt_set_gate(0, 0, 0, 0, 0);		    // Null sgment
        gdt_set_gate(1, 0, 0xFFFFFFFF, 0x9A, 0xCF); // Code Segment
        gdt_set_gate(2, 0, 0xFFFFFFFF, 0x92, 0xCF); // Data Segment
        gdt_set_gate(3, 0, 0xFFFFFFFF, 0xFA, 0xCF); // User mode code segment
	gdt_set_gate(4, 0, 0xFFFFFFFF, 0xF2, 0xCF); // User mode data segment

        gdt_flush();
}

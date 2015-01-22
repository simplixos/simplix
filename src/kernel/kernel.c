/***********************************************************************
 * BasicOS Operating System
 * 
 * File: kernel/kernel.c
 * 
 * Description:
 * 	This is the entry point for the main kernel.
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

#include <sys/common.h>
#include <sys/vga.h>
#include <sys/gdt.h>
#include <sys/idt.h>
#include <sys/int.h>
#include <sys/irq.h>
#include <sys/page.h>
#include <bas/defs.h>

// Our kernel's first function: kmain
void kmain()
{
	// FIRST enable paging and THEN load the real GDT!
        init_paging();
        gdt_install();
	idt_init();
	irq_init();

	// Interrupt tests
	//int_enable();
	//int_nmi_enable();
	//asm volatile ("int $0x3");

        // Clear the screen
        vga_clear();
        
        // Print logo
        vga_write(ASCII_LOGO);
        
        // Display build an authoring info
        vga_write("BasicOS ver. "BAS_VER_FUL"\n");
	vga_write(AUTHOR_NOTE"\n");
	vga_write(COMPILE_NOTE"\n\n");
		
	// Print a warm welcome!
        vga_write("Hello, User!");
        
        // Hang up the computer
        for (;;);
}

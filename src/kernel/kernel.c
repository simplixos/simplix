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

#include <bos/k/common.h>
#include <bos/k/vga.h>
#include <bos/k/defs.h>

#ifdef _x86
#include <bos/k/arch/x86/gdt.h>
#include <bos/k/arch/x86/idt.h>
#include <bos/k/arch/x86/int.h>
#include <bos/k/arch/x86/irq.h>
#include <bos/k/arch/x86/page.h>
#include <bos/k/arch/x86/panic.h>
#include <bos/k/arch/x86/serial.h>
#else
#endif

#include <hw/cpuid.h>
#include <bos/k/sample.h>

void _k_early()
{
	// FIRST enable paging and THEN load the real GDT!
        init_paging();
        gdt_install();
        idt_init();
        irq_init();

	// Clear the screen
        vga_clear();

	// Enable Interrupts
        int_enable();
        int_nmi_enable();

	// Interrupt test
        //asm volatile ("int $0x3");
}

// Our kernel's first function: kmain
void _k_main()
{
	tty_init();
	serial_init();

	// Print logo
        vga_write(ASCII_LOGO);

        // Display build an authoring info
        vga_write("BasicOS ver. "BAS_VER_FUL"\n");
        vga_write(AUTHOR_NOTE"\n");
        vga_write(COMPILE_NOTE"\n\n");

	// Display CPU info
	cpu_info();

	// Print a warm welcome!
        vga_write("Hello, User!");

	// BUGGED - Run PI test!
	//sample_pi();

	// Fake kernel Panic
	_k_panic("[LOLZ] Just A test! ;)");

        // Hang up the computer
        for (;;);
}

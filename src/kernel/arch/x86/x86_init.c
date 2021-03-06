/***********************************************************************
 * SimplixOS Operating System
 *
 * File: kernel/arch/x86/x86_init.c
 *
 * Description:
 * 	x86 initialization code.
 *
 * License:
 * SimplixOS Operating System - An experimental operating system.
 * Copyright (C) 2015-17 Aun-Ali Zaidi and its contributors.
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

#include <simplix/k/arch/x86/x86.h>
#include <simplix/k/defs.h>

#ifdef _x86
	#include <simplix/k/arch/x86/serial.h>
	#include <simplix/k/arch/x86/phy_alloc.h>
#else
#endif

/** x86 Specific Initialization Code, init_x86.
 *
 * This section is called from the _k_early function in
 * kernel/kernel.c and initializes the x86 cpu.
 *
 */
void arch_init(multiboot_info_t* mbd, unsigned long lmagic)
{
	// Initialise TTY and Serial devices
	//tty_init();
	serial_init();

	// FIRST enable paging and THEN load the real GDT!
	init_paging();
	gdt_install();

	// Initialize Interrupt Descriptor Tables and Interrupt Request Handler
	idt_init();
	irq_init();

	// Enable Interrupts
	int_enable();
	int_nmi_enable();

	// Print Logo
	kprintf(ASCII_LOGO);

	// Display build and authoring info
	vga_write("SimplixOS ver. "SIMPLIX_VER_FUL"\n");
	vga_write(AUTHOR_NOTE"\n");
	vga_write(COMPILE_NOTE"\n\n");

	// Map our physical space
	page_map_init(mbd, lmagic);
}

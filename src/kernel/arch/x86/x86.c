/***********************************************************************
 * BasicOS Operating System
 *
 * File: kernel/arch/x86/x86.c
 *
 * Description:
 *      x86 specific code.
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

#include <bos/k/arch/x86/x86.h>

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

void init_x86()
{
	// Initialise TTY and Serial devices
	tty_init();
	serial_init();	

	// FIRST enable paging and THEN load the real GDT!
        init_paging();
        gdt_install();
        
	// Initialize Interrupt Descriptor Tables and Interrupt Request Handler
	idt_init();
        irq_init();

        // Clear the screen
        vga_clear();

        // Enable Interrupts
        int_enable();
        int_nmi_enable();
}

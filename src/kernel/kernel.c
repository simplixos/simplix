/***********************************************************************
 * SimplixOS Operating System
 *
 * File: kernel/kernel.c
 *
 * Description:
 * 	This is the entry point for the main kernel.
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

#include <simplix/k/common.h>
#include <simplix/k/vga.h>
#include <simplix/k/defs.h>

#include <simplix/k/arch/interface.h>

#include <stdio.h>

/** The Kernel's Early Entrpoint function, kearly.
 *
 * This section is called within the initial trampoline/boot
 * assembly after the initial bootup process. It then
 * continues the setup by setting up CPU-specific features.
 *
 * @param mbd 	 Pointer to Multiboot info passed on by GRUB2
 * @param lmagic Pointer to Multiboot Magic flag
 */
void _k_early(multiboot_info_t* mbd, unsigned long lmagic)
{
	// Initialize the CPU.
	arch_init(mbd, lmagic);
}

/** The Kernel's Main Entrypoint function, kmain.
 *
 * This function is called right after the exiting of the kearly
 * function. It is the kernel's main loop which then probes for
 * devices, loads any kernel extensions, switches to usermode,
 * calls init_servers to initialize the servers, and calls
 * the SysV init daemon.
 *
 */
void _k_main(void)
{
	// Print a warm welcome!
	kprintf("Hello, User!\n");

	#ifdef TESTS
		kprintf("\nSystem Tests: \n\n");

		// Physical Memory Allocator Test
		start_phy_alloc_test();
	#endif

	// Fake kernel Panic
	//_k_panic("[LOLZ] Just A test! ;)", __FILE__, __LINE__);

	// Hang up the computer
	for (;;) ;
}

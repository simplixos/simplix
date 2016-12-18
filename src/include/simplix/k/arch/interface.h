/***********************************************************************
 * SimplixOS Operating System
 *
 * File: include/simplix/k/arch/interface.h
 *
 * Description:
 * 	Generic interface between kernel and architecture specific
 *	code.
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

#ifndef ARCH_INTERFACE_H
#define ARCH_INTERFACE_H

#include <simplix/k/arch/multiboot.h>

/* Function Prototypes */

/** Architecture Initialization Function
 *
 * This function serves as the entrypoint of the
 * CPU architecture and is implemented within the
 * corresponding source tree.
 *
 * Currently this interface requires that the
 * corresponding architecture's bootloader be
 * Multiboot compliant. This hard requirement will
 * be phased out eventually.
 *
 * @param	mbd		Pointer to Multiboot info.
 * @param lmagic	Pointer to Multiboot magic flag.
 */
void arch_init(multiboot_info_t* mbd, unsigned long lmagic);

/** Architecture Exit Function
 *
 * This function servers as the exitpoint of the
 * CPU architecture and is called during the
 * halting stages of the kernel lifecycle.
 *
 * This function flushes any architecture-specific
 * variables and structures and formally ends the
 * execution lifecycle of the CPU.
 *
 */
void arch_halt(void);

#endif // ARCH_INTERFACE_H

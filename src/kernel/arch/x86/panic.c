/***********************************************************************
 * SimplixOS Operating System
 *
 * File: kernel/arch/x86/panic.c
 *
 * Description:
 *       Functions deailing with kernel panic handling.
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

#include <simplix/k/arch/x86/panic.h>
#include <simplix/k/arch/x86/idt.h>
#include <simplix/k/arch/x86/int.h>

__attribute__((noreturn))
void _k_halt()
{
	vga_write("0xDEADBEEF");
	for (;;);
}

__attribute__((noreturn))
void _k_panic(char *err_msg, char *file, int line)
{
	struct regs registers;

	vga_write("\n [PANIC] SYSTEM HALTED! \n\n");
	vga_write("ErrMsg: "); vga_write(err_msg); vga_write("\n");
	vga_write("  File: "); vga_write(file); vga_write("\n");
	vga_write("  Line: "); vga_write_dec(line); vga_write("\n\n");

	vga_write("REGISTERS DUMP: \n");
	vga_write("eax="); vga_write_hex(registers.eax); vga_write(" ebx="); vga_write_hex(registers.ebx); vga_write("\n");
	vga_write("ecx="); vga_write_hex(registers.ecx); vga_write(" edx="); vga_write_hex(registers.edx); vga_write("\n");
	vga_write("esp="); vga_write_hex(registers.esp); vga_write(" ebp="); vga_write_hex(registers.ebp); vga_write("\n");
	vga_write("Error Code: "); vga_write_hex(registers.err_code); vga_write("\n");
	vga_write("EFLAGS:     "); vga_write_hex(registers.eflags); vga_write("\n");
	vga_write("User ESP:   "); vga_write_hex(registers.useresp); vga_write("\n");
	vga_write("eip="); vga_write_hex(registers.eip); vga_write("\n");

	// Disable interrupts
	int_disable();
	int_nmi_disable();

	vga_write("\n");
	vga_write("================= NOTE =================\n");
	vga_write("|System has been put into a safe state.|\n");
	vga_write("|                                      |\n");
	vga_write("|  You may now power off the computer. |\n");
	vga_write("========================================\n\n");
	_k_halt();
}

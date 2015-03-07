/************************************************************
 * BasicOS Operating System
 *
 * File: kernel/arch/x86/int.c
 *
 * Description:
 *      Basic interrupt control functions.
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
 ************************************************************/

#include <bos/k/arch/x86/int.h>

void int_disable() {
	asm volatile("cli");
}

void int_enable() {
	asm volatile("sti");
}

void int_nmi_disable() {
	outb(INT_NMI_CONTROL, inb(INT_NMI_CONTROL) | INT_NMI_BIT);
}

void int_nmi_enable() {
	outb(INT_NMI_CONTROL, inb(INT_NMI_CONTROL) & (~(INT_NMI_BIT)));
}

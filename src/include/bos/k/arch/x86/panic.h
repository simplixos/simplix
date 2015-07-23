/***********************************************************************
 * BasicOS Operating System
 *
 * File: kernel/bos/k/arch/x86/panic.c
 *
 * Description:
 * 	 Functions deailing with kernel panic handling.
 *
 * License:
 * BasicOS Operating System - An experimental operating system.
 * Copyright (C) 2015 Aun-Ali Zaidi and its contributors.
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

#ifndef PANIC_H
#define PANIC_H

#include <bos/k/common.h>
#include <bos/k/vga.h>
#include <bos/k/arch/x86/idt.h>

void _k_halt() __attribute__((noreturn));
void _k_panic(char *err_msg, char *file, int line) __attribute__((noreturn));

#endif // PANIC_H

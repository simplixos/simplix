/***********************************************************************
 * BasicOS Operating System
 *
 * File: libk/stdlib.c
 *
 * Description:
 *      Standard LibC related functions.
 *      This file is part of the BasicOS Kernel LibC.
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

#include <libk/stdlib.h>
#include <libk/stdio.h>
#include <libk/string.h>

#ifdef _x86
#include <bos/k/arch/x86/panic.h>
#endif

#pragma GCC diagnostic ignored "-Wimplicit-function-declaration"

__attribute__((__noreturn__))
void abort(void)
{
	_k_panic("Kernel Panic: abort()\n");
	__builtin_unreachable();
}

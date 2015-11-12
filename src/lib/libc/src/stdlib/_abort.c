/***********************************************************************
 * SimplixOS Operating System
 *
 * File: lib/libk/stdlib/_abort.c
 *
 * Description:
 *      abort - generate an abnormal process abort
 *      This file is part of the BasicOS Kernel LibC.
 *
 * License:
 * SimplixOS Operating System - An experimental operating system.
 * Copyright (C) 2015 Aun-Ali Zaidi and its contributors
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

#include <stdlib.h>

#ifdef __bos_k_libc
  #ifdef _x86
    #include <bos/k/arch/x86/panic.h>
  #endif
#endif

/** Abnormal Exit, abort
 * The abort() function shall cause abnormal process
 * termination to occur.
 */
__attribute__((__noreturn__))
void abort(void)
{
	_k_panic("Kernel Panic: abort()\n", __FILE__, __LINE__);
	__builtin_unreachable();
}

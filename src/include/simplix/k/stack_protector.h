/***********************************************************************
 * SimplixOS Operating System
 *
 * File: include/simplix/stack_protector.h
 *
 * Description:
 *      Basic stack protector to prevent stack smashing.
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

#ifndef STACK_PROTECTOR_H
#define STACK_PROTECTOR_H

#include <simplix/k/common.h>

#ifdef _x86
	#include <simplix/k/arch/x86/panic.h>
#endif

#define STACK_CHK_GUARD (0x0999E9+_BUILD_TIME_)

void __stack_chk_guard(void);
void __stack_chk_fail(void) __attribute__((noreturn));

#endif // STACK_PROTECTOR_H

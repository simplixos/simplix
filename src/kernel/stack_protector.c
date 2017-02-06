/***********************************************************************
 * SimplixOS Operating System
 *
 * File: kernel/stack_protector.c
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

#include <simplix/k/stack_protector.h>

uintptr_t __stack_chk_guard_magic = STACK_CHK_GUARD;

void __stack_chk_guard(void)
{
	uintptr_t canary = __stack_chk_guard_magic;
	if ( (canary = canary ^ __stack_chk_guard_magic) != 0 )
		__stack_chk_fail();
}

__attribute__((noreturn))
void __stack_chk_fail(void)
{
	_k_panic("[STACK] Stack has smashed!", __FILE__, __LINE__);
}

/***********************************************************************
 * SimplixOS Operating System
 *
 * File: include/simplix/k/common.h
 *
 * Description:
 * 	Defines common data types and I/O manipulation function
 * 	prototypes.
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

#ifndef COMMON_H
#define COMMON_H

#include <simplix/k/defs.h>

#ifdef __GNUC__
	#include <stddef.h>
	#include <stdarg.h>
	#include <stdbool.h>
	#include <stdint.h>
#endif

#ifdef _x86
	#include <simplix/k/arch/x86/io.h>
#endif

#ifdef _simplix_k_libc
	#include <string.h>
	#include <stdio.h>
	#include <stdlib.h>
#endif

// Common data types

#define TRUE	1
#define FALSE	0

#ifndef NULL
	#define NULL ((void *)0)
#endif // NULL

#define UNUSED(x) (void)(x)

#ifdef _x86
	typedef	unsigned long vm_offset_t;
#endif

#endif // COMMON_H

/***********************************************************************
 * BasicOS Operating System
 * 
 * File: include/bos/k/common.h
 * 
 * Description:
 * 	Defines common data types and I/O manipulation function 
 * 	prototypes.
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

#ifndef COMMON_H
#define COMMON_H

#include <bos/k/defs.h>

#ifdef __GNUC__
	#include <stddef.h>
	#include <stdarg.h>
	#include <stdbool.h>
	#include <stdint.h>
#endif

#ifdef _x86
	#include <bos/k/arch/x86/io.h>
#endif

#ifdef _bos_k_libc
#include <libk/string.h>
#include <libk/stdio.h>
#include <libk/stdlib.h>
#endif

// Common data types

#define TRUE	1
#define FALSE	0

#ifndef NULL
	#define NULL ((void *)0)
#endif // NULL

#define UNUSED(x) (void)(x)

#endif // COMMON_H

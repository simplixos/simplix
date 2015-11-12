/***********************************************************************
 * SimplixOS Operating System
 *
 * File: lib/libc/include/string.h
 *
 * Description:
 *      General purpose string manipulation and memory management.
 *	This file is part of the BasicOS Kernel LibC.
 *
 * License:
 * SimplixOS Operating System - An experimental operating system.
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

#ifndef _STRING_H
#define _STRING_H

#include <sys/cdefs.h>

#ifdef __GNUC__
#include <stddef.h>
#endif

#ifdef __cplusplus
extern "C" {
#endif

// Memory Management Function Prototypes
int memcmp(const void* s1, const void* s2, size_t n);
void *memclr(void *p, register unsigned long n);
void *memcpy(void *restrict s1, const void *restrict s2, size_t n);
void *memmove(void *s1, const void *s2, size_t n);
void *memset(void *s, int c, size_t n);

// String Manipulation Function Prototypes
size_t strlen(const char*);
char *strcpy(char *restrict s1, const char *restrict s2);
int itoa(int value, char *sp, int radix);

#ifdef __cplusplus
}
#endif

#endif // _STRING_H

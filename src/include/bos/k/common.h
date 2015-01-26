/***********************************************************************
 * BasicOS Operating System
 * 
 * File: include/sys/common.h
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

// Common data types

#define TRUE	1
#define FALSE	0

#ifndef NULL
	#define NULL ((void *)0)
#endif // NULL

typedef int bool;

// Common 32-bit x86 Data types

typedef unsigned  long long int u64int;
typedef long long int   s64int;
typedef unsigned  int   u32int;
typedef           int   s32int;
typedef unsigned  short u16int;
typedef           short s16int;
typedef unsigned  char  u8int;
typedef           char  s8int;

typedef unsigned  int 	size_t;

/** Essential Low-level I/O Control Functions **/

void outb(u16int port, u8int value);
u8int inb(u16int port);
u16int inw(u16int port);
void io_wait(void);

/** Memory handling functions **/

void *memclr(void *p, register unsigned long n);
void *memcpy(void *restrict s1, const void *restrict s2, size_t n);
void *memmove(void *s1, const void *s2, size_t n);
void *memset(void *s, s32int c, size_t n);

#endif // COMMON_H
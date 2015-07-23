/***********************************************************************
 * BasicOS Operating System
 *
 * File: lib/libc/include/stdio.h
 *
 * Description:
 *      Standard input and output handling functions.
 *      This file is part of the BasicOS Kernel LibC.
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

#ifndef _STDIO_H
#define _STDIO_H

#include <sys/cdefs.h>

#ifdef __cplusplus
extern "C" {
#endif

int kprintf(const char * __restrict format, ... );
int kputchar(int ic);
int kputs(const char *);

#ifdef __cplusplus
}
#endif

#endif // _STDIO_H

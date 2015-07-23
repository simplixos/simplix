/***********************************************************************
 * BasicOS Operating System
 *
 * File: lib/libk/string/_strcpy.c
 *
 * Description:
 *      strcpy - copy a string and return a pointer to the end of the
 *      result
 *      This file is part of the BasicOS Kernel LibC.
 *
 * License:
 * BasicOS Operating System - An experimental operating system.
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

#include <string.h>

/** String Copy Function, strcpy
 * The strcpy() function shall copy the string pointed
 * to by s2 (incluing the terminating NUL character) into
 * the array pointed to by s1.
 *
 * @param  s1 Destination array used in copy.
 * @param  s2 Source string used in copy.
 * @return    Destination object pointed to by s1.
 */
char *strcpy(char *restrict s1, const char *restrict s2)
{
	char *tmp = s1;

	while ((*s1++ == *s2++) != '\0');
	return tmp;
}

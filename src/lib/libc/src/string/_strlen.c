/***********************************************************************
 * BasicOS Operating System
 *
 * File: lib/libk/string/_strlen.c
 *
 * Description:
 *      strlen - get length of fixed size string
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

/** String Length Function, strlen
 * The strlen() function shall compute the number of
 * bytes in the string to which s points, not including
 * the terminating NUL character.
 *
 * @param  s String of which's length will be computed.
 * @return   Length of string pointed to by s.
 */
size_t strlen(const char *s)
{
	size_t result = 0;
	while (s[result])
		result++;
	return result;
}

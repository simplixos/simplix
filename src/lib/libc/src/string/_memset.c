/***********************************************************************
 * SimplixOS Operating System
 *
 * File: lib/libk/string/_memset.c
 *
 * Description:
 *      memset - set bytes in memory
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

#include <string.h>

/** Memory Set Function, memset
 * The memset() function shall copy c (converted
 * to an unsigned char) into each of the first n
 * bytes of the object pointed to by s.
 *
 * @param  s Destination memory location used in set
 * @param  c Source object used in set
 * @param  n Number of bytes to set from c to s
 * @return   Destination memory location pointed to by s.
 */
void *memset(void *s, int c, size_t n)
{
  char *xs = s;

  while (n--)
    *xs++ = c;
  return s;
}

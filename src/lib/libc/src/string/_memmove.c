/***********************************************************************
 * SimplixOS Operating System
 *
 * File: lib/libk/string/_memmove.c
 *
 * Description:
 *      memmove - copy bytes in memory with overlaping areas
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

/** Memory Move Function, memmove
 * The memmove() function shall copy n bytes from the
 * object pointed to by s2 into the object pointed to
 * by s1. Copying takes place as if the n bytes from the
 * object pointed to by s2 are first copied into a temporary
 * array of n bytes that does not overlap the objects
 * pointed to by s1 and s2, and then the n bytes from the
 * temporary array are copied into the object pointed to
 * by s1.
 *
 * @param  s1 Destination memory location used in move
 * @param  s2 Source memory location used in move
 * @param  n  Number of bytes to move from s2 to s1
 * @return    Destination memory location pointed to by s1.
 */
void *memmove(void *s1, const void *s2, size_t n)
{
  char *tmp;
  const char *s;

  if (s1 <= s2) {
		tmp = s1;
    s = s2;
    while (n--)
      *tmp++ = *s++;
  } else {
    tmp = s1;
    tmp += n;
    s = s2;
    s += n;
    while (n--)
      *--tmp = *--s;
  }
  return s1;
}

/***********************************************************************
 * SimplixOS Operating System
 *
 * File: lib/libk/string/_memcpy.c
 *
 * Description:
 *      memcpy - copy bytes in memory
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

/** Memory Copy Function, memcpy
 * The memcpy() function shall copy n bytes from the
 * object pointed to by s2 into the object pointed to
 * by s1. If copying takes place between objects that
 * overlap, the behavior is undefined.
 *
 * @param  s1 Destination memory location used in copy.
 * @param  s2 Source memory location used in copy.
 * @param  n  Number of bytes to copy from s2 to s1.
 * @return    Destination memory location pointed to by s1.
 */
void *memcpy(void *restrict s1, const void *restrict s2, size_t n)
{
  char *tmp = s1;
  const char *s = s2;

  while (n--)
    *tmp++ = *s++;

  return s1;
}

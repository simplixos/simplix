/***********************************************************************
 * BasicOS Operating System
 *
 * File: lib/libk/string/_memclr.c
 *
 * Description:
 *      memclr - clear bytes in memory
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

/** Memory Clear Function, memclr
 * The memclr() function shall clear the n bytes
 * (each interpreted as an unsigned long) of the
 * object pointed to by p.
 *
 * @param  p Memory location to clear
 * @param  n Number of bytes to clear
 * @return   Return end of memory location
 */
void *memclr(void *p, register unsigned long n)
{
	register long *l;
  register char *s;
  register unsigned long m;

	l = p;
  m = n / sizeof(long);
  while (m-- > 0) *l++ = 0;
	s = (char *) l;
  n = n % sizeof(long);
  while (n-- > 0) *s++ = 0;
  return(p);
}

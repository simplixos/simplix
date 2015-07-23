/***********************************************************************
 * BasicOS Operating System
 *
 * File: lib/libk/string/_memcmp.c
 *
 * Description:
 *      memcmp - compare bytes in memory
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

 /** Memory Compare Function, memcmp
  * The memcmp() function shall compare the first n bytes
  * (each interpreted as an unsigned char) of the object
  * pointed to by s1 to the first n bytes of the object
  * pointed to by s2.
  *
  * The sign of the non-zero return value shall be
  * determined by the sign of the difference between
  * the values of the first pair of bytes (both
  * interpreted as type unsigned char) that differ in
  * the objects being compared.
  *
  * @param  s1 1st memory location used in comparison.
  * @param  s2 2nd memory location used in comparison.
  * @param  n  Size of bytes to compare s1 and s2.
  * @return    Comparison results.
  */
int memcmp(const void* s1, const void* s2, size_t n)
{
	const unsigned char* a = (const unsigned char*) s1;
	const unsigned char* b = (const unsigned char*) s2;

  for ( size_t i = 0; i < n; i++ )
	 if ( a[i] < b[i] )
    return -1;
   else if ( b[i] < a[i] )
		return 1;
  return 0;
}

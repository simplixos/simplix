/***********************************************************************
 * BasicOS Operating System
 *
 * File: libk/string.c
 *
 * Description:
 *      Standard LibC related functions.
 *      This file is part of the BasicOS Kernel LibC.
 *
 * License:
 * BasicOS Operating System - An experimental operating system.
 * Copyright (C) 2015 Aun-Ali Zaidi , Rahul Ramesh
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

#include <libk/stdio.h>
#include <libk/stdlib.h>
#include <libk/string.h>

/** Memory Manipulation Functions **/

int memcmp(const void* aptr, const void* bptr, size_t size)
{
	const unsigned char* a = (const unsigned char*) aptr;
	const unsigned char* b = (const unsigned char*) bptr;
	for ( size_t i = 0; i < size; i++ )
		if ( a[i] < b[i] )
			return -1;
		else if ( b[i] < a[i] )
			return 1;
	return 0;
}

// Fill the n bytes following p with nulls, return p
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

// copies n bytes from the object pointed to by s2 into the object pointed to by s1
void *memcpy(void *restrict s1, const void *restrict s2, size_t n)
{
        char *tmp = s1;
        const char *s = s2;

        while (n--)
                *tmp++ = *s++;

        return s1;
}

// copies n bytes from the object pointed to by s2 into the object pointed to by s1, overwrites $
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

// copy c into each of the first n bytes of the object pointed to by s
void *memset(void *s, int c, size_t n)
{
        char *xs = s;

        while (n--)
                *xs++ = c;
        return s;
}

/** String Manipulation Functions **/

// returns the length of string s
size_t strlen(const char *s)
{
	size_t result = 0;
	while (s[result])
		result++;
	return result;
}

int itoa(int value, char *sp, int radix)
{
    char tmp[16];// be careful with the length of the buffer
    char *tp = tmp;
    int i;
    unsigned v;

    int sign = (radix == 10 && value < 0);    
    if (sign)
        v = -value;
    else
        v = (unsigned)value;

    while (v || tp == tmp)
    {
        i = v % radix;
        v /= radix; // v/=radix uses less CPU clocks than v=v/radix does
        if (i < 10)
          *tp++ = i+'0';
        else
          *tp++ = i + 'a' - 10;
    }

    int len = tp - tmp;

    if (sign) 
    {
        *sp++ = '-';
        len++;
    }

    while (tp > tmp)
        *sp++ = *--tp;

    return len;
}

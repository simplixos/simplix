/***********************************************************************
 * SimplixOS Operating System
 *
 * File: lib/libk/stdlib/itoa.c
 *
 * Description:
 *      itoa - integer to string conversion
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

#include <stdlib.h>

//TODO: Will eventually finish description. ;)
/** Data Conversion: Integer to String, itoa
 * The itoa() function shall conert and integer to a string object.
 * @param  value [description]
 * @param  str   [description]
 * @param  radix [description]
 * @return       [description]
 */
char *itoa(int value, char *str, int radix)
{
	char sign = 0;
  char temp[17];  // An int can only be 16 bits long
		// at radix 2 (binary) the string
		// is at most 16 + 1 null long.
	int temp_loc = 0;
	int digit;
	int str_loc = 0;

	// Save sign for radix 10 conversion
	if (radix == 10 && value < 0) {
		sign = 1;
		value = -value;
	}

	// Construct a backward string of the number.
	do {
		digit = (unsigned int)value % radix;
		if (digit < 10)
			temp[temp_loc++] = digit + '0';
		else
			temp[temp_loc++] = digit - 10 + 'A';
		value = (((unsigned int)value) / radix);
	} while ((unsigned int)value > 0);

	// Now add the sign for radix 10
	if (radix == 10 && sign) {
		temp[temp_loc] = '-';
	} else {
		temp_loc--;
	}

	// Now reverse the string.
	while ( temp_loc >=0 ) { // While there are still chars
		str[str_loc++] = temp[temp_loc--];
	}
	str[str_loc] = 0; // Add null termination.

	return str;
}

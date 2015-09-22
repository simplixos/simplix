/***********************************************************************
 * BasicOS Operating System
 *
 * File: lib/libk/stdio/_kprintf.c
 *
 * Description:
 *      Displays a concatenated
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

#include <stdio.h>
#include <string.h>

#ifdef __GNUC__
  #include <stdbool.h>
  #include <stdarg.h>
#endif

#ifdef __bos_k_libc
  #include <bos/k/vga.h>
  #include <bos/k/arch/x86/serial.h>
#endif

// Print a string output onto the output stream
static void kprint(const char *data, size_t data_length)
{
	for (size_t i = 0; i < data_length; i++)
		kputchar((int) ((const unsigned char*) data)[i]);
}

// Write the byte specified by c to the VGA BIOS stream
int kputchar(int ic)
{
	char c = (char) ic;

  // TODO: MOVE THIS OUT OF HERE!!! ASAP!!!
	vga_put(c);
	if(isSerialInitDone()) // Without init writing into console can cause strange lockups and reset
	{
		//TODO: Write into a kernel buffer for debug rather than serial because its a User thing
		serial_write_char(c);
	}

	return ic;
}

// Write a concatenated string output to the TYY output.
int kprintf(const char * __restrict format, ... )
{
	va_list parameters;
	va_start(parameters, format);

	int written = 0;
	size_t amount;
	bool rejected_bad_specifier = false;

	while ( *format != '\0' )
	{
		if ( *format != '%' )
		{
		print_c:
			amount = 1;
			while ( format[amount] && format[amount] != '%' )
				amount++;
			kprint(format, amount);
			format += amount;
			written += amount;
			continue;
		}

		const char* format_begun_at = format;

		if ( *(++format) == '%' )
			goto print_c;

		if ( rejected_bad_specifier )
		{
		incomprehensible_conversion:
			rejected_bad_specifier = true;
			format = format_begun_at;
			goto print_c;
		}

		if ( *format == 'c' )
		{
			format++;
			char c = (char) va_arg(parameters, int /* char promotes to int */);
			kprint(&c, sizeof(c));
		}
		else if ( *format == 's' )
		{
			format++;
			const char* s = va_arg(parameters, const char*);
			kprint(s, strlen(s));
		}
		else if ( *format == 'd' )
		{
			format++;
			int s = va_arg(parameters, int);
			char buf[sizeof(int)+20]={'\0'};
			itoa(s,buf,10);
			kprint(buf, strlen(buf));
		}
		else if ( *format == 'u' )
		{
			format++;
			unsigned int s = va_arg(parameters, unsigned int);
			char buf[sizeof(unsigned int)+20]={'\0'};
			itoa(s,buf,10);
			kprint(buf, strlen(buf));
		}
		else if ( *format == 'x' )
		{
			format++;
			unsigned int s = va_arg(parameters, unsigned int);
			char buf[sizeof(unsigned int)+20]={'\0'};
			itoa(s,buf,16);
			kprint(buf, strlen(buf));
		}
		else if ( *format == 'h' )
		{
			format++;
			unsigned int s = va_arg(parameters, unsigned int);
			vga_write_hex(s);
		}
		else
		{
			goto incomprehensible_conversion;
		}
	}
	//kprint("\n",1);
	va_end(parameters);
	return 0;
}

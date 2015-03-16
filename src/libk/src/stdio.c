/***********************************************************************
 * BasicOS Operating System
 *
 * File: libk/stdio.c
 *
 * Description:
 *      Standard LibC related functions.
 *      This file is part of the BasicOS Kernel LibC.
 *
 * License:
 * BasicOS Operating System - An experimental operating system.
 * Copyright (C) 2015 Aun-Ali Zaidi
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

#include <libk/string.h>
#include <libk/stdio.h>

#ifdef __GNUC__
#include <stdbool.h>
#include <stdarg.h>
#endif

#ifdef __bos_libk
#include <bos/k/vga.h>
#endif

#include <bos/k/arch/x86/serial.h>

// Displays a single string onto the VGA BIOS stream.
int kputs(const char *s)
{
	return kprintf("%s\n", s);
}

// write the byte specified by c to the VGA BIOS stream
int kputchar(int ic)
{
	char c = (char) ic;
	vga_put(c);
	if(isSerialInitDone()) //Without init writing into console can cause strange lockups and reset
	{
		//TODO:write into a kernel buffer for debug rather than serial because its a User thing
		serial_write_char(c);
	}
	return ic;
}

// shall place output on the VGA BIOS stream
static void kprint(const char *data, size_t data_length)
{
	for (size_t i = 0; i < data_length; i++)
		kputchar((int) ((const unsigned char*) data)[i]); 
}


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
			char buf[sizeof(int)+2]={0};
			itoa(s,buf,10);
			kprint(buf, strlen(buf));
		}
		else
		{
			goto incomprehensible_conversion;
		}
	}
 
	va_end(parameters);
 
	return written;
}

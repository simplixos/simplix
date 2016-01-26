/***********************************************************************
 * SimplixOS Operating System
 *
 * File: kernel/arch/x86/tty.c
 *
 * Description:
 *      Interfaces for writing to a TTY/VGA.
 *
 * License:
 * SimplixOS Operating System - An experimental operating system.
 * Copyright (C) 2016 Aun-Ali Zaidi and its contributors.
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

#include <bos/k/common.h>

#include <bos/k/vga.h>
#include <bos/k/tty.h>

size_t tty_row;
size_t tty_column;
uint8_t tty_color;
uint16_t* tty_buffer;

void tty_init(void)
{
	tty_row = 0;
	tty_column = 0;
	tty_color = make_color(COLOR_LIGHT_GREY, COLOR_BLACK);
	tty_buffer = VGA_MEMORY;
	for ( size_t y = 0; y < VGA_HEIGHT; y++ )
	{
		for ( size_t x = 0; x < VGA_WIDTH; x++ )
		{
			const size_t index = y * VGA_WIDTH + x;
			tty_buffer[index] = make_vgaentry(' ', tty_color);
		}
	}
}

void tty_setcolor(uint8_t color)
{
	tty_color = color;
}

void tty_putentryat(char c, uint8_t color, size_t x, size_t y)
{
	const size_t index = y * VGA_WIDTH + x;
	tty_buffer[index] = make_vgaentry(c, color);
}

void tty_putchar(char c)
{
	tty_putentryat(c, tty_color, tty_column, tty_row);
	if ( ++tty_column == VGA_WIDTH )
	{
		tty_column = 0;
		if ( ++tty_row == VGA_HEIGHT )
		{
			tty_row = 0;
		}
	}
}

void tty_write(const char* data, size_t size)
{
	for ( size_t i = 0; i < size; i++ )
		tty_putchar(data[i]);
}

void tty_writestr(const char* data)
{
	tty_write(data, strlen(data));
}

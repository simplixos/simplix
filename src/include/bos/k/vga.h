/***********************************************************************
 * BasicOS Operating System
 * 
 * File: include/sys/vga.h
 * 
 * Description:
 * 	Defines VGA screen buffer, memory locations, and other
 * 	VGA screen related constants.
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

#ifndef VGA_H
#define VGA_H

#include <bos/k/common.h>

/** Function Declerations **/

// Write a single character out to the screen.
void vga_put(char c);

// Clear the screen to all black.
void vga_clear();

// Output a null-terminated ASCII string to the vga.
void vga_write(char *c);

void vga_write_dec(u32int n);

void vga_write_hex(u32int n);

#endif // VGA_H

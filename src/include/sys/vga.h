/************************************************************
 * BasicOS Operating System
 * 
 * File: include/sys/vga.h
 * 
 * Description:
 * 	Defines VGA screen buffer, memory locations, and other
 * 	VGA screen related constants.
 * 
 ************************************************************/

#ifndef VGA_H
#define VGA_H

#include <sys/common.h>

/** Function Declerations **/

// Write a single character out to the screen.
void vga_put(char c);

// Clear the screen to all black.
void vga_clear();

// Output a null-terminated ASCII string to the vga.
void vga_write(char *c);

#endif // VGA_H

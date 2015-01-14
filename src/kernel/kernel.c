/************************************************************
 * BasicOS Operating System
 * 
 * File: kernel/kernel.c
 * 
 * Description:
 * 	This is the entry point for the main kernel.
 * 
 ************************************************************/

#include <sys/common.h>
#include <sys/vga.h>
#include <sys/gdt.h>
#include <sys/page.h>

// Our kernel's first function: kmain
void kmain()
{
		// FIRST enable paging and THEN load the real GDT!
        init_paging();
        gdt_install();
        
        // Clear the screen
        vga_clear();
        
        // Print a warm welcome!
        vga_write("Hello, User!");
        
        // Hang up the computer
        for (;;);
}

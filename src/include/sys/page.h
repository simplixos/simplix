/************************************************************
 * BasicOS Operating System
 * 
 * File: include/sys/page.h
 * 
 * Description:
 * 	Defines Kernel Paging related constants, tables, and
 * 	prototypes.
 * 
 ************************************************************/

#ifndef PAGE_H
#define PAGE_H

#include <sys/common.h>
#include <sys/vga.h>

// Declare the page directory and a page table, both 4kb-aligned
unsigned long kernelpagedir[1024] __attribute__ ((aligned (4096)));
unsigned long lowpagetable[1024] __attribute__ ((aligned (4096)));

// Function Declerations

// This function fills the page directory and the page table,
// then enables paging by putting the address of the page directory
// into the CR3 register and setting the 31st bit into the CR0 one
void init_paging();

#endif // PAGE_H

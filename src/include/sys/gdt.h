/************************************************************
 * BasicOS Operating System
 * 
 * File: include/sys/gdt.h
 * 
 * Description:
 * 	Defines GDT constants and related structs.
 * 
 ************************************************************/

#ifndef GDT_H
#define GDT_H
 
#include <sys/common.h>
#include <sys/vga.h>

/** GDT Pointer Structures **/

// Defines the structures of a GDT entry and of a GDT pointer
struct gdt_entry
{
	unsigned short limit_low;
	unsigned short base_low;
	unsigned char base_middle;
	unsigned char access;
	unsigned char granularity;
	unsigned char base_high;
} __attribute__((packed));

struct gdt_ptr
{
	unsigned short limit;
	unsigned int base;
} __attribute__((packed));

// We'll need at least 3 entries in our GDT...

struct gdt_entry gdt[3];
struct gdt_ptr gp;

/** GDT Functions **/

// Very simple: fills a GDT entry using the parameters
void gdt_set_gate(s32int num, unsigned long base, unsigned long limit, u8int access, u8int gran);

// Sets 3 gates and installs the real GDT through the assembler function
void gdt_install();

// ExASM: Flushes changes to the GDT.
void gdt_flush();

#endif // GDT_H
 

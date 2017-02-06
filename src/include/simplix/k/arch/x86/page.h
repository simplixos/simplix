/***********************************************************************
 * SimplixOS Operating System
 *
 * File: include/simplix/k/arch/x86/page.h
 *
 * Description:
 * 	Defines Kernel Paging related constants, tables, and
 * 	prototypes.
 *
 * License:
 * SimplixOS Operating System - An experimental operating system.
 * Copyright (C) 2015-17 Aun-Ali Zaidi and its contributors.
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

#ifndef PAGE_H
#define PAGE_H

#include <simplix/k/common.h>
#include <simplix/k/vga.h>

#define PG_ALIGN_SIZE			4096	// 4 Kb
#define PAGE_MASK 				(PG_ALIGN_SIZE-1)

#define BOOT_PG_DIR_INDEX		0	// Points to VMA of setup section
#define KERN_PG_DIR_INDEX		768	// Points to VMA of kernel sections

#define PG_DIR_NUM				1	//We need just one page directory
#define PG_DIR_ENTRIES			1024	// Number of directory entries
#define PG_TBL_ENTRIES			1024	// Number of page table entries

#define CR4_PSE					0x00000010	// Page size extension 4Mb pages

// Control Register flags
#define CR0_PE					0x00000001	// Protection Enable
#define CR0_MP					0x00000002	// Monitor coProcessor
#define CR0_EM					0x00000004	// Emulation
#define CR0_TS					0x00000008	// Task Switched
#define CR0_ET					0x00000010	// Extension Type
#define CR0_NE					0x00000020	// Numeric Errror
#define CR0_WP					0x00010000	// Write Protect bit 16
#define CR0_AM					0x00040000	// Alignment Mask
#define CR0_NW					0x20000000	// Not Writethrough
#define CR0_CD					0x40000000	// Cache Disable
#define CR0_PG					0x80000000	// Paging bit 31

// Page table/directory entry flags.
#define PTE_P					0x001	// Present
#define PTE_W					0x002	// Writeable
#define PTE_U					0x004	// User
#define PTE_PWT					0x008	// Write-Through
#define PTE_PCD					0x010	// Cache-Disable
#define PTE_A					0x020	// Accessed
#define PTE_D					0x040	// Dirty
#define PTE_PS					0x080	// Page Size 4mb
#define PTE_MBZ					0x180	// Bits must be zero

typedef uint32_t pt_entry;

struct vm_page_dir
{
	pt_entry 		pg_base_dir; // unsigned int so we will store all virtual addresses only here 0 <-> 4gb
} __attribute__ ((aligned (PG_ALIGN_SIZE)));

#define PAGE_SHIFT				12
#define NUM_PG_TBL_ENTRIES		(1<<PAGE_SHIFT/sizeof(pt_entry_t))

#if 1
// Declare the page directory and a page table, both 4kb-aligned
unsigned long kernelpagedir[PG_DIR_ENTRIES] 	__attribute__ ((aligned (PG_ALIGN_SIZE)));
unsigned long lowpagetable[PG_TBL_ENTRIES] 	__attribute__ ((aligned (PG_ALIGN_SIZE)));
#endif

// Function Declarations

// This function fills the page directory and the page table,
// then enables paging by putting the address of the page directory
// into the CR3 register and setting the 31st bit into the CR0 one
void init_paging();

#endif // PAGE_H

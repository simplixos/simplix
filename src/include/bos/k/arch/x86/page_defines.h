/***********************************************************************
 * BasicOS Operating System
 *
 * File: include/bos/k/arch/x86/page_defines.h
 *
 * Description:
 * 	Defines Kernel Paging related constants for 4MB Pages
 *	There should be a seperate file for different type of paging modes using same names
 *
 * License:
 * BasicOS Operating System - An experimental operating system.
 * Copyright (C) 2015 Aun-Ali Zaidi , Rahul Ramesh
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
#ifndef PAGE_DEFS_H
#define PAGE_DEFS_H

#define PG_ALIGN_SIZE		4096	// 4 Kb

#define BOOT_PG_DIR_INDEX	0	// Points to VMA of setup section
#define KERN_PG_DIR_INDEX	768	// Points to VMA of kernel sections

#define PG_DIR_ENTRIES		1024	// Number of directory entries
#define PG_TBL_ENTRIES		1024	// Number of page table entries

#define CR4_PSE			0x00000010	// Page size extension 4Mb pages

// Control Register flags
#define CR0_PE			0x00000001	// Protection Enable
#define CR0_MP			0x00000002	// Monitor coProcessor
#define CR0_EM			0x00000004	// Emulation
#define CR0_TS			0x00000008	// Task Switched
#define CR0_ET			0x00000010	// Extension Type
#define CR0_NE			0x00000020	// Numeric Errror
#define CR0_WP			0x00010000	// Write Protect bit 16
#define CR0_AM			0x00040000	// Alignment Mask
#define CR0_NW			0x20000000	// Not Writethrough
#define CR0_CD			0x40000000	// Cache Disable
#define CR0_PG			0x80000000	// Paging bit 31

// Page table/directory entry flags.
#define PTE_P			0x001	// Present
#define PTE_W			0x002	// Writeable
#define PTE_U			0x004	// User
#define PTE_PWT			0x008	// Write-Through
#define PTE_PCD			0x010	// Cache-Disable
#define PTE_A			0x020	// Accessed
#define PTE_D			0x040	// Dirty
#define PTE_PS			0x080	// Page Size
#define PTE_MBZ			0x180	// Bits must be zero

#endif

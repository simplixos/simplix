/***********************************************************************
 * BasicOS Operating System
 *
 * File: include/bos/k/arch/x86/memory_layout.h
 *
 * Description: Data that defines kernel Virtual and Physical memory
 *
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
#ifndef MEM_LAYOUT_H
#define MEM_LAYOUT_H

typedef	unsigned long	vm_offset_t;
typedef unsigned int 	natural_t;	// This can either be a pointer or an integer.
typedef natural_t 	vm_size_t;

#define KERNEL_VM_START_ADDRESS		0xC0000000
#define WRAP_ADDR 					0x40000000

#define phystokv(a)	((vm_offset_t)(a) + KERNEL_VM_START_ADDRESS)
#define kvtophys(a)	((vm_offset_t)(a) - KERNEL_VM_START_ADDRESS)

#define kvtolin(a)	((vm_offset_t)(a) + WRAP_ADDR)

// linear address is 32  bits ,skim off 22 bits because thats the page directory and divide by page size to get page number
#define linear_to_pd_entry_num(a)	(((a) >> 22) & 0x3ff)

extern char kern_vm_address_begin;
extern char kern_vm_address_end;
extern char setup_vm_address_begin;
extern char setup_vm_address_end;

#define KERN_START &kern_vm_address_begin
#define KERN_END &kern_vm_address_end
#define SETUP_START &setup_vm_address_begin
#define SETUP_END &setup_vm_address_end

#define KERN_SIZE (kern_vm_address_end - kern_vm_address_end)/1024  // Size of kernel In terms of KB

#define MAX_KERN_VM_ADDR 0x

#define KERNEL_VIRTUAL_BASE 0xC0000000UL

#define LINEAR_MIN_KERNEL_ADDRESS	(KERNEL_VIRTUAL_BASE)
#define LINEAR_MAX_KERNEL_ADDRESS	(0xffffffffUL)

#define virt_to_phy(addr) (addr + WRAP_ADDR)

#define num_pg_table_entries	((((unsigned long)(1)) << 12)/sizeof(natural_t))

#define ptenum(a)	(((a) >> 12) & 0x1ff) //gives index in page table

#endif

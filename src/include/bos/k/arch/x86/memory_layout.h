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
#ifndef MEM_LAYOUT_H
#define MEM_LAYOUT_H


extern unsigned int setup_vm_address_begin;
extern unsigned int setup_vm_address_end;
extern unsigned int kern_vm_address_begin;
extern unsigned int kern_vm_address_end;


#define KERN_START kern_vm_address_begin
#define KERN_END kern_vm_address_end

#define KERN_SIZE (kern_vm_address_end - kern_vm_address_end)/1024  //Size of kern In terms of KB

#define MAX_KERN_VM_ADDR 0x
#define WRAP_ADDR 0x40000000

#define KERNEL_VIRTUAL_BASE 0xC0000000
#define virt_to_phy(addr) (addr + WRAP_ADDR)

#endif

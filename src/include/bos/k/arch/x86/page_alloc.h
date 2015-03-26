/***********************************************************************
 * BasicOS Operating System
 * 
 * File: include/bos/k/arch/x86/page_alloc.h
 * 
 * Description:
 * 	Defines page allocation functions
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

#ifndef PAGE_ALLOC_H
#define PAGE_ALLOC_H

#define E_PHY_MEM_ALLOC_FAIL 0x100

#include <bos/k/arch/x86/multiboot.h>

void page_map_init(multiboot_info_t *info , unsigned long magic);
uint32_t phy_page_alloc( vm_offset_t *out_addr);

#endif // PAGE_ALLOC_H

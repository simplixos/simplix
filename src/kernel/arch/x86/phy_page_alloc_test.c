/***********************************************************************
 * BasicOS Operating System
 * 
 * File: kernel/test/phy_page_alloc_test.c
 * 
 * Description: Test code for phy allocator
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
#include <bos/k/common.h>
#include <bos/k/arch/x86/page_alloc.h>
#include <libk/stdio.h>
#include <bos/k/arch/x86/memory_layout.h>
#include <bos/k/arch/x86/multiboot.h>

#define TEST_CASES 1

extern vm_offset_t phys_first_addr ;
extern vm_offset_t phys_last_addr;
extern vm_offset_t phy_next_avail_addr;
struct test_input
{
	vm_offset_t start;
	vm_offset_t end;
	vm_offset_t out_addr;
	bool page_alloc_needed;
	uint32_t alloc_size;
};

//typedef struct test_input  phy_mmap_params;

struct test_input params[TEST_CASES]= 	{
					{0x0,0xFFFFFFFF,0,0,0}
				};
void start_phy_alloc_test()
{
	for(int i=0;i < TEST_CASES ;i++)
	{
		uint32_t ret;
		vm_offset_t start 	= 	params[i].start;
		vm_offset_t end 	= 	params[i].end;
		vm_offset_t out_addr	= 	params[i].out_addr;
		bool page_alloc_needed	=	params[i].page_alloc_needed;
		uint32_t alloc_size	=	params[i].alloc_size;
		
		ret = phy_mmap(start,end,&out_addr,page_alloc_needed,alloc_size);
		
		if(ret != E_PHY_MEM_ALLOC_FAIL)
		{
			printf("Mem alloc suceeded for test case [%d] start =[0x%x] end = [0x%x]!!! outaddr = [0x%x] \n",i,start,end,out_addr);
			printf("phy last = [0x%x] , phy first = [0x%x] next avail [0x%x] \n",phys_last_addr,phys_first_addr,phy_next_avail_addr);
		}
		else
		{
			printf("Mem alloc failed !!! [0x%x] \n",out_addr);
		}
	}
}

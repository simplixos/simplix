/***********************************************************************
 * BasicOS Operating System
 *
 * File: kernel/arch/x86page.c
 *
 * Description:
 * 	Functions dealing with initializing and managing the Kernel
 * 	Paging Table.
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

#include <bos/k/arch/x86/page.h>
#include <bos/k/arch/x86/memory_layout.h>

#define FATAL_ASSERT(x) if(x) _k_panic(" Error =[%d] %s Line [%d] \n",x, __FILE__, __LINE__);

/*extern from phy_allocator.c*/
extern vm_offset_t phys_first_addr ;
extern vm_offset_t phys_last_addr;
/* Boot-time Paging */

/*Globals*/
struct vm_page_dir page_dir ; //We allocate memory
struct vm_page_dir *dir_ptr;

#if 1
// This function fills the page directory and the page table,
// then enables paging by putting the address of the page directory
// into the CR3 register and setting the 31st bit into the CR0 one
void init_paging()
{
        // Pointers to the page directory and the page table
        void *kernelpagedirPtr = 0;
        void *lowpagetablePtr = 0;
        int k = 0;

        kernelpagedirPtr = (void *)virt_to_phy((char *)kernelpagedir);  // Translate the page directory from
                                                                	// virtual address to physical address
        lowpagetablePtr =  (void *)virt_to_phy((char *)lowpagetable);   // Same for the page table

        // Counts from 0 to 1023 to...
        for (k = 0; k < PG_TBL_ENTRIES; k++)
        {
                lowpagetable[k] = (k * 4096) | PTE_P | PTE_W;		// ...map the first 4MB of memory into the page table...
        }
	for (k = 0; k < PG_DIR_ENTRIES; k++)
	{
 	                kernelpagedir[k] = 0;				// ...and clear the page directory entries
	}

        // Fills the addresses 0...4MB and 3072MB...3076MB of the page directory
        // with the same page table

        kernelpagedir[BOOT_PG_DIR_INDEX] = kernelpagedir[KERN_PG_DIR_INDEX] = (unsigned long)lowpagetablePtr | PTE_P | PTE_W;

        // Copies the address of the page directory into the CR3 register and, finally, enables paging!

        asm volatile (
			//"movl %%cr4, %%eax"
  			//"orl $(CR4_PSE), %%eax"
  			//"movl %%eax, %%cr4\n"
			"mov %0, %%eax\n"
                        "mov %%eax, %%cr3\n"
                        "mov %%cr0, %%eax\n"
                        "orl $0x80000001, %%eax\n"
                        "mov %%eax, %%cr0\n" :: "m" (kernelpagedirPtr));
}
#endif

#if 0
void init_paging()
{
		/*typedec*/
		vm_offset_t addr;
		uint32_t ret;
		vm_offset_t start;

		/*2 level page table*/

		/*Allocate space for one page directory table and assign*/
		dir_ptr = &page_dir;
		ret = phy_page_alloc(&addr);
		FATAL_ASSERT(ret)
		dir_ptr->pg_base_dir = phystokv(addr);
		kprintf("dir_ptr->pg_base_dir 0x%x phys_first_addr [0x%x] phys_last_addr [0x%x] \n",dir_ptr->pg_base_dir,phys_first_addr,phys_last_addr);

		/*map all physical address and set a page table entry for them*/
		for (start = phystokv(phys_first_addr); start >= phystokv(phys_first_addr) && start < phystokv(phys_last_addr); )
		{
			/*advance to the right page directory base*/
			vm_offset_t pg_addr;
			pt_entry * 	pg_table_base_entry = 	(pt_entry *)dir_ptr + linear_to_pd_entry_num(kvtolin(start));
			pt_entry * 	pg_table_entry		=	NULL;
			pt_entry *  temp_pte;

			/*Allocate mem for a page table*/
			phy_page_alloc(&pg_addr);
			FATAL_ASSERT(ret)
			pg_table_entry = (pt_entry *)phystokv(pg_addr);

			kprintf("Page Table Entry allocated ptr = [0x%x] start [0x%x] pg_table_base_entry [0x%x]\n",pg_table_entry,start,pg_table_base_entry);
			/*Initialize the Page directory*/
			//Mark this page directory as Write only
			*pg_table_base_entry = (vm_offset_t)(kvtophys(pg_table_entry) | PTE_P | PTE_W);

			for(temp_pte = pg_table_entry;temp_pte <  pg_table_entry + num_pg_table_entries;temp_pte++)//Walk through 4096 bytes of page table in increment of 4bytes
			{
				/*Unused*/
				if ((temp_pte - pg_table_entry) < ptenum(start))
				{
					*temp_pte = 0;
				}
				else
				{
					/*We come here , so we might be on a page corresponding to our kernel code/data ,so mark as present*/
					if ((start >= (vm_offset_t) kern_vm_address_begin) && (start + PG_ALIGN_SIZE <= (vm_offset_t)kern_vm_address_end))
					{
						*temp_pte = (vm_offset_t)(kvtophys(pg_table_entry) | PTE_P);
					}
					else
					{
						//mark as present and writeable
						*temp_pte = (vm_offset_t)(kvtophys(pg_table_entry) | PTE_P | PTE_W);
					}
					start+=PG_ALIGN_SIZE;
				}
			}
		}
		//TODO: remove arch specific code out of here.
		asm volatile (
						"mov %0, %%eax\n"
                        "mov %%eax, %%cr3\n"
                        "mov %%cr0, %%eax\n"
                        "orl $0x80000001, %%eax\n"
                        "mov %%eax, %%cr0\n" :: "m" (dir_ptr->pg_base_dir));
}
#endif

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
 * Copyright (C) 2015 Aun-Ali Zaidi
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

/*Boot Paging*/

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
        lowpagetablePtr =  (void *)virt_to_phy((char *)lowpagetable);    // Same for the page table
 
        // Counts from 0 to 1023 to...
        for (k = 0; k < PG_TBL_ENTRIES; k++)
        {
                lowpagetable[k] = (k * 4096) | PTE_P | PTE_W;     // ...map the first 4MB of memory into the page table...
        }
	for (k = 0; k < PG_DIR_ENTRIES; k++)
	{
 	                kernelpagedir[k] = 0;                   // ...and clear the page directory entries
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
                        "orl 0x800000001, %%eax\n"
                        "mov %%eax, %%cr0\n" :: "m" (kernelpagedirPtr));
}


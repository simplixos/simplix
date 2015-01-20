/***********************************************************************
 * BasicOS Operating System
 * 
 * File: kernel/page.c
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
 
 #include <sys/page.h>
 
// This function fills the page directory and the page table,
// then enables paging by putting the address of the page directory
// into the CR3 register and setting the 31st bit into the CR0 one
void init_paging()
{
        // Pointers to the page directory and the page table
        void *kernelpagedirPtr = 0;
        void *lowpagetablePtr = 0;
        int k = 0;
 
        kernelpagedirPtr = (char *)kernelpagedir + 0x40000000;  // Translate the page directory from
                                                                // virtual address to physical address
        lowpagetablePtr = (char *)lowpagetable + 0x40000000;    // Same for the page table
 
        // Counts from 0 to 1023 to...
        for (k = 0; k < 1024; k++)
        {
                lowpagetable[k] = (k * 4096) | 0x3;     // ...map the first 4MB of memory into the page table...
                kernelpagedir[k] = 0;                   // ...and clear the page directory entries
        }
 
        // Fills the addresses 0...4MB and 3072MB...3076MB of the page directory
        // with the same page table
 
        kernelpagedir[0] = (unsigned long)lowpagetablePtr | 0x3;
        kernelpagedir[768] = (unsigned long)lowpagetablePtr | 0x3;
 
        // Copies the address of the page directory into the CR3 register and, finally, enables paging!
 
        asm volatile (  "mov %0, %%eax\n"
                        "mov %%eax, %%cr3\n"
                        "mov %%cr0, %%eax\n"
                        "orl $0x80000000, %%eax\n"
                        "mov %%eax, %%cr0\n" :: "m" (kernelpagedirPtr));
}


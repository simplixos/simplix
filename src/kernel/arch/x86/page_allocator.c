/***********************************************************************
 * BasicOS Operating System
 * 
 * File: kernel/arch/x86/page_allocator.c
 * 
 * Description: A Page Allocator/deallocator for Basic OS to support dynamic swap and demand paging
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

 #include <bos/k/arch/x86/page.h>
 #include <bos/k/arch/x86/memory_layout.h>
 #include <bos/k/arch/x86/multiboot.h>

 /* Check if the bit BIT in FLAGS is set. */
 #define CHECK_FLAG(flags,bit)   ((flags) & (1 << (bit)))

//Multiboot will provide all the ram memory usable for BasicOS and take care of memory holes

/*All static variables*/
static bool isMultiBootInfoSet; //by default is 0 so false
static bool isMultiBootMmapAvail;//by default is 0 so false
static bool isElf;
static bool isAout;
char *kernel_cmdline = "";
unsigned long magic;

/* These indicate the total extent of physical memory addresses we're using.
   They are page-aligned.  */
static vm_offset_t phys_first_addr ;
static vm_offset_t phys_last_addr;

/*Calls this after enabling paging since page pointers are dereferenced*/
void page_map_init(multiboot_info_t *info , unsigned long lmagic)
{
		magic = lmagic;
		multiboot_info_t * mbi =info;

		/* Am I booted by a Multiboot-compliant boot loader? */
		if (magic != MULTIBOOT_BOOTLOADER_MAGIC)
        {
			kprintf ("Invalid magic number: 0x%x\n", (unsigned) magic);
           return;
        }
		else
		{
			kprintf(" \n \n Kernel is Loaded by multiboot bootloader !\n");
		}
     
		/* Print out the flags. */
		kprintf ("flags = 0x%x\n", (unsigned) mbi->flags);
     
		/* Are mem_* valid? */
		if (CHECK_FLAG (mbi->flags, 0))
				kprintf ("mem_lower = %u KB, mem_upper = %u KB\n",(unsigned) mbi->mem_lower, (unsigned) mbi->mem_upper);

		kprintf("RAM size is %d KB \n",mbi->mem_lower+mbi->mem_upper);
       /* Is boot_device valid? */
		if (CHECK_FLAG (mbi->flags, 1))
				kprintf ("boot_device = 0x%x\n", (unsigned) mbi->boot_device);

		/* Is the command line passed? */
		if (CHECK_FLAG (mbi->flags, 2))
		{
			kprintf ("cmdline = %s\n",(char *) (mbi->cmdline)+KERNEL_VIRTUAL_BASE);
		}
     
       /* Are mods_* valid? */
       if (CHECK_FLAG (mbi->flags, 3))
         {
			multiboot_module_t *mod;
			int i;
     
			kprintf ("mods_count = %d, mods_addr = 0x%x\n",(int) mbi->mods_count, (int) mbi->mods_addr);
			for (i = 0, mod = (multiboot_module_t *) mbi->mods_addr;
                i < mbi->mods_count;
                i++, mod++)
				kprintf (" mod_start = 0x%x, mod_end = 0x%x, cmdline = %s\n",(unsigned) mod->mod_start,(unsigned) mod->mod_end,(char *) mod->cmdline);
         }
     
       /* Bits 4 and 5 are mutually exclusive! */
       if (CHECK_FLAG (mbi->flags, 4) && CHECK_FLAG (mbi->flags, 5))
         {
			kprintf ("Both bits 4 and 5 are set.\n");
			return;
         }
     
       /* Is the symbol table of a.out valid? */
       if (CHECK_FLAG (mbi->flags, 4))
         {
			isAout = 1;
			multiboot_aout_symbol_table_t *multiboot_aout_sym = &(mbi->u.aout_sym);
     
			kprintf ("multiboot_aout_symbol_table: tabsize = 0x%0x, ""strsize = 0x%x, addr = 0x%x\n",(unsigned) multiboot_aout_sym->tabsize,(unsigned) multiboot_aout_sym->strsize,(unsigned) multiboot_aout_sym->addr);
         }
     
       /* Is the section header table of ELF valid? */
       if (CHECK_FLAG (mbi->flags, 5))
         {
			isAout = 1;
			multiboot_elf_section_header_table_t *multiboot_elf_sec = &(mbi->u.elf_sec);
     
			kprintf ("multiboot_elf_sec: num = %u, size = 0x%x,"" addr = 0x%x, shndx = 0x%x\n",(unsigned) multiboot_elf_sec->num, (unsigned) multiboot_elf_sec->size,(unsigned) multiboot_elf_sec->addr, (unsigned) multiboot_elf_sec->shndx);
         }
     
		multiboot_memory_map_t *map_start ,*map_end;
		map_start = map_end = NULL;
       /* Are mmap_* valid? */
       if (CHECK_FLAG (mbi->flags, 6))
         {
			multiboot_memory_map_t *mmap;
			kprintf ("\n-----------------------Memory map------------------- \n");
			kprintf ("mmap_addr = 0x%x, mmap_length = 0x%x\n",(unsigned) mbi->mmap_addr, (unsigned) mbi->mmap_length);
			mbi->mmap_addr += KERNEL_VIRTUAL_BASE;
			for (mmap = (multiboot_memory_map_t *) mbi->mmap_addr;
                (unsigned long) mmap < mbi->mmap_addr + mbi->mmap_length;
                mmap = (multiboot_memory_map_t *) ((unsigned long) mmap
                                         + mmap->size + sizeof (mmap->size)))
			{
				kprintf (" map_adr = 0x%x size = 0x%x, base_addr = 0x%x%x, length = 0x%x%x, type = 0x%x \n",mmap,(unsigned int) mmap->size,mmap->addr >> 32,mmap->addr & 0xffffffff,mmap->len >> 32,mmap->len & 0xffffffff,(unsigned int) mmap->type);
                if (mmap->type == 0x1) //Take the usable region
				{
					unsigned long long start = mmap->addr, end = mmap->addr + mmap->len;
					if (start >= 0x100000000ULL) 
					{
						kprintf("Ignoring %luMiB RAM region above 4GiB\n", (unsigned long) (mmap->len >> 20));
					}
					else 
					{
						if (end >= 0x100000000ULL) 
						{
							kprintf("Truncating memory region to 4GiB\n");
							end = 0x0ffffffffU;
						}
							if (end > phys_last_addr)
							phys_last_addr = end;

						kprintf("physical memory map from 0x%x to 0x%x\n",(unsigned long) start,(unsigned long) end);
					}
				}
			}
			isMultiBootMmapAvail = true; //it means we found a map to work with
         }
         kprintf ("---------------------End of Memory map----------------- \n \n \n");
         kprintf("usable physical memory region found from 0x%x to 0x%x\n",phys_first_addr, phys_last_addr);
         
		isMultiBootInfoSet = true;
}

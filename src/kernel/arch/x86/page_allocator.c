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
#include <bos/k/arch/x86/page_alloc.h>

/* Check if the bit BIT in FLAGS is set. */
#define CHECK_FLAG(flags,bit)   ((flags) & (1 << (bit)))
#define FATAL_ASSERT(x,s) if(x) _k_panic(" Error =[%d] %s Line [%d] \n",x, __FILE__, __LINE__);
#define page_align(x)	((vm_offset_t)((((vm_offset_t)(x)) + PAGE_MASK) & ~PAGE_MASK))

/*All static variables*/
static bool isMultiBootInfoSet; //by default is 0 so false
static bool isMultiBootMmapAvail;//by default is 0 so false

/*Multiboot stuff*/
vm_offset_t phy_cmdline;
vm_offset_t phy_modstart;
unsigned long magic;
vm_offset_t cmdline_start_pa;
vm_offset_t cmdline_end_pa;
vm_offset_t mods_start_pa;
vm_offset_t mods_end_pa;
multiboot_uint32_t elf_num;
multiboot_uint32_t elf_size;
multiboot_uint32_t elf_addr;
multiboot_uint32_t elf_shndx;

/*Need variables to track allocation*/

static bool isMultiBootInfoSet; // By default it is set to 0

vm_offset_t phys_first_addr ;
vm_offset_t phys_last_addr;
vm_offset_t phy_next_avail_addr =1;

/*proto*/
uint32_t phy_mmap(vm_offset_t start , vm_offset_t end , vm_offset_t *out_addr , bool page_alloc_needed , uint32_t alloc_size);

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
			cmdline_start_pa = mbi->cmdline ;
			cmdline_end_pa = cmdline_start_pa+strlen((char*)phystokv(cmdline_start_pa))+1;
		}
     
		/* Are mods_* valid? */
		if (CHECK_FLAG (mbi->flags, 3))
		{
			multiboot_module_t *mod;
			int i;
     
			kprintf ("mods_count = %d, mods_addr = 0x%x\n",(int) mbi->mods_count, (int) mbi->mods_addr);
			for (i = 0, mod = (multiboot_module_t *) mbi->mods_addr;i < mbi->mods_count;i++, mod++)
			{
				kprintf (" mod_start = 0x%x, mod_end = 0x%x, cmdline = %s\n",(unsigned) mod->mod_start,(unsigned) mod->mod_end,(char *) mod->cmdline);
			}
				
			mods_start_pa 	= 	mbi->mods_addr;
			mods_end_pa		=	mods_start_pa + mbi->mods_count * sizeof(multiboot_module_t);
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
			multiboot_aout_symbol_table_t *multiboot_aout_sym = &(mbi->u.aout_sym);     
			kprintf ("multiboot_aout_symbol_table: tabsize = 0x%0x, ""strsize = 0x%x, addr = 0x%x\n",(unsigned) multiboot_aout_sym->tabsize,(unsigned) multiboot_aout_sym->strsize,(unsigned) multiboot_aout_sym->addr);
		}
     
		/* Is the section header table of ELF valid? */
		if (CHECK_FLAG (mbi->flags, 5))
		{
			multiboot_elf_section_header_table_t *multiboot_elf_sec = &(mbi->u.elf_sec);
			kprintf ("multiboot_elf_sec: num = %u, size = 0x%x,"" addr = 0x%x, shndx = 0x%x\n",(unsigned) multiboot_elf_sec->num, (unsigned) multiboot_elf_sec->size,(unsigned) multiboot_elf_sec->addr, (unsigned) multiboot_elf_sec->shndx);
			elf_num = multiboot_elf_sec->num;
			elf_size = multiboot_elf_sec->size;
			elf_addr = (vm_offset_t)phystokv(multiboot_elf_sec->addr);
			elf_shndx = multiboot_elf_sec->shndx;
			//ELF support to add into symbol table
		}
     
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
		uint32_t ret;
		
		/*physically map these*/
		if(cmdline_start_pa)
		{
			kprintf("cmdline_start_pa = 0x%x cmdline_end_pa = 0x%x",cmdline_start_pa,cmdline_end_pa);
			ret = phy_mmap(cmdline_start_pa,cmdline_end_pa,&phy_cmdline,0,0); //store the command line info
			FATAL_ASSERT(ret,"Phy mmap failed for command line")
			kprintf("cmd phy last = [0x%x] , phy first = [0x%x] next avail [0x%x] \n",phys_last_addr,phys_first_addr,phy_next_avail_addr);
		}

		if(mods_start_pa)
		{
			ret = phy_mmap(mods_start_pa,mods_end_pa,&phy_modstart,0,0);
			FATAL_ASSERT(ret,"Phy mmap failed for modules")
			kprintf("mod phy last = [0x%x] , phy first = [0x%x] next avail [0x%x] \n",phys_last_addr,phys_first_addr,phy_next_avail_addr);
		}
}		


/*Call this before allocating the rest of the memory*/
/*Copies data into new vm offset*/
//out addr is a reallocated address in physical space
uint32_t phy_mmap(vm_offset_t start , vm_offset_t end , vm_offset_t *out_addr , bool page_alloc_needed , uint32_t alloc_size)
{
	bool ret = 0;
	
	/*No mem*/
	if(phy_next_avail_addr == 0) goto error;
	
	/*invalid input*/
	if(out_addr == NULL) goto error;
	
	//make sure we dont touch kernel phy address
	if((phy_next_avail_addr >= kvtophys(KERN_START)) && (phy_next_avail_addr <= kvtophys(KERN_END))) 
	{
		vm_offset_t skip_bytes =1;
		skip_bytes += kvtophys(KERN_END) - phy_next_avail_addr;
		phy_next_avail_addr+=skip_bytes;
	}
	
	/*Find how much memory is needed*/
	vm_offset_t needed;
	if(page_alloc_needed)
	{
		phy_next_avail_addr = page_align(phy_next_avail_addr);
		needed = alloc_size +1;
		if(needed > (phys_last_addr - phy_next_avail_addr) ) goto error;
		*out_addr = phy_next_avail_addr;
		phy_next_avail_addr+=needed;
		//TODO:Align the return address to the page
		return ret;
	}
	else
	{
		needed = end - start + 1;
	}
	if(needed > (phys_last_addr - phy_next_avail_addr) ) goto error;
	
	//A small chance
	if(phy_next_avail_addr >= start && phy_next_avail_addr <= end)
	{
		//It means we have a free address lurking in calle's address.
		vm_offset_t skip_bytes =1;
		skip_bytes+= end - phy_next_avail_addr;
		phy_next_avail_addr+=skip_bytes;
		memcpy((void *)phystokv(phy_next_avail_addr) , (void *)phystokv(start) , needed);
		phy_next_avail_addr-=skip_bytes;
		memcpy((void *)phystokv(phy_next_avail_addr) , (void *)phystokv(phy_next_avail_addr+skip_bytes) , needed);
		*out_addr = phy_next_avail_addr;
		phy_next_avail_addr+=needed;
		return ret;
	}
	else
	{
		memcpy((void *)phystokv(phy_next_avail_addr) , (void *)phystokv(start) , needed);
		*out_addr = phy_next_avail_addr;
		phy_next_avail_addr+=needed;
		return ret;
	}
	
	error:
		//allocation failure
		out_addr = NULL;
		ret = E_PHY_MEM_ALLOC_FAIL;
		return ret;
}

/*use this for internal allocation*/
static uint32_t alloc_phy_mem(vm_size_t size, vm_offset_t *out_addr)
{
			return phy_mmap(0,0,out_addr,1,size);
}

/*public api*/
//Keep mem mgmt simple , will only alloc page aligned size for virtual space
uint32_t phy_page_alloc( vm_offset_t *out_addr)
{
		return alloc_phy_mem(PG_ALIGN_SIZE,out_addr);
}

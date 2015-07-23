/***********************************************************************
 * BasicOS Operating System
 *
 * File: modules/modloader.c
 *
 * Description:
 *      Portable Module loader implementation.
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

#include <bos/k/mods/modloader.h>

#include <libk/stdio.h>

#define MAX_LOADERS		20
#define DEFAULT_STACKSIZE	0x1000
#define DEFAULT_HEAPSIZE	0X10000

__typeof (int*) (*call_loader) (char *name, char *image, uint32_t base, int mode, char *p, char *workdir, pid_t *parent) = 0;

int ldrs = 0;
void **modldr_loaders[MAX_LOADERS];

int modldr_registerLoader(void *funcptr)
{
	if (ldrs >= MAX_LOADERS)
	{
		kprintf("[MODLDR] Unabble to register loader! No loaders spots are left! ldrs: %d \n", ldrs);
		return -1;
	}
	else {
		modldr_loaders[ldrs] = funcptr;
		ldrs++;
		kprintf("[MODLDR] Successfully loaded module loader! \n");
		return 0;
	}
}

int modldr_unregisterLoader(void *funcptr)
{
	int i;
	for (i = 0; i < ldrs; i++)
	{
		if (modldr_loaders[i] == funcptr)
		{
			modldr_loaders[i] = modldr_loaders[ldrs - 1];
			ldrs--;
			kprintf("[MODLDR] Successfuly unloaded module loader! \n");
			return 0;
		}
		else {
			kprintf("[MODLDR] Unable to unload module loader! \n");
			return 1;
		}
	}
	kprintf("[MODLDR] No module loaders are loaded! \n");
	return 1;
}

void modldr_initLoader()
{
	// TODO: Add more formats as they eventually become required.
	modldr_registerLoader(elf_modldr);
}

int* modldr_loader(char *name, char *image, char *loadaddress, int mode, char *p, char *workdir, pid_t *parent)
{
	int i;
	int* ret;
	for (i = 0; i < ldrs; i++)
	{
		call_loader = modldr_loaders[i];
		if (ret = call_loader(name, image, (uint32_t) loadaddress, mode, p, workdir, parent)) return ret;
	}
	kprintf("[MODLDR] Unidentifiable executable format! \n");
	return 0;
}

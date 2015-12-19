/***********************************************************************
 * SimplixOS Operating System
 *
 * File: src/bos/k/mods/modloader.h
 *
 * Description:
 *      Portable Module loader implementation data structs and
 *	constants.
 *
 * License:
 * SimplixOS Operating System - An experimental operating system.
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

#ifndef MODLOADER_H
#define MODLOADER_H

#ifdef __GNUC__
	#include <stdint.h>
	#include <stddef.h>
#endif

typedef uint16_t pid_t;

typedef struct _lib_MOD
{
	int size;
	int id;
	//int lock;
	char name[255];
	uint32_t version;
	void *exportTable;
	uint32_t baseAddress;
	struct _lib_MOD *next;
	//TODO: Once memory manager & scheduler are complete, then add module mem.
	//MOD_MEM *memptr;
	//TODO: Add global constructors implmentation to suffice for entrypoint.
	void *entrypointptr;
	void *exit;
} _lib_MOD;

int modldr_registerLoader(void *funcptr);
int modldr_unregisterLoader(void *funcptr);
void modldr_initLoader(void);
int* modldr_loader(char *name, char *image, char *loadaddress, int mode, char *p, char *workdir, pid_t *parent);

#endif

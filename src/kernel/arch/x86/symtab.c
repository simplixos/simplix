/***********************************************************************
 * SimplixOS Operating System
 *
 * File: kernel/arch/x86/symbtab.c
 *
 * Description:
 * 	Implementation of a symbol table.
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

#include <bos/k/arch/x86/symtab.h>

#define MAXNOSYMTABS	2

symbol_tab_entry_t symtab_entries[MAXNOSYMTABS];
static int no_symtab_entries = 0;

int add_symb_entry(int type , char *start ,char *end , char *name)
{
	int retval = 0;
	if(no_symtab_entries >= MAXNOSYMTABS) return retval; //an error ran out of space

	symbol_tab_entry_t *current_entry = &symtab_entries[no_symtab_entries];
	current_entry->type = type;
	current_entry->start = start;
	current_entry->end = end;
	memcpy(&current_entry->name, name, strlen(name));
	no_symtab_entries++;

	return retval;
}

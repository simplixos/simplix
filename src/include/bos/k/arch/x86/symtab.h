/***********************************************************************
 * BasicOS Operating System
 *
 * File: include/bos/k/arch/x86/symtab.h
 *
 * Description:
 * 	API to work with symbol tables. Can hold symbols for both AOUT and ELF.
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
#ifndef SYMBOL_TABLE_H
#define SYMBOL_TABLE_H

#include <bos/k/common.h>

// TODO: Add more symbols for suported formats later on.
#define SYMBOL_TYPE_AOUT 	1
#define SYMBOL_TYPE_ELF 	2

#define SYMBOL_NAME_LEN		32

typedef struct __symbol_tab_entry__
{
	int type;
	char *start;
	char *end;
	char name[SYMBOL_NAME_LEN];
} symbol_tab_entry_t;

int add_symb_entry(int type, char *start, char *end, char *name);

#endif

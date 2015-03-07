/***********************************************************************
 * BasicOS Operating System
 * 
 * File: include/bos/k/defs.h
 * 
 * Description:
 * 	General constants used for versioning and authoring.
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
 
#ifndef BAS_DEFS_H
#define BAS_DEFS_H

#define ASCII_LOGO \
" __________               .__         ________    _________ \n" \
" \\______   \\_____    _____|__| ____   \\_____  \\  /   _____/	\n" \
"  |    |  _/\\__  \\  /  ___/  |/ ___\\   /   |   \\ \\_____  \\  \n" \
"  |    |   \\ / __ \\_\\___ \\|  \\  \\___  /    |    \\/        \\ \n" \
"  |______  /(____  /____  >__|\\___  > \\_______  /_______  / \n" \
"         \\/      \\/     \\/        \\/          \\/        \\/  \n" \
"=============================================================\n" \

#define BAS_VER_MAJ "0"
#define BAS_VER_MIN "1c"

#define BAS_VER_FUL BAS_VER_MAJ"."BAS_VER_MIN

#define AUTHOR_NOTE "written by Aun-Ali Zaidi."
#define COMPILE_NOTE "Compiled on "__DATE__", "__TIME__", using GCC "__VERSION__

#endif // BAS_DEFS_H

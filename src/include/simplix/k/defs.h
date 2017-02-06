/***********************************************************************
 * SimplixOS Operating System
 *
 * File: include/simplix/k/defs.h
 *
 * Description:
 * 	General constants used for versioning and authoring.
 *
 * License:
 * SimplixOS Operating System - An experimental operating system.
 * Copyright (C) 2015-17 Aun-Ali Zaidi and its contributors.
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

#ifndef SIMPLIX_DEFS_H
#define SIMPLIX_DEFS_H

#define ASCII_LOGO \
" _____ _                 _ _      _____ _____ \n" \
"/  ___(_)               | (_)    |  _  /  ___| \n" \
"\\ `--. _ _ __ ___  _ __ | |___  _| | | \\ `--.  \n" \
" `--. \\ | '_ ` _ \\| '_ \\| | \\ \\/ / | | |`--. \\ \n" \
"/\\__/ / | | | | | | |_) | | |>  <\\ \\_/ /\\__/ / \n" \
"\\____/|_|_| |_| |_| .__/|_|_/_/\\_\\\\___/\\____/  \n" \
"                  | |                          \n" \
"                  |_|                          \n" \
"=============================================== \n"

#define SIMPLIX_VER_MAJ "0"
#define SIMPLIX_VER_MIN "1"

#define SIMPLIX_VER_FUL SIMPLIX_VER_MAJ"."SIMPLIX_VER_MIN

// UTS Specific Defines
#define SIMPLIX_UTS_SYSNAME "SimplixOS"
#define SIMPLIX_UTS_RELEASE "v"SIMPLIX_VER_FUL
#define SIMPLIX_UTS_VERSION "#1 SP "__DATE__" "__TIME__


#ifdef __GNUC__
  #ifdef __clang__
    #define COMPILER "Clang "__clang_version__
  #else
    #define COMPILER "GCC "__VERSION__
  #endif
#endif

#define AUTHOR_NOTE "written by Aun-Ali Zaidi."
#define COMPILE_NOTE "Compiled on "__DATE__", "__TIME__", using "COMPILER

#endif // SIMPLIX_DEFS_H

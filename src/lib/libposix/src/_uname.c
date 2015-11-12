/***********************************************************************
 * SimplixOS Operating System
 *
 * File: lib/libposix/src/sys/utsname/_uname.c
 *
 * Description:
 *      uname - retrieves system name structures.
 *      IEEE STD 1003.1, 2013 Edition
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

#include <sys/utsname.h>
#include <bos/k/defs.h>

#include <string.h>

/**
 * The uname() function shall store information
 * identifying the current system in the structure
 * pointed to by name.
 *
 * The uname() function uses the utsname structure
 * defined in <sys/utsname.h>.
 *
 * The uname() function shall return a string naming
 * the current system in the character array sysname.
 * Similarly, nodename shall contain the name of this
 * node within an implementation-defined communications
 * network. The arrays release and version shall further
 * identify the operating system. The array machine shall
 * contain a name that identifies the hardware that the
 * system is running on.
 *
 * @param  name Utsname struct pointing to system information.
 * @return      Successful information retrieval.
 */
int uname(struct utsname *name)
{
  // TODO: Retrieve information from /etc/hostname
  strcpy(name->nodename, "(none)");

  strcpy(name->sysname, BAS_UTS_SYSNAME);
  strcpy(name->release, BAS_UTS_RELEASE);
  strcpy(name->version, BAS_UTS_VERSION);

  //#ifdef _x86
    strcpy(name->machine, "i686");
  //#endif

  return 0;
}

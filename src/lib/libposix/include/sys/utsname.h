/***********************************************************************
 * BasicOS Operating System
 *
 * File: sys/utsname.h
 *
 * Description:
 *      Header that describes system name structures.
 *      IEEE STD 1003.1, 2013 Edition
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

#ifndef _SYS_UTSNAME_H_
#define _SYS_UTSNAME_H_

#define _UTS_LEN 64

struct utsname {
  char sysname[_UTS_LEN + 1]; /* [XSI] Name of Operating System */
  char nodename[_UTS_LEN + 1];  /* [XSI] Name of network node */
  char release[_UTS_LEN + 1]; /* [XSI] Release level */
  char version[_UTS_LEN + 1]; /* [XSI] Version level */
  char machine[_UTS_LEN + 1]; /* [XSI] Hardware type */
};

int uname(struct utsname *name);

#endif // _SYS_UTSNAME_H_

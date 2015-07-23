/************************************************************
 * BasicOS Operating System
 *
 * File: include/bos/k/arch/x86/int.h
 *
 * Description:
 *      Basic interrupt control.
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
 ************************************************************/
#ifndef INT_H
#define	INT_H

#include <bos/k/common.h>

#define INT_NMI_BIT     1 << 7
#define INT_NMI_CONTROL 0x70

void int_disable();
void int_enable();
void int_nmi_disable();
void int_nmi_enable();

#endif // INT_H

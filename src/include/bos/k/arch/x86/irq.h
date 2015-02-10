/************************************************************
 * BasicOS Operating System
 *
 * File: include/sys/irq.h
 *
 * Description:
 *      Defines IRQ PIC types.
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
 ************************************************************/

#ifndef _IRQ_H
#define	_IRQ_H

#include <bos/k/common.h>

#define IRQ0_DEFAULT_OFFSET 0x20
#define IRQ1_DEFAULT_OFFSET 0x28

#define IRQ_PIC0         0x20
#define IRQ_PIC0_COMMAND IRQ_PIC0
#define IRQ_PIC0_DATA    IRQ_PIC0 + 1

#define IRQ_PIC1         0xA0
#define IRQ_PIC1_COMMAND IRQ_PIC1
#define IRQ_PIC1_DATA    IRQ_PIC1 + 1

#define IRQ_PIC_INIT 0x11
#define IRQ_EOI      0x20

#define IRQ_PIC_8086_MODE 0x01
// TODO: add other ints

void irq_init();
bool irq_test(uint8_t int_n);

#endif

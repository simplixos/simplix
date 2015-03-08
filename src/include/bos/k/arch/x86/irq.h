/************************************************************
 * BasicOS Operating System
 *
 * File: include/bos/k/arch/x86/irq.h
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
#include <bos/k/arch/x86/idt.h>

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

#define IRQ_0 0
#define IRQ_1 1
#define IRQ_2 2
#define IRQ_3 3
#define IRQ_4 4
#define IRQ_5 5
#define IRQ_6 6
#define IRQ_7 7
#define IRQ_8 8
#define IRQ_9 9
#define IRQ_10 10
#define IRQ_11 11
#define IRQ_12 12
#define IRQ_13 13
#define IRQ_14 14
#define IRQ_15 15

#define IRQ_TYPE 6
#define IRQ_TYPE 6
// TODO: add other ints

void irq_init();
bool irq_test(uint8_t int_n);
void register_irq_handler(interrupt_handler_t irq_handler_info,int irq);

#endif

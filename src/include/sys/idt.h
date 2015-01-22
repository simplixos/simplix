/***********************************************************************
 * BasicOS Operating System
 *
 * File: include/sys/idt.h
 *
 * Description:
 *      Defines IDT structs, gates, functions, etc.
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

#ifndef IDT_H
#define	IDT_H

#include <sys/common.h>
#include <sys/vga.h>

#define IDT_TASK_GATE_32 1 | 1 << 2
#define IDT_INT_GATE_16  1 << 1 | 1 << 2
#define IDT_INT_GATE_32  1 << 1 | 1 << 2 | 1 << 3
#define IDT_TRAP_GATE_16 1 | 1 << 1 | 1 << 2
#define IDT_TRAP_GATE_32 1 | 1 << 1 | 1 << 2 | 1 << 3

#define IDT_RING_0 0
#define IDT_RING_1 1 << 5
#define IDT_RING_2 1 << 6
#define IDT_RING_3 1 << 5 | 1 << 6

typedef struct idt_entry {
  u16int base_low;
  u16int selector;
  u8int  zero;
  u8int  flags;
  u16int base_high;
} __attribute__((packed)) idt_entry_t, *pidt_entry_t;

typedef struct idt_pointer {
  u16int limit;
  u32int base;
} __attribute__((packed)) idt_pointer_t, *pidt_pointer_t;

typedef struct regs {
  u32int ds;
  u32int edi, esi, ebp, esp, ebx, edx, ecx, eax; 
  u32int int_no, err_code;    
  u32int eip, cs, eflags, useresp, ss; 
} regs_t, *pregs_t;

typedef void (*interrupt_handler_t) (regs_t);

void idt_init();
void idt_fill_entry(int entry, u32int handler, u8int ring, u8int type);
void idt_set_handler(int entry, interrupt_handler_t handler);

#endif

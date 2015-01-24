/***********************************************************************
 * BasicOS Operating System
 *
 * File: kernel/idt.c
 *
 * Description:
 *      Sets up higher-level IDT interface.
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

#include <bos/k/idt.h>

idt_entry_t         idt_entries[256];
idt_pointer_t       idt_pointer;
interrupt_handler_t int_handlers[256];

extern void isr0();
extern void isr1();
extern void isr2();
extern void isr3();
extern void isr4();
extern void isr5();
extern void isr6();
extern void isr7();
extern void isr8();
extern void isr9();
extern void isr10();
extern void isr11();
extern void isr12();
extern void isr13();
extern void isr14();
extern void isr15();
extern void isr16();
extern void isr17();
extern void isr18();
extern void isr19();
extern void isr20();
extern void isr21();
extern void isr22();
extern void isr23();
extern void isr24();
extern void isr25();
extern void isr26();
extern void isr27();
extern void isr28();
extern void isr29();
extern void isr30();
extern void isr31();

extern void idt_flush(u32int);

void isr_handler(regs_t regs);

void idt_init() {
  idt_pointer.limit = (sizeof(idt_entry_t) * 256) - 1;
  idt_pointer.base  = (u32int) &idt_entries;
  memclr(&idt_entries, sizeof(idt_entry_t) * 256);
  memclr(&int_handlers, sizeof(interrupt_handler_t) * 256);

  idt_fill_entry(0, (u32int) isr0, IDT_RING_0, IDT_INT_GATE_32);
  idt_fill_entry(1, (u32int) isr1, IDT_RING_0, IDT_INT_GATE_32);
  idt_fill_entry(2, (u32int) isr2, IDT_RING_0, IDT_INT_GATE_32);
  idt_fill_entry(3, (u32int) isr3, IDT_RING_0, IDT_INT_GATE_32);
  idt_fill_entry(4, (u32int) isr4, IDT_RING_0, IDT_INT_GATE_32);
  idt_fill_entry(5, (u32int) isr5, IDT_RING_0, IDT_TRAP_GATE_32);
  idt_fill_entry(6, (u32int) isr6, IDT_RING_0, IDT_INT_GATE_32);
  idt_fill_entry(7, (u32int) isr7, IDT_RING_0, IDT_INT_GATE_32);
  idt_fill_entry(8, (u32int) isr8, IDT_RING_0, IDT_INT_GATE_32);
  idt_fill_entry(9, (u32int) isr9, IDT_RING_0, IDT_INT_GATE_32);
  idt_fill_entry(10, (u32int) isr10, IDT_RING_0, IDT_INT_GATE_32);
  idt_fill_entry(11, (u32int) isr11, IDT_RING_0, IDT_INT_GATE_32);
  idt_fill_entry(12, (u32int) isr12, IDT_RING_0, IDT_INT_GATE_32);
  idt_fill_entry(13, (u32int) isr13, IDT_RING_0, IDT_INT_GATE_32);
  idt_fill_entry(14, (u32int) isr14, IDT_RING_0, IDT_INT_GATE_32);
  idt_fill_entry(15, (u32int) isr15, IDT_RING_0, IDT_INT_GATE_32);
  idt_fill_entry(16, (u32int) isr16, IDT_RING_0, IDT_INT_GATE_32);
  idt_fill_entry(17, (u32int) isr17, IDT_RING_0, IDT_INT_GATE_32);
  idt_fill_entry(18, (u32int) isr18, IDT_RING_0, IDT_INT_GATE_32);
  idt_fill_entry(19, (u32int) isr19, IDT_RING_0, IDT_INT_GATE_32);
  idt_fill_entry(20, (u32int) isr20, IDT_RING_0, IDT_INT_GATE_32);
  idt_fill_entry(21, (u32int) isr21, IDT_RING_0, IDT_INT_GATE_32);
  idt_fill_entry(22, (u32int) isr22, IDT_RING_0, IDT_INT_GATE_32);
  idt_fill_entry(23, (u32int) isr23, IDT_RING_0, IDT_INT_GATE_32);
  idt_fill_entry(24, (u32int) isr24, IDT_RING_0, IDT_INT_GATE_32);
  idt_fill_entry(25, (u32int) isr25, IDT_RING_0, IDT_INT_GATE_32);
  idt_fill_entry(26, (u32int) isr26, IDT_RING_0, IDT_INT_GATE_32);
  idt_fill_entry(27, (u32int) isr27, IDT_RING_0, IDT_INT_GATE_32);
  idt_fill_entry(28, (u32int) isr28, IDT_RING_0, IDT_INT_GATE_32);
  idt_fill_entry(29, (u32int) isr29, IDT_RING_0, IDT_INT_GATE_32);
  idt_fill_entry(30, (u32int) isr30, IDT_RING_0, IDT_INT_GATE_32);
  idt_fill_entry(31, (u32int) isr31, IDT_RING_0, IDT_INT_GATE_32);

  idt_flush((u32int) &idt_pointer);
}

void idt_fill_entry(int entry, u32int handler, u8int ring, u8int type) {
 	idt_entries[entry].base_low  = handler & 0xFFFF;
	idt_entries[entry].base_high = (handler >> 16) & 0xFFFF;
	idt_entries[entry].selector  = 0x08;
	idt_entries[entry].zero = 0;
	idt_entries[entry].flags = ring | type | 1 << 7;
}

void isr_handler(regs_t regs) {
	char buf[64];
	vga_write(buf);
	vga_write("[EXCEPTION] interrupt ");
	vga_write_dec(regs.int_no);
	vga_write(" raised.\n");
	vga_write(buf);
	if (int_handlers[regs.int_no] != NULL)
		int_handlers[regs.int_no](regs);
}

void idt_set_handler(int entry, interrupt_handler_t handler) {
	int_handlers[entry] = handler;
}

/***********************************************************************
 * BasicOS Operating System
 *
 * File: kernel/arch/x86/idt.c
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

#include <bos/k/arch/x86/idt.h>
#include <bos/k/arch/x86/panic.h>

#include <libk/stdio.h>
#include <libk/string.h>

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

extern void idt_flush(uint32_t);

void isr_handler(regs_t regs);

void idt_init() {
  idt_pointer.limit = (sizeof(idt_entry_t) * 256) - 1;
  idt_pointer.base  = (uint32_t) &idt_entries;
  memclr(&idt_entries, sizeof(idt_entry_t) * 256);
  memclr(&int_handlers, sizeof(interrupt_handler_t) * 256);

  idt_fill_entry(0, (uint32_t) isr0, IDT_RING_0, IDT_INT_GATE_32);
  idt_fill_entry(1, (uint32_t) isr1, IDT_RING_0, IDT_INT_GATE_32);
  idt_fill_entry(2, (uint32_t) isr2, IDT_RING_0, IDT_INT_GATE_32);
  idt_fill_entry(3, (uint32_t) isr3, IDT_RING_0, IDT_INT_GATE_32);
  idt_fill_entry(4, (uint32_t) isr4, IDT_RING_0, IDT_INT_GATE_32);
  idt_fill_entry(5, (uint32_t) isr5, IDT_RING_0, IDT_TRAP_GATE_32);
  idt_fill_entry(6, (uint32_t) isr6, IDT_RING_0, IDT_INT_GATE_32);
  idt_fill_entry(7, (uint32_t) isr7, IDT_RING_0, IDT_INT_GATE_32);
  idt_fill_entry(8, (uint32_t) isr8, IDT_RING_0, IDT_INT_GATE_32);
  idt_fill_entry(9, (uint32_t) isr9, IDT_RING_0, IDT_INT_GATE_32);
  idt_fill_entry(10, (uint32_t) isr10, IDT_RING_0, IDT_INT_GATE_32);
  idt_fill_entry(11, (uint32_t) isr11, IDT_RING_0, IDT_INT_GATE_32);
  idt_fill_entry(12, (uint32_t) isr12, IDT_RING_0, IDT_INT_GATE_32);
  idt_fill_entry(13, (uint32_t) isr13, IDT_RING_0, IDT_INT_GATE_32);
  idt_fill_entry(14, (uint32_t) isr14, IDT_RING_0, IDT_INT_GATE_32);
  idt_fill_entry(15, (uint32_t) isr15, IDT_RING_0, IDT_INT_GATE_32);
  idt_fill_entry(16, (uint32_t) isr16, IDT_RING_0, IDT_INT_GATE_32);
  idt_fill_entry(17, (uint32_t) isr17, IDT_RING_0, IDT_INT_GATE_32);
  idt_fill_entry(18, (uint32_t) isr18, IDT_RING_0, IDT_INT_GATE_32);
  idt_fill_entry(19, (uint32_t) isr19, IDT_RING_0, IDT_INT_GATE_32);
  idt_fill_entry(20, (uint32_t) isr20, IDT_RING_0, IDT_INT_GATE_32);
  idt_fill_entry(21, (uint32_t) isr21, IDT_RING_0, IDT_INT_GATE_32);
  idt_fill_entry(22, (uint32_t) isr22, IDT_RING_0, IDT_INT_GATE_32);
  idt_fill_entry(23, (uint32_t) isr23, IDT_RING_0, IDT_INT_GATE_32);
  idt_fill_entry(24, (uint32_t) isr24, IDT_RING_0, IDT_INT_GATE_32);
  idt_fill_entry(25, (uint32_t) isr25, IDT_RING_0, IDT_INT_GATE_32);
  idt_fill_entry(26, (uint32_t) isr26, IDT_RING_0, IDT_INT_GATE_32);
  idt_fill_entry(27, (uint32_t) isr27, IDT_RING_0, IDT_INT_GATE_32);
  idt_fill_entry(28, (uint32_t) isr28, IDT_RING_0, IDT_INT_GATE_32);
  idt_fill_entry(29, (uint32_t) isr29, IDT_RING_0, IDT_INT_GATE_32);
  idt_fill_entry(30, (uint32_t) isr30, IDT_RING_0, IDT_INT_GATE_32);
  idt_fill_entry(31, (uint32_t) isr31, IDT_RING_0, IDT_INT_GATE_32);

  idt_flush((uint32_t) &idt_pointer);
}

void idt_fill_entry(int entry, uint32_t handler, uint8_t ring, uint8_t type) {
 	idt_entries[entry].base_low  = handler & 0xFFFF;
	idt_entries[entry].base_high = (handler >> 16) & 0xFFFF;
	idt_entries[entry].selector  = 0x08;
	idt_entries[entry].zero = 0;
	idt_entries[entry].flags = ring | type | 1 << 7;
}

void isr_handler(regs_t regs) {
	char buf[64] = {0};
	kprintf(buf);
	//kprintf("\n[EXCEPTION] interrupt ");
	//kprintf(regs.int_no);
	//kprintf(" raised.\n");
	kprintf("\n[EXCEPTION] Interrupt %d raised!\n", regs.int_no);
	kprintf(buf);
	if (int_handlers[regs.int_no] != NULL)
		int_handlers[regs.int_no](regs);
	_k_panic("Interrupt raised!", __FILE__, __LINE__);
}

void idt_set_handler(int entry, interrupt_handler_t handler) {
	int_handlers[entry] = handler;
}

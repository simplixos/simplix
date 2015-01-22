/************************************************************
 * BasicOS Operating System
 *
 * File: kernel/irq.c
 *
 * Description:
 *      Handles initialization of IRQ and setup of highe level
 *	interface.
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

#include <sys/irq.h>
#include <sys/idt.h>

u8int irq0_offset = IRQ0_DEFAULT_OFFSET;
u8int irq1_offset = IRQ1_DEFAULT_OFFSET;

interrupt_handler_t irq_handlers[16];

extern void irq0();
extern void irq1();
extern void irq2();
extern void irq3();
extern void irq4();
extern void irq5();
extern void irq6();
extern void irq7();
extern void irq8();
extern void irq9();
extern void irq10();
extern void irq11();
extern void irq12();
extern void irq13();
extern void irq14();
extern void irq15();

void irq_init() {
  u8int pic0_icw4, pic1_icw4;
  pic0_icw4 = inb(IRQ_PIC0_DATA);
  pic1_icw4 = inb(IRQ_PIC1_DATA);
  outb(IRQ_PIC0_COMMAND, IRQ_PIC_INIT);
  outb(IRQ_PIC1_COMMAND, IRQ_PIC_INIT);
  outb(IRQ_PIC0_DATA, irq0_offset);
  outb(IRQ_PIC1_DATA, irq1_offset);
  outb(IRQ_PIC0_DATA, 0x04);
  outb(IRQ_PIC1_DATA, 0x02);
  outb(IRQ_PIC0_DATA, IRQ_PIC_8086_MODE);
  outb(IRQ_PIC1_DATA, IRQ_PIC_8086_MODE);
  outb(IRQ_PIC0_DATA, pic0_icw4);
  outb(IRQ_PIC1_DATA, pic1_icw4);

  idt_fill_entry(irq0_offset,      (u32int) irq0,  IDT_RING_0, IDT_INT_GATE_32);
  idt_fill_entry(irq0_offset + 1,  (u32int) irq1,  IDT_RING_0, IDT_INT_GATE_32);
  idt_fill_entry(irq0_offset + 2,  (u32int) irq2,  IDT_RING_0, IDT_INT_GATE_32);
  idt_fill_entry(irq0_offset + 3,  (u32int) irq3,  IDT_RING_0, IDT_INT_GATE_32);
  idt_fill_entry(irq0_offset + 4,  (u32int) irq4,  IDT_RING_0, IDT_INT_GATE_32);
  idt_fill_entry(irq0_offset + 5,  (u32int) irq5,  IDT_RING_0, IDT_TRAP_GATE_32);
  idt_fill_entry(irq0_offset + 6,  (u32int) irq6,  IDT_RING_0, IDT_INT_GATE_32);
  idt_fill_entry(irq0_offset + 7,  (u32int) irq7,  IDT_RING_0, IDT_INT_GATE_32);
  idt_fill_entry(irq1_offset + 8,  (u32int) irq8,  IDT_RING_0, IDT_INT_GATE_32);
  idt_fill_entry(irq1_offset + 9,  (u32int) irq9,  IDT_RING_0, IDT_INT_GATE_32);
  idt_fill_entry(irq1_offset + 10, (u32int) irq10, IDT_RING_0, IDT_INT_GATE_32);
  idt_fill_entry(irq1_offset + 11, (u32int) irq11, IDT_RING_0, IDT_INT_GATE_32);
  idt_fill_entry(irq1_offset + 12, (u32int) irq12, IDT_RING_0, IDT_INT_GATE_32);
  idt_fill_entry(irq1_offset + 13, (u32int) irq13, IDT_RING_0, IDT_INT_GATE_32);
  idt_fill_entry(irq1_offset + 14, (u32int) irq14, IDT_RING_0, IDT_INT_GATE_32);
  idt_fill_entry(irq1_offset + 15, (u32int) irq15, IDT_RING_0, IDT_INT_GATE_32);
}

bool irq_is_irq(u8int int_n) {
  return ((int_n >= irq0_offset && int_n < (irq0_offset + 8)) ||
          (int_n >= irq1_offset && int_n < (irq1_offset + 8))) ? TRUE : 
FALSE;
}

void irq_handler(regs_t regs) {
  if (irq_handlers[regs.err_code] != NULL)
    irq_handlers[regs.err_code](regs);

  if (regs.err_code > 7)
    outb(IRQ_PIC1_COMMAND, IRQ_EOI);
  outb(IRQ_PIC0_COMMAND, IRQ_EOI);
}


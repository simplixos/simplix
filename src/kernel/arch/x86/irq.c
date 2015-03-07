/************************************************************
 * BasicOS Operating System
 *
 * File: kernel/arch/x86/irq.c
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

#include <bos/k/arch/x86/irq.h>

#define MAX_IRQ	16

/*Hold information of IRQ callback ptr and */
typedef struct __irq_handler_info__
{
	interrupt_handler_t irq_handler_ptr;
	int inuse;
}irq_handler_info;

uint8_t irq0_offset = IRQ0_DEFAULT_OFFSET;
uint8_t irq1_offset = IRQ1_DEFAULT_OFFSET;

irq_handler_info irq_handlers[MAX_IRQ];

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

void irq_init() 
{
  uint8_t pic0_icw4, pic1_icw4;
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

  idt_fill_entry(irq0_offset,      (uint32_t) irq0,  IDT_RING_0, IDT_INT_GATE_32);
  idt_fill_entry(irq0_offset + 1,  (uint32_t) irq1,  IDT_RING_0, IDT_INT_GATE_32);
  idt_fill_entry(irq0_offset + 2,  (uint32_t) irq2,  IDT_RING_0, IDT_INT_GATE_32);
  idt_fill_entry(irq0_offset + 3,  (uint32_t) irq3,  IDT_RING_0, IDT_INT_GATE_32);
  idt_fill_entry(irq0_offset + 4,  (uint32_t) irq4,  IDT_RING_0, IDT_INT_GATE_32);
  idt_fill_entry(irq0_offset + 5,  (uint32_t) irq5,  IDT_RING_0, IDT_TRAP_GATE_32);
  idt_fill_entry(irq0_offset + 6,  (uint32_t) irq6,  IDT_RING_0, IDT_INT_GATE_32);
  idt_fill_entry(irq0_offset + 7,  (uint32_t) irq7,  IDT_RING_0, IDT_INT_GATE_32);
  idt_fill_entry(irq1_offset + 8,  (uint32_t) irq8,  IDT_RING_0, IDT_INT_GATE_32);
  idt_fill_entry(irq1_offset + 9,  (uint32_t) irq9,  IDT_RING_0, IDT_INT_GATE_32);
  idt_fill_entry(irq1_offset + 10, (uint32_t) irq10, IDT_RING_0, IDT_INT_GATE_32);
  idt_fill_entry(irq1_offset + 11, (uint32_t) irq11, IDT_RING_0, IDT_INT_GATE_32);
  idt_fill_entry(irq1_offset + 12, (uint32_t) irq12, IDT_RING_0, IDT_INT_GATE_32);
  idt_fill_entry(irq1_offset + 13, (uint32_t) irq13, IDT_RING_0, IDT_INT_GATE_32);
  idt_fill_entry(irq1_offset + 14, (uint32_t) irq14, IDT_RING_0, IDT_INT_GATE_32);
  idt_fill_entry(irq1_offset + 15, (uint32_t) irq15, IDT_RING_0, IDT_INT_GATE_32);
  
  for(int i =0 ;i<MAX_IRQ ;i++)
  {
  	irq_handlers[i].inuse =0;
	irq_handlers[i].irq_handler_ptr = NULL;
  }
}

bool irq_is_irq(uint8_t int_n) 
{
  return ((int_n >= irq0_offset && int_n < (irq0_offset + 8)) ||
          (int_n >= irq1_offset && int_n < (irq1_offset + 8))) ? TRUE : 
FALSE;
}

void irq_handler(regs_t regs) 
{
  if (irq_handlers[regs.err_code].irq_handler_ptr != NULL)
    irq_handlers[regs.err_code].irq_handler_ptr(regs);

  if (regs.err_code > 7)
    outb(IRQ_PIC1_COMMAND, IRQ_EOI);//inform slave PIC of IRQ processing done
  outb(IRQ_PIC0_COMMAND, IRQ_EOI);//inform master PIC of IRQ processing done
}

void register_irq_handler(interrupt_handler_t irq_handler_info ,int irq)
{
  if((irq >= IRQ_0) && (irq <= IRQ_15))
  {
    if(irq_handlers[irq].inuse == 0)
    {
      irq_handlers[irq].irq_handler_ptr = irq_handler_info;
    }
  }
}


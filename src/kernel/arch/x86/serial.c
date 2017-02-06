/***********************************************************************
 * SimplixOS Operating System
 *
 * File: kernel/arch/x86/serial.c
 *
 * Description:
 *       Source file contains implementation of Basic Serial Driver.
 *	 Serial driver for 8250
 *
 * License:
 * SimplixOS Operating System - An experimental operating system.
 * Copyright (C) 2015-17 Aun-Ali Zaidi and its contributors.
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

#include <simplix/k/arch/x86/irq.h>
#include <simplix/k/arch/x86/serial.h>
#include <simplix/k/arch/x86/panic.h>

static int serial_init_done = 0;

#define CHECK_INIT_DONE(x) if(!x) { kprintf("serial device not found "); return;}
#define CHECK_INIT_DONE_RET(x) if(!x) { kprintf("serial device not found "); return serial_init_done;}

#define SERIAL_DEVICE "8250"

/*prototype*/
static void serial_irq_handler (regs_t);
static int serial_read_char(void);

/* Initializes serial registers and installs IRQ3/4 ISR*/
void serial_init()
{
	short int div_latch_val;
	/* Disable all interrupts , set first bit to 0 */
	outb(SERIAL_BASE_ADDR_COM1 + SERIAL_INTR_EN_REG, 	0x00);

	/* Enable DLAB (Divisor Latch Access Bit) , set 8th bit to 1 since we need to set baud */
	outb(SERIAL_BASE_ADDR_COM1 + SERIAL_LINE_CTRL_REG , 	0x80);

	/* Set Baud Rate
	 * Divisor latch bytes has High byte(offset = 1) and Low Byte (offset = 0)
	 * Div Latch Val = clock/baud rate
	 */
	div_latch_val = SERIAL_HW_CLK/SERIAL_BAUD;

	/*Set low byte and high byte of div latch*/
	//TODO : uart clock required , hardcode baud to 115200

	outb(SERIAL_BASE_ADDR_COM1 + SERIAL_DIV_LATCH_LOW, /*0x0C*/div_latch_val);
	outb(SERIAL_BASE_ADDR_COM1 + SERIAL_DIV_LATCH_HI,  /*0x00*/div_latch_val>>8);

	/* 8 bits, no parity, one stop bit ,disable divisor latch */
	outb(SERIAL_BASE_ADDR_COM1 + SERIAL_LINE_CTRL_REG, 0x03);

	/* 8250 compability mode ,disable FIFO */
	outb(SERIAL_BASE_ADDR_COM1 + SERIAL_FIFO_CTRL_REG, 0x00);

	/*Enable Interrupts*/
	outb(SERIAL_BASE_ADDR_COM1 + SERIAL_INTR_EN_REG, 0x01);

	/*register IRQ handlers*/
	register_irq_handler(serial_irq_handler , IRQ_4);
	register_irq_handler(serial_irq_handler , IRQ_3);

	kprintf("IRQ 3 and IRQ 4 handlers registerd \n");
	kprintf("Serial Init is done \n");

	if(inb(SERIAL_BASE_ADDR_COM1+5) == 0xFF)
	{
		kprintf("Serial Init failed! No serial port!\n");
		_k_panic("[TTY] Serial device not found! Serial Init Failed!\n", __FILE__, __LINE__);
	}
	else
	{
		/*clear any pending interrupts and TX buffer*/
		inb(SERIAL_BASE_ADDR_COM1+SERIAL_INTR_IDENT_REG );
		inb(SERIAL_BASE_ADDR_COM1+SERIAL_REC_BUF_REG );
		serial_init_done = 1;
		serial_write_string("serial_device: " SERIAL_DEVICE"\n");
		serial_write_string("Serial init complete!\n");
	}
}

/*IRQ callback*/
static void serial_irq_handler (regs_t reg)
{
	CHECK_INIT_DONE(serial_init_done)
	switch(reg.err_code)
	{
		case IRQ_3:
			kprintf("Received IRQ 3 from COM3 port");
			break;
		case IRQ_4:
			kprintf("Received IRQ 4 from COM4 port");
			int data;
			do {
				data = serial_read_char();
				kprintf((char *)data);
			} while(data != SERIAL_NO_DATA);
			break;
		default:
			kprintf("Received unknown IRQ");
			break;
	}
}

//FIXME A better routine
static void serial_delay(void)
{
	inb(0x84);
	inb(0x84);
	inb(0x84);
	inb(0x84);
}

void serial_write_string(const char * string)
{
	CHECK_INIT_DONE(serial_init_done)
	while(*string != '\0')
	serial_write_char(*string++);
}

void serial_write_char(int c)
{
	CHECK_INIT_DONE(serial_init_done)
	int i;
	for (i = 0; !(inb(SERIAL_BASE_ADDR_COM1 + SERIAL_LINE_STAT_REG) & SERIAL_OUT_DATA_READY) && i < 128; i++)
		serial_delay();
	outb(SERIAL_BASE_ADDR_COM1+SERIAL_TX_BUF_REG, c);
}

static int serial_read_char(void)
{
	CHECK_INIT_DONE_RET(serial_init_done)
	if(!(inb(SERIAL_BASE_ADDR_COM1+SERIAL_LINE_STAT_REG) & SERIAL_IN_DATA_READY))
		return SERIAL_NO_DATA;
	return inb(SERIAL_BASE_ADDR_COM1+SERIAL_REC_BUF_REG);
}

int isSerialInitDone(void)
{
	return serial_init_done;
}

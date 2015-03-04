/***********************************************************************
 * BasicOS Operating System
 *
 * File: include/bos/k/arch/x86/serial.h
 *
 * Description:
 *      Serial Port API's
 *
 * License:
 * BasicOS Operating System - An experimental operating system.
 * Copyright (C) 2015 Rahul Ramesh
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

#ifndef SERIAL_H
#define	SERIAL_H

/* Define headers to program serial port registers on x86 */
/* Intel x86 uses 0x3F8 to 0x3Ff I/O mapped addresses for controlling UART Registers */

#define SERIAL_HW_CLK		152000	//UART countdown timer
#define SERIAL_BASE_ADDR_COM1 	0x3F8 	//COM1 IRQ4
#define SERIAL_BASE_ADDR_COM2 	0x2F8 	//COM2 IRQ3
#define SERIAL_BASE_ADDR_COM3 	0x3E8 	//COM3 IRQ4
#define SERIAL_BASE_ADDR_COM4 	0x2E8 	//COM4 IRQ3

/*Interrupt Enable Bits*/

#define SERIAL_IE_BIT_0		0	/* Enable interrupt to receive data */
#define SERIAL_IE_BIT_1		1	/* Receive interrupt when tx buffer in UART has finished transmitting characters ,PIC 16550 */
#define SERIAL_IE_BIT_2		2	/* Receiver line status , something has gone wrong */
#define SERIAL_IE_BIT_3		3	/* Modem status interrupt , something has changed so act accordingly*/
#define SERIAL_IE_BIT_4		4	/* Enable sleep mode UART 16750	*/
#define SERIAL_IE_BIT_5		5	/* Enable low power mode UART 16750	*/
#define SERIAL_IE_BIT_6		6	/* Reserved for future */
#define SERIAL_IE_BIT_7		7	/* Reserved for future */

/*Interrupt Identification Register*/

/*
 * BIT 0				Interrupt Pending Flag
 * ----------------------------------
 * BIT 3 	BIT 2 		BIT 1
 * ----------------------------------
 *  0		 0		 0      Modem Status Interrupt				--> Read Modem Status Register(MSR)
 *  0		 0		 1	Transmitter Holding Register Empty Interrupt	--> Read Interrupt Identification Register(IIR) or
											    Write to Transmit Holding Buffer(THR)
 *  0		 1		 0	Received Data Available Interrupt		--> Read Receive Buffer Register(RBR)
 *  0		 1		 1	Receiver Line Status Interrupt			--> Read Line Status Register(LSR)
 *  1		 0		 0	Reserved
 *  1		 0		 1	Reserved
 *  1		 1		 0	Time-out Interrupt Pending			--> Read Receive Buffer Register(RBR)
 *  1		 1		 1	Reserved
 * BIT 4				Reserved
 * BIT 5				64 Byte FIFO Enabled (16750 only)
 * ------------------
 * BIT 7 	BIT 6
 * ------------------
 *  0		 0			No FIFO on chip
 *  0		 1			Reserved condition
 *  1		 0			FIFO enabled, but not functioning
 *  1		 1			FIFO enabled
 */

/*FIFO Control Register*/
 
/*
 * BIT 0		Enable FIFOs , write 0 to clear FIFO 
 * BIT 1		Clear Receive FIFO
 * BIT 2		Clear Transmit FIFO
 * BIT 3		DMA Mode Select
 * BIT 4		Reserved
 * BIT 5		Enable 64 Byte FIFO (16750)
 * ------------------
 * BIT 7 	BIT 6 	Threshold value after which application driver needs to read FIFO before overflow.
 * ------------------
 *  0		 0	1 byte
 *  0		 1	4 bytes
 *  1		 0	8 bytes
 *  1		 1	14 bytes
 */

/*Line Control Register*/

/*
 * ------------------
 * BIT 1 	BIT 0   		Bits to indicate number of data bits sent
 * ------------------
 *  0		 0			5 bits
 *  0		 1			6 bits
 *  1		 0			7 bits
 *  1		 1			8 bits
 * ------------------
 * BIT 2				Number of stopping bits { 0 = 1 stopping bits , 1 = 2 stopping bits }
 * ----------------------------------
 * BIT 5 	BIT 4 		BIT 3	Select Parity for data integrity
 * ----------------------------------
 *  0		 0		 0      No Parity
 *  0		 0		 1	Odd Parity
 *  0		 1		 0	UnUsed
 *  0		 1		 1	Even Parity
 *  1		 0		 0	UnUsed
 *  1		 0		 1	Mark
 *  1		 1		 0	UnUsed
 *  1		 1		 1	Space
 *  ---------------------------------
 * BIT 6				Divisor Latch Access Bit
 * BIT 7				Set Break Enable
 */

/*Modem Control Register*/

/*			Unused so far
 * BIT 0		Data Terminal Ready
 * BIT 1		Request to send
 * BIT 2		Aux Ouput 1
 * BIT 3		Aux Ouput 2
 * BIT 4		Loopback mode
 * BIT 5		Autoflow Control Enabled (16750)
 * BIT 6		Reserved
 * BIT 7		Reserved
 */

/* Line Status Register */  

/*			Error registers
 * BIT 0		Data Ready
 * BIT 1		Overrun Error
 * BIT 2		Parity Error
 * BIT 3		Framing Error
 * BIT 4		Break Interrupt
 * BIT 5		Empty Transmitter Holding Register
 * BIT 6		Empty Data Holding Registers
 * BIT 7		Error in Received FIFO
 */

/* Modem Status Register */  

/*			Status of modem
 * BIT 0		Delta Clear To Send
 * BIT 1		Delta Data Set Ready
 * BIT 2		Trailing Edge Ring Indicator
 * BIT 3		Delta Data Carrier Detect
 * BIT 4		Clear To Send
 * BIT 5		Data Set Ready
 * BIT 6		Ring Indicator
 * BIT 7		Carrier Detect
 */

/* Define Offsets to UART registers*/

#define SERIAL_REC_BUF_REG 	0 	/* Receive Buffer in read mode  			{ DLAB = 0 } */
#define SERIAL_TX_BUF_REG  	0	/* Transmitter Holding Buffer in write mode		{ DLAB = 0 } */
#define SERIAL_DIV_LATCH_LOW  	0	/* Divisor Low Byte					{ DLAB = 1 } */

#define SERIAL_INTR_EN_REG 	1	/* Interrupt Enable (Read/Write)			{ DLAB = 0 } */
#define SERIAL_DIV_LATCH_HI 	1	/* Divisor High Byte					{ DLAB = 1 } */

#define SERIAL_INTR_IDENT_REG 	2	/* Interrupt Identification Register (Read)		{ DLAB = X } */
#define SERIAL_FIFO_CTRL_REG 	2	/* FIFO Control Register (Write)			{ DLAB = X } */

#define SERIAL_LINE_CTRL_REG 	3	/* Line Control Register (Read/Write)			{ DLAB = X } */

#define SERIAL_MODEM_CTRL_REG 	4	/* Modem Control Register (Read/Write)			{ DLAB = X } */

#define SERIAL_LINE_STAT_REG 	5	/* Line Status Register (Read)				{ DLAB = X } */

#define SERIAL_MODEM_STAT_REG 	6	/* Modem Status Register (Read)				{ DLAB = X } */

#define SERIAL_SCRATCH_REG 	7	/* Scratch Register (Read/Write)			{ DLAB = X } */

#endif

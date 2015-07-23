;---------------------------------------------------------------------------
;       BasicOS Operating System
;
;       File: kernel/boot.s
;
;       Descripition:
;               Loads bootstrap 32-bit kernel into memory, sets up paging,
;               jumps to 64-bit, and sets up GDT.
;
;       License:
;       BasicOS Operating System - An experimental operating system
;       Copyright (C) 2015 Aun-Ali Zaidi and its contributors.
;
;       This program is free software: you can redistribute it and/or modify
;       it under the terms of the GNU General Public License as published by
;       the Free Software Foundation, either version 3 of the License, or
;       (at your option) any later version.
;
;       This program is distributed in the hope that it will be useful,
;       but WITHOUT ANY WARRANTY; without even the implied warranty of
;       MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the
;       GNU General Public License for more details.
;
;       You should have received a copy of the GNU General Public License
;       along with this program. If not, see <http://www.gnu.org/licenses/>.
;---------------------------------------------------------------------------

[BITS 32]		; Load up kernel in protected mode (32-bit,paging) then jump to long mode (64-bit).
[section .text]		; Keep NASM happy
[global trampoline]	; Our start function.
[extern _k_early]	; C kernel early events
[extern _k_main]	; our C kernel main

; Multiboot constants
MULTIBOOT_PAGE_ALIGN	equ 1<<0
MULTIBOOT_MEMORY_INFO	equ 1<<1
MULTIBOOT_VIDEO_INFO	equ 1<<2

MULTIBOOT_HEADER_MAGIC	equ 0x1BADB002
MULTIBOOT_HEADER_FLAGS	equ (MULTIBOOT_PAGE_ALIGN | MULTIBOOT_MEMORY_INFO | MULTIBOOT_VIDEO_INFO)
MULTIBOOT_CHECKSUM	equ -(MULTIBOOT_HEADER_MAGIC + MULTIBOOT_HEADER_FLAGS)

; Multiboot 2 constants
MULTIBOOT2_HEADER_MAGIC		equ 0xe85250d6
MULTIBOOT2_HEADER_LENGTH	equ MultibootHeader2End - MultibootHeader2
MULTIBOOT2_CHECKSUM		equ (-(MULTIBOOT2_HEADER_MAGIC + 0 + MULTIBOOT2_HEADER_LENGTH) & 0xffffffff)

STACKSIZE equ 0x4000	; 1K Stack

; Multiboot header (needed to boot by GRUB)
[section .multiboot]	; Multiboot section (0x1000)
ALIGN 8			; Align to 8Kb pages

				; Offset | Description
dd MULTIBOOT_HEADER_MAGIC	;      0 - Multiboot Header Magic
dd MULTIBOOT_HEADER_FLAGS	;      4 - Multiboot Header Flags
dd MULTIBOOT_CHECKSUM		;      8 - Multiboot Checksum
dd 0		;      c - Multiboot Header Address (16-bit flag)
dd 0		;     10 - Load Address (16-bit flag)
dd 0		;     14 - Load End Address (16-bit flag)
dd 0		;

; the basic 32-bit loader that will switch to the 64-bit
trampoline:

	cli
	hlt

	; here's the trick; we load a GDT with a base address
	; of 0x40000000 for the code (0x08) and data (0x10) segments
	lgdt [trickgdt]		; Load the GDT from location 'trickgdt'
	mov ax, 0x10		; Set the A-register to 0x10
	mov ds, ax		; Set the DS-register to ax(0x10)
	mov es, ax		; Set the ES-register to ax(0x10)
	mov fs, ax		; Set the FS-register to ax(0x10)
	mov gs, ax		; Set the GS-register to ax(0x10)
	mov ss, ax		; Set the SS-register to ax(0x10)

	; jump to the higherhalf kernel
	jmp 0x08:higherhalf	; Jump to the 'higherhalf' code segment with 0x08 as the offset

higherhalf:
	; from now the CPU will automatically translate every address
	; by adding the base 0x40000000

	; set up a new stack for our kernel
	mov esp, sys_stack	; Set the stack pointer register to 'sys_stack'

	; jump to early setup functions in C
	call _k_early		; Call the '_k_early' function in C file, kernel/kernel.c

	; jump to our C kernel ;)
	call _k_main		; Call the '_k_main' function in C file, kernel/kernel.c

	; just a simple protection
	cli			; Clear the interrupts
	hlt			; Halt the CPU

[global gdt_flush]	; make 'gdt_flush' accessible from C code
[extern gp]		; tells the assembler to look at C code for 'gp'

; this function does the same thing as the 'start32' one, this time with
; real GDT.
gdt_flush:
	lgdt [gp]	; Load the GDT from external variable 'gp'
	mov ax, 0x10	; Set the A-register to ax(0x10)
	mov ds, ax	; Set the DS-register to ax(0x10)
	mov es, ax	; Set the ES-register to ax(0x10)
	mov fs, ax	; Set the FS-register to ax(0x10)
	mov gs, ax	; Set the GS-register to ax(0x10)
	mov ss, ax	; Set the SS-register to ax(0x10)
	jmp 0x08:flush2	; Jump to the 'flush2' code segment and with 0x08 as the offset

flush2:
	ret		; Return to original context

[section .setup] ; tells assembler to include this data in the '.setup' section

trickgdt:
	dw gdt_end - gdt - 1	; size of the GDT
	dd gdt			; linear address of the GDT

gdt:
	dd 0, 0							; null gate
	db 0xFF, 0xFF, 0, 0, 0, 10011010b, 11001111b, 0x40	; code selector 0x08: base 0x40000000, limit 0xFFFFFFFF, type 0x9A, granularity 0xCF
  db 0xFF, 0xFF, 0, 0, 0, 10010010b, 11001111b, 0x40	; data selector 0x10: base 0x40000000, limit 0xFFFFFFFF, type 0x92, granularity 0xCF
  db 0xFF, 0xFF, 0, 0, 0, 11111010b, 11001111b, 0x40	; user mode code selector: base 0x40000000, limit 0xFFFFFFFFF, type 0xFA, granularity 0xCF
  db 0xFF, 0xFF, 0, 0, 0, 11110010b, 11001111b, 0x40	; user mode data selector: base 0x40000000, limit 0xFFFFFFFFF, type 0xF2, granularity 0xCF

gdt_end:

[section .bss]

resb 0x1000	; Reserve 4k bytes
sys_stack:
	; our kernel stack

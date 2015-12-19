;---------------------------------------------------------------------------
;	SimplixOS Operating System
;
;	File: kernel/arch/x86/boot.s
;
;	Descripition:
;		Loads 32-bit kernel into memory and sets up paging and GDT.
;
;	License:
;	SimplixOS Operating System - An experimental operating system
;	Copyright (C) 2015 Aun-Ali Zaidi and its contributors.
;
;	This program is free software: you can redistribute it and/or modify
;	it under the terms of the GNU General Public License as published by
;	the Free Software Foundation, either version 3 of the License, or
;	(at your option) any later version.
;
;	This program is distributed in the hope that it will be useful,
;	but WITHOUT ANY WARRANTY; without even the implied warranty of
;	MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the
;	GNU General Public License for more details.
;
;	You should have received a copy of the GNU General Public License
;	along with this program. If not, see <http://www.gnu.org/licenses/>.
;---------------------------------------------------------------------------

[BITS 32]		; 32 bit code

; Multiboot constants
MULTIBOOT_PAGE_ALIGN    equ 1<<0
MULTIBOOT_MEMORY_INFO   equ 1<<1
MULTIBOOT_HEADER_MAGIC  equ 0x1BADB002
MULTIBOOT_HEADER_FLAGS  equ MULTIBOOT_PAGE_ALIGN | MULTIBOOT_MEMORY_INFO
MULTIBOOT_CHECKSUM      equ -(MULTIBOOT_HEADER_MAGIC + MULTIBOOT_HEADER_FLAGS)

KERNEL_VIRTUAL_BASE equ 0xC0000000                  ; 3GB

[section .multiboot]
; Multiboot header (needed to boot from GRUB)
ALIGN 4
multiboot_header:
        dd MULTIBOOT_HEADER_MAGIC
        dd MULTIBOOT_HEADER_FLAGS
        dd MULTIBOOT_CHECKSUM

[section .text]		; keep NASM happy
[global start]		; make 'start' function global
[extern _k_early]	; C kernel early events
[extern _k_main]	; our C kernel main
; the kernel entry point
start:
	mov ecx ,eax ;save the magic number where grub stores in eax since we are loading trickgdt

        ; here's the trick: we load a GDT with a base address
        ; of 0x40000000 for the code (0x08) and data (0x10) segments
        lgdt [trickgdt]
        mov ax, 0x10
        mov ds, ax
        mov es, ax
        mov fs, ax
        mov gs, ax
        mov ss, ax

        ; jump to the higher half kernel
        jmp 0x08:higherhalf

higherhalf:
        ; from now the CPU will translate automatically every address
        ; by adding the base 0x40000000

        mov esp, sys_stack ; set up a new stack for our kernel

	push ecx ; push bootloader magic that we saved

	add ebx, KERNEL_VIRTUAL_BASE ;since ebx points to phy address add the kernel base address else will lead to triple fault

	push ebx ; push multiboot structure pointer on the stack for _k_early

	call _k_early ; jump to early setup functions in C

        call _k_main ; jump to our C kernel ;)

        ; just a simple protection...
        cli
	hlt

[global gdt_flush] ; make 'gdt_flush' accessible from C code
[extern gp]        ; tells the assembler to look at C code for 'gp'

; this function does the same thing of the 'start' one, this time with
; the real GDT
gdt_flush:
        lgdt [gp]
        mov ax, 0x10
        mov ds, ax
        mov es, ax
        mov fs, ax
        mov gs, ax
        mov ss, ax
        jmp 0x08:flush2

flush2:
        ret

[section .setup] ; tells the assembler to include this data in the '.setup' section

trickgdt:
        dw gdt_end - gdt - 1 ; size of the GDT
        dd gdt ; linear address of GDT

gdt:
        dd 0, 0                                                 ; null gate
        db 0xFF, 0xFF, 0, 0, 0, 10011010b, 11001111b, 0x40      ; code selector 0x08: base 0x40000000, limit 0xFFFFFFFF, type 0x9A, granularity 0xCF
        db 0xFF, 0xFF, 0, 0, 0, 10010010b, 11001111b, 0x40      ; data selector 0x10: base 0x40000000, limit 0xFFFFFFFF, type 0x92, granularity 0xCF
        db 0xFF, 0xFF, 0, 0, 0, 11111010b, 11001111b, 0x40	; user mode code selector: base 0x40000000, limit 0xFFFFFFFFF, type 0xFA, granularity 0xCF
        db 0xFF, 0xFF, 0, 0, 0, 11110010b, 11001111b, 0x40	; user mode data selector: base 0x40000000, limit 0xFFFFFFFFF, type 0xF2, granularity 0xCF

gdt_end:

[section .bss]

resb 0x1000
sys_stack:
        ; our kernel stack

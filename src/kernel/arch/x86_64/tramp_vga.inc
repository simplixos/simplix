;---------------------------------------------------------------------------
;       SimplixOS Operating System
;
;       File: kernel/arch/x86_64/tramp_vga.inc
;
;       Descripition:
;               Minimalistic VGA writing functions for 64-bit trampoline.
;
;       License:
;       SimplixOS Operating System - An experimental operating system
;       Copyright (C) 2015-17 Aun-Ali Zaidi
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

; VGA Constants
xpos db 0
ypos db 0

msg db "Your CPU does not support long mode which is required for 64-bit.", 0

tramp_printc:
	call tramp_writeVGA	; Call segment 'tramp_writeVGA'
	
tramp_prints:
	mov eax, [esi]		; String char to AL
	lea esi, [esi+1]
	cmp al, 0
	jne tramp_printc	; else, we're done
	add byte [ypos], 1	; move down one row
	mov byte [xpos], 0	; move back to the left of the screen
	ret

tramp_writeVGA:
	mov ah, 0x0F		; attrib = white on black
	mov ecx, eax		; save char/attribute

	movzx eax, byte [ypos]
	mov edx, 160		; 2 bytes (char/attrib)
	mul edx			; for 80 columns
	
	movzx ebx, byte [xpos]
	shl ebx, 1		; times 2 to skip attrib

	mov edi, 0xb8000	; start of VGA memory
	add edi, eax		; add y offset
	add edi, ebx		; add x offset

	mov eax, ecx		; restore char/attribute
	mov word [ds:edi], ax
	add byte [xpos], 1	; shift to right

	ret

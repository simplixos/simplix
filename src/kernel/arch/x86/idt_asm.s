;---------------------------------------------------------------------------
;       BasicOS Operating System
;
;       File: kernel/arch/x86/idt_asm.s
;
;       Description:
;		Low-level IDT initialization code.
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
[BITS 32]
[GLOBAL idt_flush]    ; Allows the C code to call idt_flush().

idt_flush:
  mov eax, [esp+4]  ; Get the pointer to the IDT, passed as a parameter.
  lidt [eax]        ; Load the IDT pointer.
  ret

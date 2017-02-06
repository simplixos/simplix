/***********************************************************************
 * SimplixOS Operating System
 *
 * File: simplix/k/mods/mod_elf.h
 *
 * Description:
 *      Elf related header for ELF module loader.
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

#ifndef MOD_ELF_H
#define MOD_ELF_H

/* ELF Memory Resource Limits */
// Increasing these may help improve performance
#define ELF_HEAP_COMMIT		0x10000
#define ELF_HEAP_RESERVE	0x100000
#define ELF_STACK_COMMIT	0x10000
#define ELF_STACK_RESERVE	0x100000

/* If module will be loaded by USER or by KERNEL */
#define ELF_USER0	0
#define ELF_USERS0	1
#define ELF_SYS0	2
#define ELF_SYSS0	3

/* Machine specific Primitive Data-Types */
typedef unsigned int Elf32_Addr;
typedef unsigned short int Elf32_Half;
typedef unsigned int Elf32_Off;
typedef int Elf32_Sword;
typedef unsigned int Elf32_Word;

#define EI_NIDENT	16

/* ELF Type Definitions */
#define ET_NONE	0
#define ET_REL	1	// Relocatable ELF 32 module
#define ET_EXEC	2	// Executable ELF 32 module
#define ET_DYN	3	// SSared EF 32 module

/* Reserved ELF Defines */
#define ET_CORE		4
#define ET_LOPROC	0xFF00
#define ET_HIPROC	0xFFFF

/* ELF Machine specific defines */
#define EM_NONE		0
#define EM_M32		1
#define EM_SPARC	2
#define EM_386		3
#define EM_68K		4
#define EM_88K		5
#define EM_860		7
#define EM_MIPS		8

/* ELF Magic Values */
#define ELFMAG0		0x7f
#define ELFMAG1		'E'
#define ELFMAG2		'L'
#define ELFMAG3		'F'

/* ELF Section Header Indexes */
#define SHN_UNDEF	0
#define SHN_LORESERVE	0xff00
#define SHN_LOPROC	0xff00
#define SHN_HIPROC	0xff1f
#define SHN_ABS		0xfff1
#define SHN_COMMON	0xfff2
#define SHN_HIRESERVE	0xffff

/* ELF Section Header Types */
#define SHT_NULL	0
#define SHT_PROGBITS	1
#define SHT_SYMTAB	2
#define SHT_STRTAB	3
#define SHT_RELA	4
#define SHT_HASH	5
#define SHT_DYNAMIC	6
#define SHT_NOTE	7
#define SHT_NOBITS	8
#define SHT_REL		9
#define SHT_SHLIB	10
#define SHT_DYNSYM	11
#define SHT_LOPROC	0x70000000
#define SHT_HIPROC	0x7fffffff
#define SHT_LOUSER	0x80000000
#define SHT_HIUSER	0xffffffff

/* ELF Program Header Types */
#define PT_NULL		0
#define PT_LOAD		1
#define PT_DYNAMIC	2
#define PT_INTERP	3
#define PT_NOTE		4
#define PT_SHLIB	5
#define PT_PHDR		6
#define PT_LOPROC	0x70000000
#define PT_HIPROC	0X7fffffff

/* Interpreting ELF32 Symbol Tables */
#define ELF32_ST_BIND(i) ((i)>>4)
#define ELF32_ST_TYPE(i) ((i)&0xf)
#define ELF32_ST_INFO(b,t) (((b)<<4)+((t)&0xf))

/* Interpreting ELF Relocation Table Information */
#define ELF32_R_SYM(i)		((i) >> 8)
#define ELF32_R_TYPE(i)		((unsigned char) (i))
#define ELF32_R_INFO(s,t)	(((s) << 8) + (unsigned char) (t))

/* ELF Symbol Types in Symbol Tables */
#define STT_NOTYPE	0
#define STT_OBJECT	1
#define STT_FUNC	2
#define STT_SECTION	3
#define STT_FILE	4
#define STT_LOPROC	13
#define STT_HIPROC	15

/* ELF Section Attribute Flags */
#define SHF_WRITE	0x1
#define SHF_ALLOC	0x2
#define SHF_EXECINSTR	0x4
#define SHF_MASKPROC	0xf0000000

/* ELF x86 Relocation Types */
#ifdef _x86
	#define R_386_GOT32	3
	#define R_386_PLT32	4
	#define R_386_COPY	5
	#define R_386_GLOB_DAT	6
	#define R_386_JMP_SLOT	7
	#define R_386_RELATIVE	8
	#define R_386_GOTOFF	9
	#define R_386_GOTPC	10
#endif

/* ELF Dynamic Array Types */
#define DT_NULL		0
#define DT_NEEDED	1
#define DT_PLTRELSZ	2
#define DT_PLTGOT	3
#define DT_HASH		4
#define DT_STRTAB	5
#define DT_SYMTAB	6
#define DT_RELA		7
#define DT_RELASZ	8
#define DT_RELAENT	9
#define DT_STRSZ	10
#define DT_SYMENT	11
#define DT_INIT		12
#define DT_FINI		13
#define DT_SONAME	14
#define DT_RPATH	15
#define DT_SYMBOLIC	16
#define DT_REL		17
#define DT_RELSZ	18
#define DT_RELENT	19
#define DT_RELENT	19
#define DT_PLTREL	20
#define DT_DEBUG	21
#define DT_TEXTREL	22
#define DT_JMPREL	23
#define DT_BIND_NOW	24
#define DT_LOPROC	0x70000000
#define DT_HIPROC	0x7fffffff

/* ELF Header */
typedef struct __attribute__((packed)) {
	unsigned char e_ident[EI_NIDENT];
	Elf32_Half	e_type;
	Elf32_Half	e_machine;
	Elf32_Word	e_version;
	Elf32_Addr	e_entry;
	Elf32_Off	e_phoff;
	Elf32_Off	e_shoff;
	Elf32_Word	e_flags;
	Elf32_Half	e_ehsize;
	Elf32_Half	e_phentsize;
	Elf32_Half	e_phnum;
	Elf32_Half	e_shentsize;
	Elf32_Half	e_shnum;
	Elf32_Half	e_shstrndx;
} Elf32_Ehdr;

/* ELF Section Header */
typedef struct __attribute__((packed)) {
	Elf32_Word	sh_name;
	Elf32_Word	sh_type;
	Elf32_Word	sh_flags;
	Elf32_Addr	sh_addr;
	Elf32_Off	sh_offset;
	Elf32_Word	sh_size;
	Elf32_Word	sh_link;
	Elf32_Word	sh_info;
	Elf32_Word	sh_addralign;
	Elf32_Word	sh_entsize;
}Elf32_Shdr;

/* ELF Program Header */
typedef struct{
	Elf32_Word	p_type;
	Elf32_Off	p_offset;
	Elf32_Addr	p_vaddr;
	Elf32_Addr	p_paddr;
	Elf32_Word	p_filesz;
	Elf32_Word	p_memsz;
	Elf32_Word	p_flags;
	Elf32_Word	p_align;
} Elf32_Phdr;

/* ELF Relocation Information */
typedef struct {
	Elf32_Addr	r_offset;
	Elf32_Word	r_info;
} Elf32_Rel;

typedef struct {
	Elf32_Addr	r_offset;
	Elf32_Word	r_info;
	Elf32_Sword	r_addend;
} Elf32_Rela;

//This structure defines an ELF symbol table. Documentation was lifted from the
//Tool Interface Standard (TIS) Executable and Linking Format (ELF) Specification Version 1.2
typedef struct {
	Elf32_Word	st_name;	//This member holds an index into the object file's symbol string table,
					//which holds the character representations of the symbol names.
	Elf32_Addr	st_value;	//This member gives the value of the associated symbol.
					//Depending on the context,this may be an absolute value,
					//an address, and so on; details appear below.
	Elf32_Word	st_size;	//Many symbols have associated sizes. For example,
					//a data object's size is the number of bytes contained
					//in the object. This member holds 0 if the symbol has no size or
					//an unknown size.
	unsigned char	st_info;	//This member specifies the symbol's type and binding
					//attributes.
	unsigned char	st_other;	//This member currently holds 0 and has no defined meaning.
	Elf32_Half	st_shndx;	//Every symbol table entry is "defined'' in relation to some section;
					//this member holds the relevant section header table index.
} Elf32_Sym;

typedef struct {
	Elf32_Sword	d_tag;
	union {
		Elf32_Word	d_val;
		Elf32_Addr	d_ptr;
	} d_un;
} Elf32_Dyn;

typedef struct {
	Elf32_Word	namesz;
	Elf32_Word	descsz;
	Elf32_Word	type;
	char		info[];
} Elf32_Note;

#endif

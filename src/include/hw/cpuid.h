/***********************************************************************
 * SimplixOS Operating System
 *
 * File: include/hw/cpuid.h
 *
 * Description:
 *      Defines CPUID detection functions and CPU features.
 *
 * License:
 * SimplixOS Operating System - An experimental operating system.
 * Copyright (C) 2016 Aun-Ali Zaidi and its contributors.
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

#ifndef CPUID_H
#define CPUID_H

#include <bos/k/common.h>

// CPU Features

#define CPU_FEATURE_FPU		1<<0	// Floating-Point Unit on-Chip
#define CPU_FEATURE_VME 	1<<1	// Virtual Mode Extension
#define CPU_FEATURE_DE		1<<2	// Debugging Extension
#define CPU_FEATURE_PSE		1<<3	// Page Size Extension
#define CPU_FEATURE_TSC		1<<4	// Time Stamp Counter
#define CPU_FEATURE_MSR		1<<5	// Model Specific Registers
#define CPU_FEATURE_PAE		1<<6	// Physical Address Extension
#define CPU_FEATURE_MCE		1<<7	// Machine Check Exception
#define CPU_FEATURE_CX8		1<<8	// CMPXCHG8 Instruction
#define CPU_FEATURE_APIC	1<<9	// On-chip APIC hardware
#define CPU_FEATURE_SEP		1<<11	// Fast System Call
#define CPU_FEATURE_MTRR	1<<12	// Memory type Range Registers
#define CPU_FEATURE_PGE		1<<13	// Page Global Enable
#define	CPU_FEATURE_MCA		1<<14	// Machine Check Architecture
#define CPU_FEATURE_CMOV	1<<15	// Conditional MOVe Instruction
#define CPU_FEATURE_PAT		1<<16	// Page Attribute Table
#define CPU_FEATURE_PSE36	1<<17	// 36-bit Page Size Extension
#define CPU_FEATURE_PSN		1<<18	// Proccesor Serial Number
#define CPU_FEATURE_CLFSH	1<<19	// CFLUSH Instruction
#define CPU_FEATURE_DS		1<<21	// Debug Store
#define CPU_FEATURE_ACPI	1<<22	// Thermal Monitor & Software Controlled Clock
#define CPU_FEATURE_MMX		1<<23	// MultiMedia eXtension
#define CPU_FEATURE_FXSR	1<<24	// Fast Floating Point Save & Restore
#define CPU_FEATURE_SSE		1<<25	// Streaming SIMD Extension 1
#define CPU_FEATURE_SSE2	1<<26	// Streaming SIMD Extension 2
#define CPU_FEATURE_SS		1<<27	// Self Snoop
#define CPU_FEATURE_HTT		1<<28	// Hyper Threading Technology
#define CPU_FEATURE_TM		1<<29	// Thermal Monitor
#define CPU_FEATURE_PBE		1<<31	// Pend Breal Enabled

// CPU Extended Features

#define CPU_FEATURE_EXT_SSE3	1<<0	// Streaming SIMD Extension 3
#define CPU_FEATURE_EXT_MW	1<<3	// Mwait Instruction
#define CPU_FEATURE_EXT_CPL	1<<4	// CPL-qualified Debug Store
#define CPU_FEATURE_EXT_VMX	1<<5	// VMX
#define CPU_FEATURE_EXT_EST	1<<7	// Enhanced Speed Test
#define CPU_FEATURE_EXT_TM2	1<<8	// Thermal Monitor 2
#define CPU_FEATURE_EXT_L1	1<<10	// L1 Context ID
#define CPU_FEATURE_EXT_CAE	1<<13	// CompareAndExchange 16B

// CPUID Funcs

uint32_t cpuid_maxcall();
uint32_t cpuid_features();
uint32_t cpuid_extended_features();
// TODO: implement cpuid func in inline asm/c to use with cpuid_procname
//void cpuid_procname(char *name);
void cpu_info(void);

#endif // CPUID_H

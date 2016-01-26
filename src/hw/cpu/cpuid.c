/***********************************************************************
 * SimplixOS Operating System
 *
 * File: hw/cpu/cpuid.c
 *
 * Description:
 *      Functions detecting CPU and CPU features.
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

#include <hw/cpuid.h>

#ifdef __GNUC__
	#include <cpuid.h>
	#ifdef __clang__
		#define _CLANG_CPUID
	#else
		#define _GCC_CPUID
	#endif
#else
	#define __get_cpuid(func,ax,bx,cx,dx)\
		__asm__ __volatile__ ("cpuid":\
		"=a" (ax), "=b" (bx), "=c" (cx), "=d" (dx) : "a" (func));
#endif

// Retrieve the maximum function callable using cpuid
uint32_t cpuid_maxcall()
{
	#ifdef _CLANG_CPUID
		int maxcall = __get_cpuid_max(0x0, NULL);
	#elif defined(_GCC_CPUID)
		unsigned maxcall = __get_cpuid_max(0x0, NULL);
	#endif
	return (uint32_t)maxcall;
}

// This will retrieve the CPU features available
// returns the content of the edx register containing available features
uint32_t cpuid_features()
{
	unsigned eax, ebx, ecx, edx;
	#ifdef _CLANG_CPUID
		int features = __get_cpuid(1, &eax, &ebx, &ecx, &edx);
	#elif defined(_GCC_CPUID)
		unsigned features = __get_cpuid(1, &eax, &ebx, &ecx, &edx);
	#endif
	if (features == 0) return (uint32_t)0;
	return (uint32_t)edx;
}

// This will retrieve the extended CPU features available
// returns The content of the ecx register containing available extended features
uint32_t cpuid_extended_features()
{
	unsigned eax, ebx, ecx, edx;
	#ifdef _CLANG_CPUID
		int extendedFeatures = __get_cpuid(1, &eax, &ebx, &ecx, &edx);
	#elif defined(_GCC_CPUID)
		unsigned extendedFeatures = __get_cpuid(1, &eax, &ebx, &ecx, &edx);
	#endif
	if (extendedFeatures == 0) return (uint32_t)0;
	return (uint32_t)ecx;
}

/* -- NOT WORKING : PAGE FAULT
// Retrieve the processor name.
// \param name Preallocated string containing at least room for 13 characters. Will
// 	       contain the name of the processor.
void cpuid_procname(char* name)
{
  name[12] = 0;
  uint32_t max_op;
  __get_cpuid(0, max_op, (uint32_t)name[0], (uint32_t)name[8], (uint32_t)name[4]);
}
*/

/** x86 CPUID Info Retrieval Function, cpu_info
 *
 * This function returns information retrieved from the
 * CPUID x86 assembly instruction, such as CPU Name, Stepping,
 * Model, Family, Processor Type, Extended Model, Extended
 * Family, Features, and Extended Features.
 *
 */
void cpu_info(void)
{
	unsigned eax, ebx, ecx, edx;
	__get_cpuid(1, &eax, &ebx, &ecx, &edx);

	char *procname;
	//cpuid_procname(procname);
	procname = "Unavailable";
	kprintf("________________________________\n");
	kprintf("|         Processor Info       |\n");
	kprintf("********************************\n");

	// Processor Stepping, Model, Family, & Type
	kprintf("	General Info: \n");
	kprintf("	Stepping: ");
	kprintf("%d", eax & 0xF);
	kprintf(" Model: ");
	kprintf("%d", (eax >> 4) & 0xF);
	kprintf(" Family: ");
	#pragma GCC diagnostic push
	#pragma GCC diagnostic ignored "-Wmaybe-uninitialized"
	kprintf("%d", (eax >> 8) & 0xF);
	#pragma GCC diagnostic pop
	kprintf(" Extended Model: ");
	kprintf("%d", (eax >> 16) & 0xF);
	kprintf(" Extended Family: ");
	kprintf("%d\n", (eax >> 20) & 0xFF);

	kprintf("	Processor Name: \n");
	kprintf("	"); kprintf(procname); kprintf("\n");
	kprintf("	Processor Max 'cpuid' Calls: \n");
	kprintf("	"); kprintf("%d\n", cpuid_maxcall());

	kprintf("	Processor Features: \n");
	// Feature detection conditionals
	if (cpuid_features() & CPU_FEATURE_FPU)	kprintf("	* FPU ");
	if (cpuid_features() & CPU_FEATURE_VME) kprintf("VME ");
	if (cpuid_features() & CPU_FEATURE_DE)  kprintf("DE ");
	if (cpuid_features() & CPU_FEATURE_PSE) kprintf("PSE ");
	if (cpuid_features() & CPU_FEATURE_TSC) kprintf("TSC ");
	if (cpuid_features() & CPU_FEATURE_MSR) kprintf("MSR ");
	if (cpuid_features() & CPU_FEATURE_PAE) kprintf("PAE ");
	if (cpuid_features() & CPU_FEATURE_MCE) kprintf("MCE ");
	if (cpuid_features() & CPU_FEATURE_CX8) kprintf("CX8 ");
	if (cpuid_features() & CPU_FEATURE_APIC) kprintf("APIC ");
	if (cpuid_features() & CPU_FEATURE_SEP) kprintf("SEP ");
	if (cpuid_features() & CPU_FEATURE_MTRR) kprintf("MTRR ");
	if (cpuid_features() & CPU_FEATURE_PGE) kprintf("PGE ");
	if (cpuid_features() & CPU_FEATURE_MCA) kprintf("MCA ");
	if (cpuid_features() & CPU_FEATURE_CMOV) kprintf("CMOV ");
	if (cpuid_features() & CPU_FEATURE_PAT) kprintf("PAT ");
	if (cpuid_features() & CPU_FEATURE_PSE36) kprintf("PSE36 ");
	if (cpuid_features() & CPU_FEATURE_PSN) kprintf("PSN ");
	if (cpuid_features() & CPU_FEATURE_CLFSH) kprintf("CLFSH ");
	if (cpuid_features() & CPU_FEATURE_DS)  kprintf("DS ");
	if (cpuid_features() & CPU_FEATURE_ACPI) kprintf("ACPI ");
	if (cpuid_features() & CPU_FEATURE_MMX) kprintf("MMX ");
	if (cpuid_features() & CPU_FEATURE_FXSR) kprintf("FXSR ");
	if (cpuid_features() & CPU_FEATURE_SSE) kprintf("SSE ");
	if (cpuid_features() & CPU_FEATURE_SSE2) kprintf("SSE2 ");
	if (cpuid_features() & CPU_FEATURE_SS)  kprintf("SS ");
	if (cpuid_features() & CPU_FEATURE_HTT) kprintf("HTT ");
	if (cpuid_features() & CPU_FEATURE_TM)  kprintf("TM ");
	if (cpuid_features() & CPU_FEATURE_PBE) kprintf("PBE ");
	kprintf("\n");

	// Processor Extended Features
	kprintf("	Processor Extended Features: \n");
	if (cpuid_extended_features() & CPU_FEATURE_EXT_SSE3) kprintf("	* SSE3 ");
	if (cpuid_extended_features() & CPU_FEATURE_EXT_MW)   kprintf("MW ");
	if (cpuid_extended_features() & CPU_FEATURE_EXT_CPL)  kprintf("CPL ");
	if (cpuid_extended_features() & CPU_FEATURE_EXT_VMX)  kprintf("VMX ");
	if (cpuid_extended_features() & CPU_FEATURE_EXT_EST)  kprintf("EST ");
	if (cpuid_extended_features() & CPU_FEATURE_EXT_TM2)  kprintf("TM2 ");
	if (cpuid_extended_features() & CPU_FEATURE_EXT_L1)   kprintf("L1 ");
	if (cpuid_extended_features() & CPU_FEATURE_EXT_CAE)  kprintf("CAE ");
	kprintf("\n");

	kprintf("________________________________\n");
	kprintf("|         Processor Info       |\n");
	kprintf("********************************\n");

	kprintf("\n");
	// TODO: Add CPUID detection for CPU built-in caches.
}

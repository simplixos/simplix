/***********************************************************************
 * SimplixOS Operating System
 *
 * File: kernel/arch/x86/cpuid.c
 *
 * Description:
 *      Functions detecting x86 CPU features.
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

#include <simplix/k/arch/x86/cpuid.h>

#include <assert.h>

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
	unsigned edx = 0, unused;
	#ifdef _CLANG_CPUID
		int features = __get_cpuid(1, &unused, &unused, &unused, &edx);
	#elif defined(_GCC_CPUID)
		unsigned features = __get_cpuid(1, &unused, &unused, &unused, &edx);
	#endif
	if (features == 0) return (uint32_t)0;
	return (uint32_t)edx;
}

// This will retrieve the extended CPU features available
// returns The content of the ecx register containing available extended features
uint32_t cpuid_extended_features()
{
	unsigned ecx = 0, unused;
	#ifdef _CLANG_CPUID
		int extendedFeatures = __get_cpuid(1, &unused, &unused, &ecx, &unused);
	#elif defined(_GCC_CPUID)
		unsigned extendedFeatures = __get_cpuid(1, &unused, &unused, &ecx, &unused);
	#endif
	if (extendedFeatures == 0) return (uint32_t)0;
	return (uint32_t)ecx;
}


// Retrieve the processor vendor id.
void cpuid_vendorid(char* name)
{
	name[12] = 0;
	unsigned int max_op;
	assert(__get_cpuid(0, &max_op, (unsigned int *)&name[0], (unsigned int *)&name[8], (unsigned int *)&name[4]));
}

// Retrieves the processor branding string.
void cpuid_brand(unsigned int brand)
{
	unsigned op, unused;
	op = 0;
	assert(__get_cpuid(0x80000000, &op, &unused, &unused, &unused));

	if (op >= 0x80000004) {
		unsigned eax = 0, ebx = 0, ecx = 0, edx = 0;

		// XXX: Simplify conditionals...
		if (op >= 0x80000002) {
			assert(__get_cpuid(0x80000002, &eax, &ebx, &ecx, &edx));
			kprintf("%c%c%c%c", eax & 0xff, (eax >> 8) & 0xff, (eax >> 16) & 0xff, (eax >> 24) & 0xff);
			kprintf("%c%c%c%c", ebx & 0xff, (ebx >> 8) & 0xff, (ebx >> 16) & 0xff, (ebx >> 24) & 0xff);
			kprintf("%c%c%c%c", ecx & 0xff, (ecx >> 8) & 0xff, (ecx >> 16) & 0xff, (ecx >> 24) & 0xff);
			kprintf("%c%c%c%c", edx & 0xff, (edx >> 8) & 0xff, (edx >> 16) & 0xff, (edx >> 24) & 0xff);
		}
		if (op >= 0x80000003) {
			assert(__get_cpuid(0x80000003, &eax, &ebx, &ecx, &edx));
			kprintf("%c%c%c%c", eax & 0xff, (eax >> 8) & 0xff, (eax >> 16) & 0xff, (eax >> 24) & 0xff);
			kprintf("%c%c%c%c", ebx & 0xff, (ebx >> 8) & 0xff, (ebx >> 16) & 0xff, (ebx >> 24) & 0xff);
			kprintf("%c%c%c%c", ecx & 0xff, (ecx >> 8) & 0xff, (ecx >> 16) & 0xff, (ecx >> 24) & 0xff);
			kprintf("%c%c%c%c", edx & 0xff, (edx >> 8) & 0xff, (edx >> 16) & 0xff, (edx >> 24) & 0xff);
		}
		if (op >= 0x80000004) {
			assert(__get_cpuid(0x80000004, &eax, &ebx, &ecx, &edx));
			kprintf("%c%c%c%c", eax & 0xff, (eax >> 8) & 0xff, (eax >> 16) & 0xff, (eax >> 24) & 0xff);
			kprintf("%c%c%c%c", ebx & 0xff, (ebx >> 8) & 0xff, (ebx >> 16) & 0xff, (ebx >> 24) & 0xff);
			kprintf("%c%c%c%c", ecx & 0xff, (ecx >> 8) & 0xff, (ecx >> 16) & 0xff, (ecx >> 24) & 0xff);
			kprintf("%c%c%c%c", edx & 0xff, (edx >> 8) & 0xff, (edx >> 16) & 0xff, (edx >> 24) & 0xff);
		}
	} else if (brand > 0)
		kprintf("%d", brand);
}

/** x86 CPUID Info Retrieval Function, arch_cpu_info
 *
 * This function returns information retrieved from the
 * CPUID x86 assembly instruction, such as CPU Name, Stepping,
 * Model, Family, Processor Type, Extended Model, Extended
 * Family, Features, and Extended Features.
 *
 */
void arch_cpu_info(void)
{
	unsigned eax = 0, ebx = 0, unused;
	assert(__get_cpuid(1, &eax, &ebx, &unused, &unused));

	char vendorid[13];
	unsigned int brand = ebx & 0xff;
	cpuid_vendorid(vendorid);
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
	kprintf("%d", (eax >> 8) & 0xF);
	kprintf(" Extended Model: ");
	kprintf("%d", (eax >> 16) & 0xF);
	kprintf(" Extended Family: ");
	kprintf("%d\n", (eax >> 20) & 0xFF);

	kprintf("	Processor Vendor ID: \n");
	kprintf("	"); kprintf(vendorid); kprintf("\n");
	kprintf("	Processor Brand: \n");
	kprintf("	"); cpuid_brand(brand); kprintf("\n");
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

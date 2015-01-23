/***********************************************************************
 * BasicOS Operating System
 *
 * File: hw/cpu/cpuid.c
 *
 * Description:
 *      Functions detecting CPUID and CPU features.
 *
 * License:
 * BasicOS Operating System - An experimental operating system.
 * Copyright (C) 2015 Aun-Ali Zaidi
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

#define cpuid(func,ax,bx,cx,dx)\
	__asm__ __volatile__ ("cpuid":\
	"=a" (ax), "=b" (bx), "=c" (cx), "=d" (dx) : "a" (func));

// Retrieve the maximum function callable using cpuid
u32int cpuid_maxcall()
{
	u32int eax, ebx, ecx, edx;
	cpuid(0, eax, ebx, ecx, edx);
	return eax;
}

// Retrive the processors manufacturing stepping
u32int cpuid_general_info()
{
	u32int eax, ebx, ecx, edx;
	cpuid(1, eax, ebx, ecx, edx);
	return eax;
}

// This will retrieve the CPU features available
// returns the content of the edx register containing available features
u32int cpuid_features()
{
	u32int eax, ebx, ecx, edx;
	cpuid(1, eax, ebx, ecx, edx);
	return edx;
}

// This will retrieve the extended CPU features available
// returns The content of the ecx register containing available extended features
u32int cpuid_extended_features()
{
	u32int eax, ebx, ecx, edx;
	cpuid(1, eax, ebx, ecx, edx);
	return ecx;
}

/* -- Currently not Compiling!
// Retrieve the processor name.
// \param name Preallocated string containing at least room for 13 characters. Will
// 	       contain the name of the processor.
void cpuid_procname(char* name)
{
  name[12] = 0;
  u32int max_op;
  cpuid(0, max_op, (u32int)name[0], (u32int)name[8], (u32int)name[4]);
}
*/

void cpu_info()
{
	char *procname;
	//cpuid_procname(procname);
	procname = "Unavailable";
	vga_write("________________________________\n");
	vga_write("|         Processor Info       |\n");
	vga_write("********************************\n");
	
        // Processor Stepping, Model, Family, & Type
        vga_write("     General Info: \n");
        vga_write("     Stepping: ");
        if (cpuid_general_info() & CPU_STEP_1) vga_write("1");
        if (cpuid_general_info() & CPU_STEP_2) vga_write("2");
        if (cpuid_general_info() & CPU_STEP_3) vga_write("3");
        if (cpuid_general_info() & CPU_STEP_4) vga_write("4");
        vga_write(" Model: ");
        if (cpuid_general_info() & CPU_MODEL_4) vga_write("4");
        if (cpuid_general_info() & CPU_MODEL_5) vga_write("5");
        if (cpuid_general_info() & CPU_MODEL_6) vga_write("6");
        if (cpuid_general_info() & CPU_MODEL_7) vga_write("7");
        vga_write(" Family: ");
        if (cpuid_general_info() & CPU_FAM_8)  vga_write("8");
        if (cpuid_general_info() & CPU_FAM_9)  vga_write("9");
        if (cpuid_general_info() & CPU_FAM_10) vga_write("10");
        if (cpuid_general_info() & CPU_FAM_11) vga_write("11");
        vga_write("\n");
	
	vga_write("	Processor Name: \n");
	vga_write("	"); vga_write(procname); vga_write("\n");
	vga_write("	Processor Max cpuid Call: \n");
	vga_write("	"); vga_write_dec(cpuid_maxcall()); vga_write("\n");
	vga_write("	Processor Features: \n");
	
	// Feature detection conditionals
	if (cpuid_features() & CPU_FEATURE_FPU)	vga_write("	* FPU ");
	if (cpuid_features() & CPU_FEATURE_VME) vga_write("VME ");
	if (cpuid_features() & CPU_FEATURE_DE)  vga_write("DE ");
	if (cpuid_features() & CPU_FEATURE_PSE) vga_write("PSE ");
	if (cpuid_features() & CPU_FEATURE_TSC) vga_write("TSC ");
	if (cpuid_features() & CPU_FEATURE_MSR) vga_write("MSR ");
	if (cpuid_features() & CPU_FEATURE_PAE) vga_write("PAE ");
	if (cpuid_features() & CPU_FEATURE_MCE) vga_write("MCE ");
	if (cpuid_features() & CPU_FEATURE_CX8) vga_write("CX8 ");
	if (cpuid_features() & CPU_FEATURE_APIC) vga_write("APIC ");
	if (cpuid_features() & CPU_FEATURE_SEP) vga_write("SEP ");
	if (cpuid_features() & CPU_FEATURE_MTRR) vga_write("MTRR ");
	if (cpuid_features() & CPU_FEATURE_PGE) vga_write("PGE ");
	if (cpuid_features() & CPU_FEATURE_MCA) vga_write("MCA ");
	if (cpuid_features() & CPU_FEATURE_CMOV) vga_write("CMOV ");
	if (cpuid_features() & CPU_FEATURE_PAT) vga_write("PAT ");
	if (cpuid_features() & CPU_FEATURE_PSE36) vga_write("PSE36 ");
	if (cpuid_features() & CPU_FEATURE_PSN) vga_write("PSN ");
	if (cpuid_features() & CPU_FEATURE_CLFSH) vga_write("CLFSH ");
	if (cpuid_features() & CPU_FEATURE_DS)  vga_write("DS ");
	if (cpuid_features() & CPU_FEATURE_ACPI) vga_write("ACPI ");
	if (cpuid_features() & CPU_FEATURE_MMX) vga_write("MMX ");
	if (cpuid_features() & CPU_FEATURE_FXSR) vga_write("FXSR ");
	if (cpuid_features() & CPU_FEATURE_SSE) vga_write("SSE ");
	if (cpuid_features() & CPU_FEATURE_SSE2) vga_write("SSE2 ");
	if (cpuid_features() & CPU_FEATURE_SS)  vga_write("SS ");
	if (cpuid_features() & CPU_FEATURE_HTT) vga_write("HTT ");
	if (cpuid_features() & CPU_FEATURE_TM)  vga_write("TM ");
	if (cpuid_features() & CPU_FEATURE_PBE) vga_write("PBE ");
	vga_write("\n");
	
	// Processor Extended Features
	vga_write("	Processor Extended Features: \n");
	if (cpuid_extended_features() & CPU_FEATURE_EXT_SSE3) vga_write("	* SSE3 ");
	if (cpuid_extended_features() & CPU_FEATURE_EXT_MW)   vga_write("MW ");
	if (cpuid_extended_features() & CPU_FEATURE_EXT_CPL)  vga_write("CPL ");
	if (cpuid_extended_features() & CPU_FEATURE_EXT_VMX)  vga_write("VMX ");
	if (cpuid_extended_features() & CPU_FEATURE_EXT_EST)  vga_write("EST ");
	if (cpuid_extended_features() & CPU_FEATURE_EXT_TM2)  vga_write("TM2 ");
	if (cpuid_extended_features() & CPU_FEATURE_EXT_L1)   vga_write("L1 ");
	if (cpuid_extended_features() & CPU_FEATURE_EXT_CAE)  vga_write("CAE ");
	vga_write("\n\n");

	// TODO: Add CPUID detection for CPU built-in caches.
}

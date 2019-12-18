#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct TYPE_3__ {int wProcessorArchitecture; int /*<<< orphan*/  member_0; } ;
typedef  TYPE_1__ SYSTEM_INFO ;

/* Variables and functions */
 int CPU_ARCH_ARM_32 ; 
 int CPU_ARCH_ARM_64 ; 
 int CPU_ARCH_UNDEFINED ; 
 int CPU_ARCH_X86_64 ; 
 int /*<<< orphan*/  GetNativeSystemInfo (TYPE_1__*) ; 
#define  PROCESSOR_ARCHITECTURE_AMD64 131 
#define  PROCESSOR_ARCHITECTURE_ARM 130 
#define  PROCESSOR_ARCHITECTURE_ARM64 129 
#define  PROCESSOR_ARCHITECTURE_INTEL 128 

int GetCpuArch(void)
{
	SYSTEM_INFO info = { 0 };
	GetNativeSystemInfo(&info);
	switch (info.wProcessorArchitecture) {
	case PROCESSOR_ARCHITECTURE_AMD64:
		return CPU_ARCH_X86_64;
	case PROCESSOR_ARCHITECTURE_INTEL:
		return CPU_ARCH_X86_64;
	case PROCESSOR_ARCHITECTURE_ARM64:
		return CPU_ARCH_ARM_64;
	case PROCESSOR_ARCHITECTURE_ARM:
		return CPU_ARCH_ARM_32;
	default:
		return CPU_ARCH_UNDEFINED;
	}
}
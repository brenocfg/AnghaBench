#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */

/* Type definitions */
typedef  scalar_t__ ULONG ;

/* Variables and functions */
 int /*<<< orphan*/  ENTER_FUNC () ; 
 int /*<<< orphan*/  LEAVE_FUNC () ; 
 int /*<<< orphan*/  MaskIrqs () ; 
 scalar_t__ OldGPFaultHandler ; 
 scalar_t__ SetGlobalInt (int,scalar_t__) ; 
 int /*<<< orphan*/  UnmaskIrqs () ; 

void InstallGPFaultHook(void)
{
	ULONG LocalGPFaultHandler;

	ENTER_FUNC();

	MaskIrqs();
	if(!OldGPFaultHandler)
	{
		__asm__("mov $NewGPFaultHandler,%0"
			:"=r" (LocalGPFaultHandler)
			:
			:"eax");
		OldGPFaultHandler=SetGlobalInt(0x0D,(ULONG)LocalGPFaultHandler);
	}
	UnmaskIrqs();

    LEAVE_FUNC();
}
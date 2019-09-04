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
typedef  int /*<<< orphan*/  BOOLEAN ;

/* Variables and functions */
 int /*<<< orphan*/  DPRINT (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  MaskIrqs () ; 
 scalar_t__ OldInt1Handler ; 
 scalar_t__ SetGlobalInt (int,scalar_t__) ; 
 int /*<<< orphan*/  TRUE ; 
 int /*<<< orphan*/  UnmaskIrqs () ; 

BOOLEAN InstallTraceHook(void)
{
	ULONG LocalInt1Handler;

    DPRINT((0,"InstallTraceHook(OldInt1Handler=%0.8x)...\n",OldInt1Handler));

	MaskIrqs();
	if(!OldInt1Handler)
	{
		__asm__("mov $NewInt1Handler,%0"
			:"=r" (LocalInt1Handler)
			:
			:"eax");
		OldInt1Handler=SetGlobalInt(0x01,(ULONG)LocalInt1Handler);
	}
	UnmaskIrqs();
	return TRUE;
}
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
 int /*<<< orphan*/  DPRINT (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ENTER_FUNC () ; 
 int /*<<< orphan*/  LEAVE_FUNC () ; 
 int /*<<< orphan*/  MaskIrqs () ; 
 scalar_t__ OldIntEHandler ; 
 scalar_t__ SetGlobalInt (int,scalar_t__) ; 
 int /*<<< orphan*/  UnmaskIrqs () ; 

void InstallIntEHook(void)
{
	ULONG LocalIntEHandler;

	ENTER_FUNC();

	MaskIrqs();
	if(!OldIntEHandler)
	{
		__asm__ __volatile__("mov $NewIntEHandler,%0"
			:"=r" (LocalIntEHandler)
			:
			:"eax");
		OldIntEHandler=SetGlobalInt(0x0E,(ULONG)LocalIntEHandler);
	}
	UnmaskIrqs();
	DPRINT((0,"OldIntE @ %x\n", OldIntEHandler));
    LEAVE_FUNC();
}
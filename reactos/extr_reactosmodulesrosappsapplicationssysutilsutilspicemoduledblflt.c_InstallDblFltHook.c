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
 scalar_t__ OldDblFltHandler ; 
 scalar_t__ SetGlobalInt (int,scalar_t__) ; 
 int /*<<< orphan*/  UnmaskIrqs () ; 

void InstallDblFltHook(void)
{
	ULONG LocalDblFltHandler;

	ENTER_FUNC();

	MaskIrqs();
	if(!OldDblFltHandler)
	{
		__asm__("mov $NewDblFltHandler,%0"
			:"=r" (LocalDblFltHandler)
			:
			:"eax");
		OldDblFltHandler=SetGlobalInt(0x08,(ULONG)LocalDblFltHandler);
	}
	UnmaskIrqs();

    LEAVE_FUNC();
}
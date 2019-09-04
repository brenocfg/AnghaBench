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
 int /*<<< orphan*/  KeyboardIRQL ; 
 int /*<<< orphan*/  LEAVE_FUNC () ; 
 int /*<<< orphan*/  MaskIrqs () ; 
 scalar_t__ OldGlobalInt31Handler ; 
 scalar_t__ SetGlobalInt (int /*<<< orphan*/ ,scalar_t__) ; 
 int /*<<< orphan*/  UnmaskIrqs () ; 

void InstallGlobalKeyboardHook(void)
{
	ULONG LocalNewGlobalInt31Handler;

	ENTER_FUNC();

	MaskIrqs();
	if(!OldGlobalInt31Handler)
	{
		__asm__("mov $NewGlobalInt31Handler,%0"
			:"=r" (LocalNewGlobalInt31Handler)
			:
			:"eax");
		OldGlobalInt31Handler=SetGlobalInt(KeyboardIRQL,(ULONG)LocalNewGlobalInt31Handler);
	}
	UnmaskIrqs();

    LEAVE_FUNC();
}
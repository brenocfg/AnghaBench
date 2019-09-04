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
typedef  int /*<<< orphan*/  ULONG ;

/* Variables and functions */
 int /*<<< orphan*/  ENTER_FUNC () ; 
 int /*<<< orphan*/  LEAVE_FUNC () ; 

void InstallSyscallHook(void)
{
	ULONG LocalSyscallHandler;

	ENTER_FUNC();
/*ei  fix later
	MaskIrqs();
	if(!OldSyscallHandler)
	{
		__asm__("mov $NewSyscallHandler,%0"
			:"=r" (LocalSyscallHandler)
			:
			:"eax");
		OldSyscallHandler=SetGlobalInt(0x2e,(ULONG)LocalSyscallHandler);

		ScanExports("free_module",(PULONG)&ulFreeModule);

		DPRINT((0,"InstallSyscallHook(): free_module @ %x\n",ulFreeModule));
	}
	UnmaskIrqs();
 */
    LEAVE_FUNC();
}
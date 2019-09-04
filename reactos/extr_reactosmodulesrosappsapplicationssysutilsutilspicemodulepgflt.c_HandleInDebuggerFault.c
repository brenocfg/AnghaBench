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
typedef  int ULONG ;
struct TYPE_3__ {int error_code; int /*<<< orphan*/  eip; int /*<<< orphan*/  eflags; int /*<<< orphan*/  cs; } ;
typedef  int* PULONG ;
typedef  scalar_t__ PEPROCESS ;
typedef  TYPE_1__ FRAME ;

/* Variables and functions */
 int* ADDR_TO_PDE (int) ; 
 int* ADDR_TO_PTE (int) ; 
 int /*<<< orphan*/  CurrentEBP ; 
 int /*<<< orphan*/  DPRINT (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ENTER_FUNC () ; 
 int /*<<< orphan*/  IntelStackWalk (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ IoGetCurrentProcess () ; 
 int /*<<< orphan*/  LEAVE_FUNC () ; 
 scalar_t__ TRUE ; 
 int _PAGE_4M ; 
 int _PAGE_PRESENT ; 
 scalar_t__ bInPageFaultHandler ; 
 int /*<<< orphan*/  bInPrintk ; 
 int /*<<< orphan*/  ulRealStackPtr ; 

ULONG HandleInDebuggerFault(FRAME* ptr,ULONG address)
{
	PEPROCESS tsk;

    ENTER_FUNC();

	DPRINT((0,"HandleInDebuggerFault(): ###### page fault @ %.8X while inside debugger, eip: %x\n",address, ptr->eip));

	// fault in this page fault handler
	if(bInPageFaultHandler)
	{
    	DPRINT((0,"HandleInDebuggerFault(): ###### page fault @ %.8X while in page fault handler\n",address));

        DPRINT((0,"!!! machine is halted !!!\n"));
        __asm__ __volatile__ ("hlt");

        LEAVE_FUNC();
		return 0;
	}

	bInPageFaultHandler = TRUE;

    // when we come here from DebuggerShell() we live on a different stack
    // so the current task is different as well
    tsk = IoGetCurrentProcess();

    DPRINT((0,"%.8X (%.4X:%.8X %.8X %s %s %s task=%.8X )\n",
        address,
        ptr->cs,
        ptr->eip,
        ptr->eflags,
        (ptr->error_code&1)?"PLP":"NP",
        (ptr->error_code&2)?"WRITE":"READ",
        (ptr->error_code&4)?"USER-MODE":"KERNEL-MODE",
        (ULONG)tsk));

	if(!bInPrintk)
    {
    	DPRINT((0,"HandleInDebuggerFault(): unexpected pagefault in command handler!\n",address));
    }
	else
    {
    	DPRINT((0,"HandleInDebuggerFault(): unexpected pagefault in command handler while in PrintkCallback()!\n",address));
    }

    if(tsk)
    {
	    PULONG pPGD;
	    PULONG pPTE;

        pPGD = ADDR_TO_PDE(address);

        DPRINT((0,"PGD for %.8X @ %.8X = %.8X\n",address,(ULONG)pPGD,(ULONG)(*pPGD) ));

        if(pPGD && (*pPGD)&_PAGE_PRESENT)
        {
            // not large page
            if(!((*pPGD)&_PAGE_4M))
            {
                pPTE = ADDR_TO_PTE(address);
                if(pPTE)
                {
                    DPRINT((0,"PTE for %.8X @ %.8X = %.8X\n",address,(ULONG)pPTE,(ULONG)(*pPTE) ));
                }
            }
        }
    }

    IntelStackWalk(ptr->eip,CurrentEBP,ulRealStackPtr);

    DPRINT((0,"!!! machine is halted !!!\n"));
    __asm__ __volatile__ ("hlt");

    LEAVE_FUNC();

	return 2;
}
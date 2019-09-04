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

/* Variables and functions */
 int /*<<< orphan*/  DPRINT (int /*<<< orphan*/ ) ; 
 scalar_t__ DeInstallSWBreakpoint (scalar_t__) ; 
 int /*<<< orphan*/  ENTER_FUNC () ; 
 scalar_t__ FALSE ; 
 int /*<<< orphan*/  LEAVE_FUNC () ; 
 scalar_t__ bIsPrintkPatched ; 
 scalar_t__ ulPrintk ; 

void DeInstallPrintkHook(void)
{
    ENTER_FUNC();

	DPRINT((0,"enter DeInstallPrintkHook()\n"));
    if(bIsPrintkPatched && ulPrintk)
    {
		// will be done on exit debugger
        if (DeInstallSWBreakpoint(ulPrintk))
				  bIsPrintkPatched = FALSE;
    }
    LEAVE_FUNC();
}
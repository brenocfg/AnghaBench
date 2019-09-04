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
typedef  int /*<<< orphan*/  PULONG ;

/* Variables and functions */
 int /*<<< orphan*/  ASSERT (scalar_t__) ; 
 int /*<<< orphan*/  DPRINT (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ENTER_FUNC () ; 
 scalar_t__ InstallSWBreakpoint (scalar_t__,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  LEAVE_FUNC () ; 
 int /*<<< orphan*/  PrintkCallback ; 
 int /*<<< orphan*/  ScanExports (char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  TRUE ; 
 scalar_t__ bIsPrintkPatched ; 
 scalar_t__ ulPrintk ; 

void InstallPrintkHook(void)
{

	ENTER_FUNC();

	if( bIsPrintkPatched )
			return;

  DPRINT((0,"installing PrintString hook\n"));
	ScanExports("_KdpPrintString",(PULONG)&ulPrintk);

	DPRINT((0,"_KdpPrintString @ %x\n", ulPrintk));
	ASSERT( ulPrintk );                 // temporary
    if(ulPrintk)
    {
      bIsPrintkPatched = InstallSWBreakpoint(ulPrintk,TRUE,PrintkCallback);
  		DPRINT((0,"KdpPrintStringTest breakpoint installed? %d\n", bIsPrintkPatched));
    }

	LEAVE_FUNC();
}
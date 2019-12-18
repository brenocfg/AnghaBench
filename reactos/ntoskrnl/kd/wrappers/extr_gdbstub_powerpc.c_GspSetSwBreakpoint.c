#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
typedef  size_t ULONG_PTR ;
struct TYPE_2__ {size_t Address; int /*<<< orphan*/  Active; } ;

/* Variables and functions */
 int /*<<< orphan*/  DPRINT (char*,size_t) ; 
 int /*<<< orphan*/  DPRINT1 (char*) ; 
 int /*<<< orphan*/  FALSE ; 
 int /*<<< orphan*/  GspOutBuffer ; 
 size_t GspSwBreakpointCount ; 
 TYPE_1__* GspSwBreakpoints ; 
 size_t MAX_SW_BREAKPOINTS ; 
 int /*<<< orphan*/  strcpy (int /*<<< orphan*/ ,char*) ; 

__attribute__((used)) static void
GspSetSwBreakpoint(ULONG_PTR Address)
{
  DPRINT("GspSetSwBreakpoint(0x%p)\n", Address);

  if (MAX_SW_BREAKPOINTS == GspSwBreakpointCount)
    {
      DPRINT1("Trying to set too many software breakpoints\n");
      strcpy(GspOutBuffer, "E22");
    }
  else
    {
      DPRINT("Stored at index %u\n", GspSwBreakpointCount);
      GspSwBreakpoints[GspSwBreakpointCount].Address = Address;
      GspSwBreakpoints[GspSwBreakpointCount].Active = FALSE;
      GspSwBreakpointCount++;
      strcpy(GspOutBuffer, "OK");
    }
}
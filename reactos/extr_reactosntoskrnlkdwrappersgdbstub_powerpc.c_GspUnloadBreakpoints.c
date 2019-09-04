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
struct TYPE_2__ {scalar_t__ Address; void* Active; int /*<<< orphan*/  PrevContent; } ;
typedef  int /*<<< orphan*/  PKTRAP_FRAME ;
typedef  int /*<<< orphan*/  PCHAR ;

/* Variables and functions */
 int /*<<< orphan*/  DPRINT (char*,...) ; 
 int /*<<< orphan*/  DPRINT1 (char*,scalar_t__) ; 
 void* FALSE ; 
 void* GspMemoryError ; 
 unsigned int GspSwBreakpointCount ; 
 TYPE_1__* GspSwBreakpoints ; 
 int /*<<< orphan*/  GspWriteMemSafe (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void
GspUnloadBreakpoints(PKTRAP_FRAME TrapFrame)
{
  unsigned Index;

  DPRINT("GspUnloadHwBreakpoints\n");

  for (Index = 0; Index < GspSwBreakpointCount; Index++)
    {
      if (GspSwBreakpoints[Index].Active)
        {
          GspMemoryError = FALSE;
          GspWriteMemSafe((PCHAR) GspSwBreakpoints[Index].Address,
                          GspSwBreakpoints[Index].PrevContent);
          GspSwBreakpoints[Index].Active = FALSE;
          if (GspMemoryError)
            {
              DPRINT1("Failed to remove software breakpoint from 0x%p\n",
                      GspSwBreakpoints[Index].Address);
            }
          else
            {
              DPRINT("Successfully removed software breakpoint from 0x%p\n",
                     GspSwBreakpoints[Index].Address);
            }
        }
    }
}
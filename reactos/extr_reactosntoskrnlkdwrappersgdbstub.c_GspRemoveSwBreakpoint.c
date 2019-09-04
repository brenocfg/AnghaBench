#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
typedef  size_t ULONG_PTR ;
typedef  size_t ULONG ;
struct TYPE_4__ {int /*<<< orphan*/  Active; } ;
typedef  int /*<<< orphan*/  GSPSWBREAKPOINT ;

/* Variables and functions */
 int /*<<< orphan*/  ASSERT (int) ; 
 int /*<<< orphan*/  DPRINT (char*,size_t) ; 
 int /*<<< orphan*/  DPRINT1 (char*) ; 
 scalar_t__ GspFindSwBreakpoint (size_t,size_t*) ; 
 int /*<<< orphan*/  GspOutBuffer ; 
 size_t GspSwBreakpointCount ; 
 TYPE_1__* GspSwBreakpoints ; 
 int /*<<< orphan*/  memmove (TYPE_1__*,TYPE_1__*,size_t) ; 
 int /*<<< orphan*/  strcpy (int /*<<< orphan*/ ,char*) ; 

__attribute__((used)) static void
GspRemoveSwBreakpoint(ULONG_PTR Address)
{
    ULONG Index;

    DPRINT("GspRemoveSwBreakpoint(0x%p)\n", Address);

    if (GspFindSwBreakpoint(Address, &Index))
    {
        DPRINT("Found match at index %u\n", Index);
        ASSERT(!GspSwBreakpoints[Index].Active);

        if (Index + 1 < GspSwBreakpointCount)
            memmove(GspSwBreakpoints + Index,
                    GspSwBreakpoints + (Index + 1),
                    (GspSwBreakpointCount - Index - 1) * sizeof(GSPSWBREAKPOINT));

        GspSwBreakpointCount--;
        strcpy(GspOutBuffer, "OK");
        return;
    }

    DPRINT1("Not found\n");
    strcpy(GspOutBuffer, "E22");
}
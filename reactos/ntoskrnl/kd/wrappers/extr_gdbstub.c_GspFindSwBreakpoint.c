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
typedef  scalar_t__ ULONG_PTR ;
typedef  size_t ULONG ;
struct TYPE_2__ {scalar_t__ Address; } ;
typedef  size_t* PULONG ;
typedef  int /*<<< orphan*/  BOOLEAN ;

/* Variables and functions */
 int /*<<< orphan*/  FALSE ; 
 size_t GspSwBreakpointCount ; 
 TYPE_1__* GspSwBreakpoints ; 
 int /*<<< orphan*/  TRUE ; 

__attribute__((used)) static BOOLEAN
GspFindSwBreakpoint(ULONG_PTR Address, PULONG PIndex)
{
    ULONG Index;

    for (Index = 0; Index < GspSwBreakpointCount; Index++)
    {
        if (GspSwBreakpoints[Index].Address == Address)
        {
            if (PIndex)
                *PIndex = Index;
            return TRUE;
        }
    }

    return FALSE;
}
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
typedef  size_t ULONG ;
struct TYPE_2__ {int Active; scalar_t__ Address; int /*<<< orphan*/  PrevContent; } ;
typedef  int /*<<< orphan*/  PCHAR ;

/* Variables and functions */
 int /*<<< orphan*/  DPRINT (char*,scalar_t__) ; 
 int /*<<< orphan*/  DPRINT1 (char*,scalar_t__) ; 
 scalar_t__ FALSE ; 
 scalar_t__ GspMemoryError ; 
 int /*<<< orphan*/  GspReadMemSafe (int /*<<< orphan*/ ) ; 
 TYPE_1__* GspSwBreakpoints ; 
 int /*<<< orphan*/  GspWriteMemSafe (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  I386_OPCODE_INT3 ; 

__attribute__((used)) static void
GspLoadSwBreakpoint(ULONG Index)
{
    GspMemoryError = FALSE;

    GspSwBreakpoints[Index].PrevContent = GspReadMemSafe((PCHAR)GspSwBreakpoints[Index].Address);

    if (!GspMemoryError)
        GspWriteMemSafe((PCHAR)GspSwBreakpoints[Index].Address, I386_OPCODE_INT3);

    GspSwBreakpoints[Index].Active = !GspMemoryError;

    if (GspMemoryError)
        DPRINT1("Failed to set software breakpoint at 0x%p\n", GspSwBreakpoints[Index].Address);
    else
        DPRINT("Successfully set software breakpoint at 0x%p\n", GspSwBreakpoints[Index].Address);
}
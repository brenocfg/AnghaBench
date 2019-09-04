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
typedef  int /*<<< orphan*/  VOID ;
typedef  scalar_t__ ULONG ;
typedef  int /*<<< orphan*/  PLARGE_MCB ;
typedef  int /*<<< orphan*/  LONGLONG ;

/* Variables and functions */
 scalar_t__ FsRtlGetNextLargeMcbEntry (int /*<<< orphan*/ ,scalar_t__,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  trace (char*,...) ; 

__attribute__((used)) static VOID DumpAllRuns(PLARGE_MCB Mcb)
{
    ULONG i;
    LONGLONG Vbn, Lbn, Count;

    trace("MCB %p:\n", Mcb);

    for (i = 0; FsRtlGetNextLargeMcbEntry(Mcb, i, &Vbn, &Lbn, &Count); i++)
    {
        // print out vbn, lbn, and count
        trace("\t[%I64d,%I64d,%I64d]\n", Vbn, Lbn, Count);
    }
    trace("\n");
}
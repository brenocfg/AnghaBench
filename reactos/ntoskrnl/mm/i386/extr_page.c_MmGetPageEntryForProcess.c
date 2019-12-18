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
typedef  int /*<<< orphan*/  PVOID ;
typedef  int /*<<< orphan*/ * PULONG ;
typedef  int /*<<< orphan*/  PEPROCESS ;

/* Variables and functions */
 int /*<<< orphan*/  FALSE ; 
 int /*<<< orphan*/ * MmGetPageTableForProcess (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  MmUnmapPageTable (int /*<<< orphan*/ *) ; 

__attribute__((used)) static ULONG MmGetPageEntryForProcess(PEPROCESS Process, PVOID Address)
{
    ULONG Pte;
    PULONG Pt;

    Pt = MmGetPageTableForProcess(Process, Address, FALSE);
    if (Pt)
    {
        Pte = *Pt;
        MmUnmapPageTable(Pt);
        return Pte;
    }
    return 0;
}
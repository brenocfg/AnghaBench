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
typedef  int ULONG_PTR ;
typedef  scalar_t__ UINT ;
struct TYPE_4__ {scalar_t__ RamSize; scalar_t__ RamBase; } ;
typedef  scalar_t__ PUCHAR ;
typedef  TYPE_1__* PNIC_ADAPTER ;
typedef  int /*<<< orphan*/  BOOLEAN ;

/* Variables and functions */
 int /*<<< orphan*/  FALSE ; 
 int /*<<< orphan*/  MAX_TRACE ; 
 int /*<<< orphan*/  MID_TRACE ; 
 int /*<<< orphan*/  MIN_TRACE ; 
 int /*<<< orphan*/  NDIS_DbgPrint (int /*<<< orphan*/ ,char*) ; 
 scalar_t__ NICTestAddress (TYPE_1__*,int) ; 
 int /*<<< orphan*/  TRUE ; 

__attribute__((used)) static BOOLEAN NICTestRAM(
    PNIC_ADAPTER Adapter)
/*
 * FUNCTION: Finds out how much RAM a NIC has
 * ARGUMENTS:
 *     Adapter = Pointer to adapter information
 * RETURNS:
 *     TRUE if the RAM size was found, FALSE if not
 * NOTES:
 *     Start at 1KB and test for every 1KB up to 64KB
 */
{
    ULONG_PTR Base;

    NDIS_DbgPrint(MAX_TRACE, ("Called.\n"));

    /* Locate RAM base address */
    for (Base = 0x0400; Base < 0x10000; Base += 0x0400) {
        if (NICTestAddress(Adapter, Base))
            break;
    }

    if (Base == 0x10000) {
        /* No RAM on this board */
        NDIS_DbgPrint(MIN_TRACE, ("No RAM found on board.\n"));
        return FALSE;
    }

    Adapter->RamBase = (PUCHAR)Base;

    /* Find RAM size */
    for (; Base < 0x10000; Base += 0x0400) {
        if (!NICTestAddress(Adapter, Base))
            break;
    }

    Adapter->RamSize = (UINT)(Base - (ULONG_PTR)Adapter->RamBase);

    NDIS_DbgPrint(MID_TRACE, ("RAM is at (0x%X). Size is (0x%X).\n",
        Adapter->RamBase, Adapter->RamSize));

    return TRUE;
}
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
typedef  scalar_t__ ULONG ;
typedef  scalar_t__ PVOID ;
typedef  scalar_t__ PUCHAR ;
typedef  int /*<<< orphan*/  BOOLEAN ;

/* Variables and functions */
 scalar_t__ ALIGN_DOWN_POINTER_BY (scalar_t__,scalar_t__) ; 
 int /*<<< orphan*/  FALSE ; 
 int /*<<< orphan*/  MmIsAddressValid (scalar_t__) ; 
 scalar_t__ PAGE_SIZE ; 
 int /*<<< orphan*/  TRUE ; 

BOOLEAN
KdbIsMemoryValid(PVOID pvBase, ULONG cjSize)
{
    PUCHAR pjAddress;

    pjAddress = ALIGN_DOWN_POINTER_BY(pvBase, PAGE_SIZE);

    while (pjAddress < (PUCHAR)pvBase + cjSize)
    {
        if (!MmIsAddressValid(pjAddress)) return FALSE;
        pjAddress += PAGE_SIZE;
    }

    return TRUE;
}
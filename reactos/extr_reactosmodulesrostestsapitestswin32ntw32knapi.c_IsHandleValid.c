#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
typedef  size_t USHORT ;
typedef  int ULONG_PTR ;
struct TYPE_3__ {scalar_t__ FullUnique; int /*<<< orphan*/ * KernelData; } ;
typedef  int /*<<< orphan*/ * PVOID ;
typedef  TYPE_1__* PGDI_TABLE_ENTRY ;
typedef  scalar_t__ HGDIOBJ ;
typedef  int /*<<< orphan*/  BOOL ;

/* Variables and functions */
 int /*<<< orphan*/  FALSE ; 
 TYPE_1__* GdiHandleTable ; 
 int /*<<< orphan*/  TRUE ; 

BOOL
IsHandleValid(HGDIOBJ hobj)
{
    USHORT Index = (ULONG_PTR)hobj;
    PGDI_TABLE_ENTRY pentry = &GdiHandleTable[Index];

    if (pentry->KernelData == NULL ||
        pentry->KernelData < (PVOID)0x80000000 ||
        (USHORT)pentry->FullUnique != (USHORT)((ULONG_PTR)hobj >> 16))
    {
        return FALSE;
    }
    
    return TRUE;
}
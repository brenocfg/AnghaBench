#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  VOID ;
struct TYPE_7__ {TYPE_1__* VolumeFcb; int /*<<< orphan*/  DirResource; } ;
struct TYPE_6__ {scalar_t__ RefCount; int /*<<< orphan*/  Flags; int /*<<< orphan*/  PathNameU; } ;
typedef  TYPE_1__* PVFATFCB ;
typedef  TYPE_2__* PDEVICE_EXTENSION ;

/* Variables and functions */
 int /*<<< orphan*/  ASSERT (int) ; 
 int /*<<< orphan*/  BooleanFlagOn (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  DPRINT (char*,TYPE_1__*,int /*<<< orphan*/ *,scalar_t__) ; 
 int ExIsResourceAcquiredExclusive (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  FCB_IS_FAT ; 
 int /*<<< orphan*/  FCB_IS_VOLUME ; 

VOID
#ifndef KDBG
vfatGrabFCB(
#else
_vfatGrabFCB(
#endif
    PDEVICE_EXTENSION pVCB,
    PVFATFCB pFCB
#ifdef KDBG
    ,
    PCSTR File,
    ULONG Line,
    PCSTR Func
#endif
)
{
#ifdef KDBG
    if (DebugFile.Buffer != NULL && FsRtlIsNameInExpression(&DebugFile, &pFCB->LongNameU, FALSE, NULL))
    {
        DPRINT1("Inc ref count (%d, oc: %d) for: %p (%wZ) at: %s(%d) %s\n", pFCB->RefCount, pFCB->OpenHandleCount, pFCB, &pFCB->PathNameU, File, Line, Func);
    }
#else
    DPRINT("Grabbing FCB at %p: %wZ, refCount:%d\n",
           pFCB, &pFCB->PathNameU, pFCB->RefCount);
#endif

    ASSERT(ExIsResourceAcquiredExclusive(&pVCB->DirResource));

    ASSERT(!BooleanFlagOn(pFCB->Flags, FCB_IS_FAT));
    ASSERT(pFCB != pVCB->VolumeFcb && !BooleanFlagOn(pFCB->Flags, FCB_IS_VOLUME));
    ASSERT(pFCB->RefCount > 0);
    ++pFCB->RefCount;
}
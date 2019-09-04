#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_10__   TYPE_2__ ;
typedef  struct TYPE_9__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  VOID ;
typedef  int ULONG ;
struct TYPE_10__ {TYPE_1__* VolumeFcb; int /*<<< orphan*/  DirResource; } ;
struct TYPE_9__ {scalar_t__ RefCount; scalar_t__ OpenHandleCount; struct TYPE_9__* parentFcb; int /*<<< orphan*/  Flags; int /*<<< orphan*/ * FileObject; int /*<<< orphan*/  PathNameU; } ;
typedef  TYPE_1__* PVFATFCB ;
typedef  int /*<<< orphan*/ * PFILE_OBJECT ;
typedef  TYPE_2__* PDEVICE_EXTENSION ;

/* Variables and functions */
 int /*<<< orphan*/  ASSERT (int) ; 
 scalar_t__ BooleanFlagOn (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  CcUninitializeCacheMap (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  ClearFlag (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  DPRINT (char*,TYPE_1__*,int /*<<< orphan*/ *,scalar_t__) ; 
 int ExIsResourceAcquiredExclusive (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  FCB_CACHE_INITIALIZED ; 
 int /*<<< orphan*/  FCB_IS_FAT ; 
 int /*<<< orphan*/  FCB_IS_VOLUME ; 
 int /*<<< orphan*/  ObDereferenceObject (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  vfatDelFCBFromTable (TYPE_2__*,TYPE_1__*) ; 
 int /*<<< orphan*/  vfatDestroyFCB (TYPE_1__*) ; 

VOID
#ifndef KDBG
vfatReleaseFCB(
#else
_vfatReleaseFCB(
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
    PVFATFCB tmpFcb;

#ifdef KDBG
    if (DebugFile.Buffer != NULL && FsRtlIsNameInExpression(&DebugFile, &pFCB->LongNameU, FALSE, NULL))
    {
        DPRINT1("Dec ref count (%d, oc: %d) for: %p (%wZ) at: %s(%d) %s\n", pFCB->RefCount, pFCB->OpenHandleCount, pFCB, &pFCB->PathNameU, File, Line, Func);
    }
#else
    DPRINT("Releasing FCB at %p: %wZ, refCount:%d\n",
           pFCB, &pFCB->PathNameU, pFCB->RefCount);
#endif

    ASSERT(ExIsResourceAcquiredExclusive(&pVCB->DirResource));

    while (pFCB)
    {
        ULONG RefCount;

        ASSERT(!BooleanFlagOn(pFCB->Flags, FCB_IS_FAT));
        ASSERT(pFCB != pVCB->VolumeFcb && !BooleanFlagOn(pFCB->Flags, FCB_IS_VOLUME));
        ASSERT(pFCB->RefCount > 0);
        RefCount = --pFCB->RefCount;

        if (RefCount == 1 && BooleanFlagOn(pFCB->Flags, FCB_CACHE_INITIALIZED))
        {
            PFILE_OBJECT tmpFileObject;
            tmpFileObject = pFCB->FileObject;

            pFCB->FileObject = NULL;
            CcUninitializeCacheMap(tmpFileObject, NULL, NULL);
            ClearFlag(pFCB->Flags, FCB_CACHE_INITIALIZED);
            ObDereferenceObject(tmpFileObject);
        }

        if (RefCount == 0)
        {
            ASSERT(pFCB->OpenHandleCount == 0);
            tmpFcb = pFCB->parentFcb;
            vfatDelFCBFromTable(pVCB, pFCB);
            vfatDestroyFCB(pFCB);
        }
        else
        {
            tmpFcb = NULL;
        }
        pFCB = tmpFcb;
    }
}
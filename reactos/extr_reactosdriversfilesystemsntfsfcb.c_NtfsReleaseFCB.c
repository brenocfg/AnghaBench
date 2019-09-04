#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_9__   TYPE_2__ ;
typedef  struct TYPE_8__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  VOID ;
struct TYPE_9__ {scalar_t__ RefCount; int /*<<< orphan*/  FileObject; int /*<<< orphan*/  FcbListEntry; int /*<<< orphan*/  PathName; } ;
struct TYPE_8__ {int /*<<< orphan*/  FcbListLock; } ;
typedef  TYPE_1__* PNTFS_VCB ;
typedef  TYPE_2__* PNTFS_FCB ;
typedef  int /*<<< orphan*/  KIRQL ;

/* Variables and functions */
 int /*<<< orphan*/  CcUninitializeCacheMap (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  DPRINT (char*,TYPE_2__*,int /*<<< orphan*/ ,scalar_t__) ; 
 int /*<<< orphan*/  KeAcquireSpinLock (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  KeReleaseSpinLock (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  NtfsDestroyFCB (TYPE_2__*) ; 
 int /*<<< orphan*/  NtfsFCBIsDirectory (TYPE_2__*) ; 
 int /*<<< orphan*/  RemoveEntryList (int /*<<< orphan*/ *) ; 

VOID
NtfsReleaseFCB(PNTFS_VCB Vcb,
               PNTFS_FCB Fcb)
{
    KIRQL oldIrql;

    DPRINT("releasing FCB at %p: %S, refCount:%d\n",
           Fcb,
           Fcb->PathName,
           Fcb->RefCount);

    KeAcquireSpinLock(&Vcb->FcbListLock, &oldIrql);
    Fcb->RefCount--;
    if (Fcb->RefCount <= 0 && !NtfsFCBIsDirectory(Fcb))
    {
        RemoveEntryList(&Fcb->FcbListEntry);
        KeReleaseSpinLock(&Vcb->FcbListLock, oldIrql);
        CcUninitializeCacheMap(Fcb->FileObject, NULL, NULL);
        NtfsDestroyFCB(Fcb);
    }
    else
    {
        KeReleaseSpinLock(&Vcb->FcbListLock, oldIrql);
    }
}
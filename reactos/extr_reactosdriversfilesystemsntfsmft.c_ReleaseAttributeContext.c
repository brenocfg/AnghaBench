#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_5__ ;
typedef  struct TYPE_7__   TYPE_3__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  VOID ;
struct TYPE_8__ {scalar_t__ IsNonResident; } ;
struct TYPE_7__ {int /*<<< orphan*/  AttrCtxtLookasideList; } ;
struct TYPE_6__ {TYPE_5__* pRecord; int /*<<< orphan*/  DataRunsMCB; } ;
typedef  TYPE_1__* PNTFS_ATTR_CONTEXT ;

/* Variables and functions */
 int /*<<< orphan*/  ExFreePoolWithTag (TYPE_5__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ExFreeToNPagedLookasideList (int /*<<< orphan*/ *,TYPE_1__*) ; 
 int /*<<< orphan*/  FsRtlUninitializeLargeMcb (int /*<<< orphan*/ *) ; 
 TYPE_3__* NtfsGlobalData ; 
 int /*<<< orphan*/  TAG_NTFS ; 

VOID
ReleaseAttributeContext(PNTFS_ATTR_CONTEXT Context)
{
    if (Context->pRecord)
    {
        if (Context->pRecord->IsNonResident)
        {
            FsRtlUninitializeLargeMcb(&Context->DataRunsMCB);
        }

        ExFreePoolWithTag(Context->pRecord, TAG_NTFS);
    }

    ExFreeToNPagedLookasideList(&NtfsGlobalData->AttrCtxtLookasideList, Context);
}
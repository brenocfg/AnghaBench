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
struct TYPE_6__ {scalar_t__ FatType; } ;
struct TYPE_7__ {int /*<<< orphan*/  FatResource; int /*<<< orphan*/  (* GetDirtyStatus ) (TYPE_2__*,int /*<<< orphan*/ *) ;TYPE_1__ FatInfo; } ;
typedef  TYPE_2__* PDEVICE_EXTENSION ;
typedef  int /*<<< orphan*/ * PBOOLEAN ;
typedef  int /*<<< orphan*/  NTSTATUS ;

/* Variables and functions */
 int /*<<< orphan*/  DPRINT (char*,TYPE_2__*) ; 
 int /*<<< orphan*/  ExAcquireResourceSharedLite (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ExReleaseResourceLite (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  FALSE ; 
 scalar_t__ FAT12 ; 
 int /*<<< orphan*/  STATUS_SUCCESS ; 
 int /*<<< orphan*/  TRUE ; 
 int /*<<< orphan*/  stub1 (TYPE_2__*,int /*<<< orphan*/ *) ; 

NTSTATUS
GetDirtyStatus(
    PDEVICE_EXTENSION DeviceExt,
    PBOOLEAN DirtyStatus)
{
    NTSTATUS Status;

    DPRINT("GetDirtyStatus(DeviceExt %p)\n", DeviceExt);

    /* FAT12 has no dirty bit */
    if (DeviceExt->FatInfo.FatType == FAT12)
    {
        *DirtyStatus = FALSE;
        return STATUS_SUCCESS;
    }

    /* Not really in the FAT, but share the lock because
     * we're really low-level and shouldn't happent that often
     * And call the appropriate function
     */
    ExAcquireResourceSharedLite(&DeviceExt->FatResource, TRUE);
    Status = DeviceExt->GetDirtyStatus(DeviceExt, DirtyStatus);
    ExReleaseResourceLite(&DeviceExt->FatResource);

    return Status;
}
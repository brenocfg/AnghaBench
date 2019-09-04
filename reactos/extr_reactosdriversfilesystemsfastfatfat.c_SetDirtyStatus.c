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
struct TYPE_7__ {int /*<<< orphan*/  FatResource; int /*<<< orphan*/  (* SetDirtyStatus ) (TYPE_2__*,int /*<<< orphan*/ ) ;TYPE_1__ FatInfo; } ;
typedef  TYPE_2__* PDEVICE_EXTENSION ;
typedef  int /*<<< orphan*/  NTSTATUS ;
typedef  int /*<<< orphan*/  BOOLEAN ;

/* Variables and functions */
 int /*<<< orphan*/  DPRINT (char*,TYPE_2__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ExAcquireResourceExclusiveLite (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ExReleaseResourceLite (int /*<<< orphan*/ *) ; 
 scalar_t__ FAT12 ; 
 int /*<<< orphan*/  STATUS_SUCCESS ; 
 int /*<<< orphan*/  TRUE ; 
 int /*<<< orphan*/  stub1 (TYPE_2__*,int /*<<< orphan*/ ) ; 

NTSTATUS
SetDirtyStatus(
    PDEVICE_EXTENSION DeviceExt,
    BOOLEAN DirtyStatus)
{
    NTSTATUS Status;

    DPRINT("SetDirtyStatus(DeviceExt %p, DirtyStatus %d)\n", DeviceExt, DirtyStatus);

    /* FAT12 has no dirty bit */
    if (DeviceExt->FatInfo.FatType == FAT12)
    {
        return STATUS_SUCCESS;
    }

    /* Not really in the FAT, but share the lock because
     * we're really low-level and shouldn't happent that often
     * And call the appropriate function
     * Acquire exclusive because we will modify ondisk value
     */
    ExAcquireResourceExclusiveLite(&DeviceExt->FatResource, TRUE);
    Status = DeviceExt->SetDirtyStatus(DeviceExt, DirtyStatus);
    ExReleaseResourceLite(&DeviceExt->FatResource);

    return Status;
}
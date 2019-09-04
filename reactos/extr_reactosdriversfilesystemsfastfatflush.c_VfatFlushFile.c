#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_13__   TYPE_3__ ;
typedef  struct TYPE_12__   TYPE_2__ ;
typedef  struct TYPE_11__   TYPE_1__ ;

/* Type definitions */
struct TYPE_13__ {scalar_t__ Status; } ;
struct TYPE_12__ {int /*<<< orphan*/  DirResource; } ;
struct TYPE_11__ {int /*<<< orphan*/  Flags; int /*<<< orphan*/  SectionObjectPointers; int /*<<< orphan*/  PathNameU; } ;
typedef  TYPE_1__* PVFATFCB ;
typedef  TYPE_2__* PDEVICE_EXTENSION ;
typedef  scalar_t__ NTSTATUS ;
typedef  TYPE_3__ IO_STATUS_BLOCK ;

/* Variables and functions */
 scalar_t__ BooleanFlagOn (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  CcFlushCache (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ ,TYPE_3__*) ; 
 int /*<<< orphan*/  DPRINT (char*,TYPE_2__*,TYPE_1__*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  ExAcquireResourceExclusiveLite (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ExReleaseResourceLite (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  FCB_IS_DIRTY ; 
 int /*<<< orphan*/  NT_SUCCESS (scalar_t__) ; 
 scalar_t__ STATUS_INVALID_PARAMETER ; 
 scalar_t__ STATUS_SUCCESS ; 
 int /*<<< orphan*/  TRUE ; 
 scalar_t__ VfatUpdateEntry (TYPE_2__*,TYPE_1__*) ; 

__attribute__((used)) static
NTSTATUS
VfatFlushFile(
    PDEVICE_EXTENSION DeviceExt,
    PVFATFCB Fcb)
{
    IO_STATUS_BLOCK IoStatus;
    NTSTATUS Status;

    DPRINT("VfatFlushFile(DeviceExt %p, Fcb %p) for '%wZ'\n", DeviceExt, Fcb, &Fcb->PathNameU);

    CcFlushCache(&Fcb->SectionObjectPointers, NULL, 0, &IoStatus);
    if (IoStatus.Status == STATUS_INVALID_PARAMETER)
    {
        /* FIXME: Caching was possible not initialized */
        IoStatus.Status = STATUS_SUCCESS;
    }

    ExAcquireResourceExclusiveLite(&DeviceExt->DirResource, TRUE);
    if (BooleanFlagOn(Fcb->Flags, FCB_IS_DIRTY))
    {
        Status = VfatUpdateEntry(DeviceExt, Fcb);
        if (!NT_SUCCESS(Status))
        {
            IoStatus.Status = Status;
        }
    }
    ExReleaseResourceLite(&DeviceExt->DirResource);

    return IoStatus.Status;
}
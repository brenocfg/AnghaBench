#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_16__   TYPE_7__ ;
typedef  struct TYPE_15__   TYPE_5__ ;
typedef  struct TYPE_14__   TYPE_4__ ;
typedef  struct TYPE_13__   TYPE_3__ ;
typedef  struct TYPE_12__   TYPE_2__ ;
typedef  struct TYPE_11__   TYPE_1__ ;

/* Type definitions */
struct TYPE_16__ {TYPE_4__* DeviceObject; } ;
struct TYPE_15__ {int /*<<< orphan*/  DirResource; } ;
struct TYPE_14__ {TYPE_5__* DeviceExtension; } ;
struct TYPE_13__ {int Flags; TYPE_2__* Irp; TYPE_4__* DeviceObject; } ;
struct TYPE_11__ {int /*<<< orphan*/  Information; } ;
struct TYPE_12__ {TYPE_1__ IoStatus; } ;
typedef  TYPE_3__* PNTFS_IRP_CONTEXT ;
typedef  TYPE_4__* PDEVICE_OBJECT ;
typedef  TYPE_5__* PDEVICE_EXTENSION ;
typedef  int /*<<< orphan*/  NTSTATUS ;

/* Variables and functions */
 int /*<<< orphan*/  DPRINT (char*) ; 
 int /*<<< orphan*/  ExAcquireResourceExclusiveLite (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ExReleaseResourceLite (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  FILE_OPENED ; 
 int IRPCONTEXT_CANWAIT ; 
 int /*<<< orphan*/  NtfsCreateFile (TYPE_4__*,TYPE_3__*) ; 
 TYPE_7__* NtfsGlobalData ; 
 int /*<<< orphan*/  NtfsMarkIrpContextForQueue (TYPE_3__*) ; 
 int /*<<< orphan*/  STATUS_SUCCESS ; 
 int /*<<< orphan*/  TRUE ; 

NTSTATUS
NtfsCreate(PNTFS_IRP_CONTEXT IrpContext)
{
    PDEVICE_EXTENSION DeviceExt;
    NTSTATUS Status;
    PDEVICE_OBJECT DeviceObject;

    DeviceObject = IrpContext->DeviceObject;
    if (DeviceObject == NtfsGlobalData->DeviceObject)
    {
        /* DeviceObject represents FileSystem instead of logical volume */
        DPRINT("Opening file system\n");
        IrpContext->Irp->IoStatus.Information = FILE_OPENED;
        return STATUS_SUCCESS;
    }

    DeviceExt = DeviceObject->DeviceExtension;

    if (!(IrpContext->Flags & IRPCONTEXT_CANWAIT))
    {
        return NtfsMarkIrpContextForQueue(IrpContext);
    }

    ExAcquireResourceExclusiveLite(&DeviceExt->DirResource,
                                   TRUE);
    Status = NtfsCreateFile(DeviceObject,
                            IrpContext);
    ExReleaseResourceLite(&DeviceExt->DirResource);

    return Status;
}
#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_11__   TYPE_4__ ;
typedef  struct TYPE_10__   TYPE_3__ ;
typedef  struct TYPE_9__   TYPE_2__ ;
typedef  struct TYPE_8__   TYPE_1__ ;

/* Type definitions */
struct TYPE_11__ {int Flags; int OpenHandleCount; } ;
struct TYPE_10__ {TYPE_1__* FsContext; } ;
struct TYPE_9__ {TYPE_3__* FileObject; } ;
struct TYPE_8__ {int Flags; } ;
typedef  TYPE_1__* PNTFS_FCB ;
typedef  int /*<<< orphan*/  PIRP ;
typedef  TYPE_2__* PIO_STACK_LOCATION ;
typedef  TYPE_3__* PFILE_OBJECT ;
typedef  TYPE_4__* PDEVICE_EXTENSION ;
typedef  int /*<<< orphan*/  NTSTATUS ;
typedef  scalar_t__ BOOLEAN ;

/* Variables and functions */
 int /*<<< orphan*/  DPRINT (char*,TYPE_4__*,int /*<<< orphan*/ ,scalar_t__) ; 
 int FCB_IS_VOLUME ; 
 TYPE_2__* IoGetCurrentIrpStackLocation (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  STATUS_ACCESS_DENIED ; 
 int /*<<< orphan*/  STATUS_SUCCESS ; 
 int VCB_VOLUME_LOCKED ; 

__attribute__((used)) static
NTSTATUS
LockOrUnlockVolume(PDEVICE_EXTENSION DeviceExt,
                   PIRP Irp,
                   BOOLEAN Lock)
{
    PFILE_OBJECT FileObject;
    PNTFS_FCB Fcb;
    PIO_STACK_LOCATION Stack;

    DPRINT("LockOrUnlockVolume(%p, %p, %d)\n", DeviceExt, Irp, Lock);

    Stack = IoGetCurrentIrpStackLocation(Irp);
    FileObject = Stack->FileObject;
    Fcb = FileObject->FsContext;

    /* Only allow locking with the volume open */
    if (!(Fcb->Flags & FCB_IS_VOLUME))
    {
        return STATUS_ACCESS_DENIED;
    }

    /* Bail out if it's already in the demanded state */
    if (((DeviceExt->Flags & VCB_VOLUME_LOCKED) && Lock) ||
        (!(DeviceExt->Flags & VCB_VOLUME_LOCKED) && !Lock))
    {
        return STATUS_ACCESS_DENIED;
    }

    /* Deny locking if we're not alone */
    if (Lock && DeviceExt->OpenHandleCount != 1)
    {
        return STATUS_ACCESS_DENIED;
    }

    /* Finally, proceed */
    if (Lock)
    {
        DeviceExt->Flags |= VCB_VOLUME_LOCKED;
    }
    else
    {
        DeviceExt->Flags &= ~VCB_VOLUME_LOCKED;
    }

    return STATUS_SUCCESS;
}
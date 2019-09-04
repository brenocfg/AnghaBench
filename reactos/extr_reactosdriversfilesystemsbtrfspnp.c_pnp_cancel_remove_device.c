#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_10__   TYPE_6__ ;
typedef  struct TYPE_9__   TYPE_2__ ;
typedef  struct TYPE_8__   TYPE_1__ ;

/* Type definitions */
struct TYPE_8__ {int /*<<< orphan*/  tree_lock; TYPE_6__* root_fileref; } ;
typedef  TYPE_1__ device_extension ;
struct TYPE_10__ {scalar_t__ open_count; scalar_t__ fcb; } ;
struct TYPE_9__ {TYPE_1__* DeviceExtension; } ;
typedef  TYPE_2__* PDEVICE_OBJECT ;
typedef  int /*<<< orphan*/  NTSTATUS ;

/* Variables and functions */
 int /*<<< orphan*/  ExAcquireResourceSharedLite (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ExReleaseResourceLite (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  IRP_MN_CANCEL_REMOVE_DEVICE ; 
 int /*<<< orphan*/  NT_SUCCESS (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  STATUS_ACCESS_DENIED ; 
 int /*<<< orphan*/  STATUS_SUCCESS ; 
 int /*<<< orphan*/  TRUE ; 
 int /*<<< orphan*/  WARN (char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  acquire_fcb_lock_exclusive (TYPE_1__*) ; 
 scalar_t__ has_open_children (TYPE_6__*) ; 
 int /*<<< orphan*/  release_fcb_lock (TYPE_1__*) ; 
 int /*<<< orphan*/  send_disks_pnp_message (TYPE_1__*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static NTSTATUS pnp_cancel_remove_device(PDEVICE_OBJECT DeviceObject) {
    device_extension* Vcb = DeviceObject->DeviceExtension;
    NTSTATUS Status;

    ExAcquireResourceSharedLite(&Vcb->tree_lock, TRUE);

    acquire_fcb_lock_exclusive(Vcb);

    if (Vcb->root_fileref && Vcb->root_fileref->fcb && (Vcb->root_fileref->open_count > 0 || has_open_children(Vcb->root_fileref))) {
        Status = STATUS_ACCESS_DENIED;
        goto end;
    }

    Status = send_disks_pnp_message(Vcb, IRP_MN_CANCEL_REMOVE_DEVICE);
    if (!NT_SUCCESS(Status)) {
        WARN("send_disks_pnp_message returned %08x\n", Status);
        goto end;
    }

end:
    release_fcb_lock(Vcb);
    ExReleaseResourceLite(&Vcb->tree_lock);

    return STATUS_SUCCESS;
}
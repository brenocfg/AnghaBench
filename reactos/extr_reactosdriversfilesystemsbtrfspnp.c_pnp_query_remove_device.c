#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_12__   TYPE_6__ ;
typedef  struct TYPE_11__   TYPE_2__ ;
typedef  struct TYPE_10__   TYPE_1__ ;

/* Type definitions */
struct TYPE_10__ {int /*<<< orphan*/  tree_lock; int /*<<< orphan*/  readonly; scalar_t__ need_write; int /*<<< orphan*/  removing; TYPE_6__* root_fileref; } ;
typedef  TYPE_1__ device_extension ;
struct TYPE_12__ {scalar_t__ open_count; scalar_t__ fcb; } ;
struct TYPE_11__ {TYPE_1__* DeviceExtension; } ;
typedef  int /*<<< orphan*/  PIRP ;
typedef  TYPE_2__* PDEVICE_OBJECT ;
typedef  int /*<<< orphan*/  NTSTATUS ;

/* Variables and functions */
 int /*<<< orphan*/  ERR (char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ExAcquireResourceExclusiveLite (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ExReleaseResourceLite (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  IRP_MN_QUERY_REMOVE_DEVICE ; 
 int /*<<< orphan*/  NT_SUCCESS (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  STATUS_ACCESS_DENIED ; 
 int /*<<< orphan*/  STATUS_SUCCESS ; 
 int /*<<< orphan*/  TRUE ; 
 int /*<<< orphan*/  WARN (char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  acquire_fcb_lock_exclusive (TYPE_1__*) ; 
 int /*<<< orphan*/  do_write (TYPE_1__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  free_trees (TYPE_1__*) ; 
 scalar_t__ has_open_children (TYPE_6__*) ; 
 int /*<<< orphan*/  release_fcb_lock (TYPE_1__*) ; 
 int /*<<< orphan*/  send_disks_pnp_message (TYPE_1__*,int /*<<< orphan*/ ) ; 

NTSTATUS pnp_query_remove_device(PDEVICE_OBJECT DeviceObject, PIRP Irp) {
    device_extension* Vcb = DeviceObject->DeviceExtension;
    NTSTATUS Status;

    ExAcquireResourceExclusiveLite(&Vcb->tree_lock, TRUE);

    acquire_fcb_lock_exclusive(Vcb);

    if (Vcb->root_fileref && Vcb->root_fileref->fcb && (Vcb->root_fileref->open_count > 0 || has_open_children(Vcb->root_fileref))) {
        Status = STATUS_ACCESS_DENIED;
        goto end;
    }

    Status = send_disks_pnp_message(Vcb, IRP_MN_QUERY_REMOVE_DEVICE);
    if (!NT_SUCCESS(Status)) {
        WARN("send_disks_pnp_message returned %08x\n", Status);
        goto end;
    }

    Vcb->removing = TRUE;

    if (Vcb->need_write && !Vcb->readonly) {
        Status = do_write(Vcb, Irp);

        free_trees(Vcb);

        if (!NT_SUCCESS(Status)) {
            ERR("do_write returned %08x\n", Status);
            goto end;
        }
    }


    Status = STATUS_SUCCESS;
end:
    release_fcb_lock(Vcb);

    ExReleaseResourceLite(&Vcb->tree_lock);

    return Status;
}
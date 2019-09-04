#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct TYPE_6__ {scalar_t__ Status; } ;
struct TYPE_5__ {int /*<<< orphan*/  StorageDevice; } ;
typedef  TYPE_1__* PVCB ;
typedef  scalar_t__ PIRP ;
typedef  scalar_t__ NTSTATUS ;
typedef  int /*<<< orphan*/  KEVENT ;
typedef  TYPE_2__ IO_STATUS_BLOCK ;

/* Variables and functions */
 int /*<<< orphan*/  Executive ; 
 int /*<<< orphan*/  FALSE ; 
 int /*<<< orphan*/  IRP_MJ_SHUTDOWN ; 
 scalar_t__ IoBuildSynchronousFsdRequest (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ *,TYPE_2__*) ; 
 scalar_t__ IoCallDriver (int /*<<< orphan*/ ,scalar_t__) ; 
 int /*<<< orphan*/  KeInitializeEvent (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  KeWaitForSingleObject (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  KernelMode ; 
 int /*<<< orphan*/  NotificationEvent ; 
 scalar_t__ STATUS_INSUFFICIENT_RESOURCES ; 
 scalar_t__ STATUS_PENDING ; 

__attribute__((used)) static
NTSTATUS
VfatDiskShutDown(
    PVCB Vcb)
{
    PIRP Irp;
    KEVENT Event;
    NTSTATUS Status;
    IO_STATUS_BLOCK IoStatus;

    KeInitializeEvent(&Event, NotificationEvent, FALSE);
    Irp = IoBuildSynchronousFsdRequest(IRP_MJ_SHUTDOWN, Vcb->StorageDevice,
                                       NULL, 0, NULL, &Event, &IoStatus);
    if (Irp)
    {
        Status = IoCallDriver(Vcb->StorageDevice, Irp);
        if (Status == STATUS_PENDING)
        {
            KeWaitForSingleObject(&Event, Executive, KernelMode, FALSE, NULL);
            Status = IoStatus.Status;
        }
    }
    else
    {
        Status = STATUS_INSUFFICIENT_RESOURCES;
    }

    return Status;
}
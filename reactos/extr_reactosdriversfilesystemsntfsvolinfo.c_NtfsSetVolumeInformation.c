#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_3__ ;
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
struct TYPE_6__ {scalar_t__ Information; int /*<<< orphan*/  Status; } ;
struct TYPE_8__ {TYPE_1__ IoStatus; } ;
struct TYPE_7__ {TYPE_3__* Irp; } ;
typedef  TYPE_2__* PNTFS_IRP_CONTEXT ;
typedef  TYPE_3__* PIRP ;
typedef  int /*<<< orphan*/  NTSTATUS ;

/* Variables and functions */
 int /*<<< orphan*/  ASSERT (TYPE_2__*) ; 
 int /*<<< orphan*/  DPRINT (char*) ; 
 int /*<<< orphan*/  STATUS_NOT_SUPPORTED ; 

NTSTATUS
NtfsSetVolumeInformation(PNTFS_IRP_CONTEXT IrpContext)
{
    PIRP Irp;

    DPRINT("NtfsSetVolumeInformation() called\n");

    ASSERT(IrpContext);

    Irp = IrpContext->Irp;
    Irp->IoStatus.Status = STATUS_NOT_SUPPORTED;
    Irp->IoStatus.Information = 0;

    return STATUS_NOT_SUPPORTED;
}
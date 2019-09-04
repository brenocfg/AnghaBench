#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_10__   TYPE_3__ ;
typedef  struct TYPE_9__   TYPE_2__ ;
typedef  struct TYPE_8__   TYPE_1__ ;

/* Type definitions */
struct TYPE_10__ {int MinorFunction; int /*<<< orphan*/  Flags; TYPE_2__* Irp; } ;
struct TYPE_8__ {scalar_t__ Information; } ;
struct TYPE_9__ {TYPE_1__ IoStatus; } ;
typedef  TYPE_3__* PVFAT_IRP_CONTEXT ;
typedef  scalar_t__ NTSTATUS ;

/* Variables and functions */
 scalar_t__ BooleanFlagOn (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  DPRINT (char*,int) ; 
 scalar_t__ DoQuery (TYPE_3__*) ; 
 int /*<<< orphan*/  IRPCONTEXT_COMPLETE ; 
#define  IRP_MN_NOTIFY_CHANGE_DIRECTORY 129 
#define  IRP_MN_QUERY_DIRECTORY 128 
 scalar_t__ STATUS_INVALID_DEVICE_REQUEST ; 
 scalar_t__ STATUS_PENDING ; 
 scalar_t__ STATUS_SUCCESS ; 
 scalar_t__ VfatMarkIrpContextForQueue (TYPE_3__*) ; 
 scalar_t__ VfatNotifyChangeDirectory (TYPE_3__*) ; 

NTSTATUS
VfatDirectoryControl(
    PVFAT_IRP_CONTEXT IrpContext)
{
    NTSTATUS Status = STATUS_SUCCESS;

    IrpContext->Irp->IoStatus.Information = 0;

    switch (IrpContext->MinorFunction)
    {
        case IRP_MN_QUERY_DIRECTORY:
            Status = DoQuery (IrpContext);
            break;

        case IRP_MN_NOTIFY_CHANGE_DIRECTORY:
            Status = VfatNotifyChangeDirectory(IrpContext);
            break;

        default:
            /* Error */
            DPRINT("Unexpected minor function %x in VFAT driver\n",
                   IrpContext->MinorFunction);
            Status = STATUS_INVALID_DEVICE_REQUEST;
            break;
    }

    if (Status == STATUS_PENDING && BooleanFlagOn(IrpContext->Flags, IRPCONTEXT_COMPLETE))
    {
        return VfatMarkIrpContextForQueue(IrpContext);
    }

    return Status;
}
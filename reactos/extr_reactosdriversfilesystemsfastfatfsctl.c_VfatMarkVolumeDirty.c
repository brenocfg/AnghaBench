#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_9__   TYPE_3__ ;
typedef  struct TYPE_8__   TYPE_2__ ;
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
struct TYPE_9__ {TYPE_1__* VolumeFcb; } ;
struct TYPE_8__ {TYPE_3__* DeviceExt; } ;
struct TYPE_7__ {int /*<<< orphan*/  Flags; } ;
typedef  TYPE_2__* PVFAT_IRP_CONTEXT ;
typedef  TYPE_3__* PDEVICE_EXTENSION ;
typedef  int /*<<< orphan*/  NTSTATUS ;

/* Variables and functions */
 int /*<<< orphan*/  BooleanFlagOn (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  DPRINT (char*,TYPE_2__*) ; 
 int /*<<< orphan*/  STATUS_SUCCESS ; 
 int /*<<< orphan*/  SetDirtyStatus (TYPE_3__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  TRUE ; 
 int /*<<< orphan*/  VCB_CLEAR_DIRTY ; 
 int /*<<< orphan*/  VCB_IS_DIRTY ; 

__attribute__((used)) static
NTSTATUS
VfatMarkVolumeDirty(
    PVFAT_IRP_CONTEXT IrpContext)
{
    PDEVICE_EXTENSION DeviceExt;
    NTSTATUS Status = STATUS_SUCCESS;

    DPRINT("VfatMarkVolumeDirty(IrpContext %p)\n", IrpContext);
    DeviceExt = IrpContext->DeviceExt;

    if (!BooleanFlagOn(DeviceExt->VolumeFcb->Flags, VCB_IS_DIRTY))
    {
        Status = SetDirtyStatus(DeviceExt, TRUE);
    }

    DeviceExt->VolumeFcb->Flags &= ~VCB_CLEAR_DIRTY;

    return Status;
}
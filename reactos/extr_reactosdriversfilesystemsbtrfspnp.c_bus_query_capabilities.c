#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_15__   TYPE_6__ ;
typedef  struct TYPE_14__   TYPE_5__ ;
typedef  struct TYPE_13__   TYPE_4__ ;
typedef  struct TYPE_12__   TYPE_3__ ;
typedef  struct TYPE_11__   TYPE_2__ ;
typedef  struct TYPE_10__   TYPE_1__ ;

/* Type definitions */
struct TYPE_15__ {void* SilentInstall; void* UniqueID; } ;
struct TYPE_10__ {TYPE_6__* Capabilities; } ;
struct TYPE_11__ {TYPE_1__ DeviceCapabilities; } ;
struct TYPE_14__ {TYPE_2__ Parameters; } ;
struct TYPE_12__ {int /*<<< orphan*/  Status; } ;
struct TYPE_13__ {TYPE_3__ IoStatus; } ;
typedef  TYPE_4__* PIRP ;
typedef  TYPE_5__* PIO_STACK_LOCATION ;
typedef  TYPE_6__* PDEVICE_CAPABILITIES ;

/* Variables and functions */
 TYPE_5__* IoGetCurrentIrpStackLocation (TYPE_4__*) ; 
 int /*<<< orphan*/  STATUS_SUCCESS ; 
 void* TRUE ; 

__attribute__((used)) static void bus_query_capabilities(PIRP Irp) {
    PIO_STACK_LOCATION IrpSp = IoGetCurrentIrpStackLocation(Irp);
    PDEVICE_CAPABILITIES dc = IrpSp->Parameters.DeviceCapabilities.Capabilities;

    dc->UniqueID = TRUE;
    dc->SilentInstall = TRUE;

    Irp->IoStatus.Status = STATUS_SUCCESS;
}
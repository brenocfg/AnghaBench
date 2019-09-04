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
struct TYPE_5__ {scalar_t__ Information; int /*<<< orphan*/  Status; } ;
struct TYPE_6__ {TYPE_1__ IoStatus; } ;
typedef  TYPE_2__* PIRP ;
typedef  int /*<<< orphan*/  PIO_STACK_LOCATION ;
typedef  int /*<<< orphan*/  NTSTATUS ;

/* Variables and functions */
 int /*<<< orphan*/  DPRINT (char*) ; 
 int /*<<< orphan*/  IO_NO_INCREMENT ; 
 int /*<<< orphan*/  IoCompleteRequest (TYPE_2__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  STATUS_SUCCESS ; 

__attribute__((used)) static
NTSTATUS
WaitForBind(PIRP Irp, PIO_STACK_LOCATION IrpSp)
{
    /* I've seen several code samples that use this IOCTL but there's
     * no official documentation on it. I'm just implementing it as a no-op
     * right now because I don't see any reason we need it. We handle an open
     * and bind just fine with IRP_MJ_CREATE and IOCTL_NDISUIO_OPEN_DEVICE */
    DPRINT("Wait for bind complete\n");
    
    Irp->IoStatus.Status = STATUS_SUCCESS;
    Irp->IoStatus.Information = 0;
    
    IoCompleteRequest(Irp, IO_NO_INCREMENT);
    
    return STATUS_SUCCESS;
}
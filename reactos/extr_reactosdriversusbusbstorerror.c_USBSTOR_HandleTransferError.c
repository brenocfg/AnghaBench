#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_27__   TYPE_8__ ;
typedef  struct TYPE_26__   TYPE_6__ ;
typedef  struct TYPE_25__   TYPE_5__ ;
typedef  struct TYPE_24__   TYPE_4__ ;
typedef  struct TYPE_23__   TYPE_3__ ;
typedef  struct TYPE_22__   TYPE_2__ ;
typedef  struct TYPE_21__   TYPE_1__ ;
typedef  struct TYPE_20__   TYPE_10__ ;

/* Type definitions */
struct TYPE_23__ {scalar_t__ Argument1; } ;
struct TYPE_24__ {TYPE_3__ Others; } ;
struct TYPE_27__ {TYPE_4__ Parameters; } ;
struct TYPE_25__ {scalar_t__ Information; int /*<<< orphan*/  Status; } ;
struct TYPE_26__ {int RetryCount; struct TYPE_26__* cbw; TYPE_10__* FDODeviceExtension; struct TYPE_26__* Irp; struct TYPE_26__* Self; struct TYPE_26__* PDODeviceExtension; int /*<<< orphan*/  LowerDeviceObject; TYPE_5__ IoStatus; scalar_t__ Cdb; } ;
struct TYPE_22__ {TYPE_1__* Pipes; } ;
struct TYPE_21__ {int /*<<< orphan*/  PipeHandle; } ;
struct TYPE_20__ {size_t BulkInPipeIndex; size_t BulkOutPipeIndex; int /*<<< orphan*/ * LastTimerActiveSrb; int /*<<< orphan*/  TimerWorkQueueEnabled; void* SrbErrorHandlingActive; TYPE_2__* InterfaceInformation; int /*<<< orphan*/  LowerDeviceObject; } ;
typedef  TYPE_6__* PSCSI_REQUEST_BLOCK ;
typedef  TYPE_6__* PIRP_CONTEXT ;
typedef  TYPE_8__* PIO_STACK_LOCATION ;
typedef  int /*<<< orphan*/  PDEVICE_OBJECT ;
typedef  TYPE_6__* PCDB ;
typedef  int /*<<< orphan*/  NTSTATUS ;

/* Variables and functions */
 int /*<<< orphan*/  ASSERT (TYPE_6__*) ; 
 int /*<<< orphan*/  DPRINT1 (char*,int,...) ; 
 void* FALSE ; 
 int /*<<< orphan*/  FreeItem (TYPE_6__*) ; 
 int /*<<< orphan*/  IO_NO_INCREMENT ; 
 int /*<<< orphan*/  IoCompleteRequest (TYPE_6__*,int /*<<< orphan*/ ) ; 
 TYPE_8__* IoGetCurrentIrpStackLocation (TYPE_6__*) ; 
 scalar_t__ NT_SUCCESS (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  STATUS_SUCCESS ; 
 int /*<<< orphan*/  TRUE ; 
 int /*<<< orphan*/  USBSTOR_HandleExecuteSCSI (TYPE_6__*,TYPE_6__*,int) ; 
 int /*<<< orphan*/  USBSTOR_QueueNextRequest (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  USBSTOR_QueueTerminateRequest (int /*<<< orphan*/ ,TYPE_6__*) ; 
 int /*<<< orphan*/  USBSTOR_ResetDevice (int /*<<< orphan*/ ,TYPE_10__*) ; 
 int /*<<< orphan*/  USBSTOR_ResetPipeWithHandle (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

NTSTATUS
USBSTOR_HandleTransferError(
    PDEVICE_OBJECT DeviceObject,
    PIRP_CONTEXT Context)
{
    NTSTATUS Status = STATUS_SUCCESS;
    PIO_STACK_LOCATION Stack;
    PSCSI_REQUEST_BLOCK Request;
    PCDB pCDB;

    //
    // sanity checks
    //
    ASSERT(Context);
    ASSERT(Context->PDODeviceExtension);
    ASSERT(Context->PDODeviceExtension->Self);
    ASSERT(Context->Irp);

    //
    // first perform a mass storage reset step 1 in 5.3.4 USB Mass Storage Bulk Only Specification
    //
    Status = USBSTOR_ResetDevice(Context->FDODeviceExtension->LowerDeviceObject, Context->FDODeviceExtension);
    if (NT_SUCCESS(Status))
    {
        //
        // step 2 reset bulk in pipe section 5.3.4
        //
        Status = USBSTOR_ResetPipeWithHandle(Context->FDODeviceExtension->LowerDeviceObject, Context->FDODeviceExtension->InterfaceInformation->Pipes[Context->FDODeviceExtension->BulkInPipeIndex].PipeHandle);
        if (NT_SUCCESS(Status))
        {
            //
            // finally reset bulk out pipe
            //
            Status = USBSTOR_ResetPipeWithHandle(Context->FDODeviceExtension->LowerDeviceObject, Context->FDODeviceExtension->InterfaceInformation->Pipes[Context->FDODeviceExtension->BulkOutPipeIndex].PipeHandle);
        }
    }

    //
    // get next stack location
    //
    Stack = IoGetCurrentIrpStackLocation(Context->Irp);

    //
    // get request block
    //
    Request = (PSCSI_REQUEST_BLOCK)Stack->Parameters.Others.Argument1;
    ASSERT(Request);

    //
    // obtain request type
    //
    pCDB = (PCDB)Request->Cdb;
    ASSERT(pCDB);

    if (Status != STATUS_SUCCESS || Context->RetryCount >= 1)
    {
        //
        // Complete the master IRP
        //
        Context->Irp->IoStatus.Status = Status;
        Context->Irp->IoStatus.Information = 0;
        USBSTOR_QueueTerminateRequest(Context->PDODeviceExtension->LowerDeviceObject, Context->Irp);
        IoCompleteRequest(Context->Irp, IO_NO_INCREMENT);

        //
        // Start the next request
        //
        USBSTOR_QueueNextRequest(Context->PDODeviceExtension->LowerDeviceObject);

        //
        // srb handling finished
        //
        Context->FDODeviceExtension->SrbErrorHandlingActive = FALSE;

        //
        // clear timer srb
        //
        Context->FDODeviceExtension->LastTimerActiveSrb = NULL;
    }
    else
    {
        DPRINT1("Retrying Count %lu %p\n", Context->RetryCount, Context->PDODeviceExtension->Self);

        //
        // re-schedule request
        //
        USBSTOR_HandleExecuteSCSI(Context->PDODeviceExtension->Self, Context->Irp, Context->RetryCount + 1);

        //
        // srb error handling finished
        //
        Context->FDODeviceExtension->SrbErrorHandlingActive = FALSE;

        //
        // srb error handling finished
        //
        Context->FDODeviceExtension->TimerWorkQueueEnabled = TRUE;

        //
        // clear timer srb
        //
        Context->FDODeviceExtension->LastTimerActiveSrb = NULL;
    }

    //
    // cleanup irp context
    //
    FreeItem(Context->cbw);
    FreeItem(Context);


    DPRINT1("USBSTOR_HandleTransferError returning with Status %x\n", Status);
    return Status;
}
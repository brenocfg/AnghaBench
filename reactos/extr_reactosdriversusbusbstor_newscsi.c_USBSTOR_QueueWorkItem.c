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
struct TYPE_9__ {int /*<<< orphan*/  WorkQueueItem; int /*<<< orphan*/  DeviceObject; int /*<<< orphan*/  Irp; TYPE_2__* Context; } ;
struct TYPE_8__ {TYPE_1__* FDODeviceExtension; } ;
struct TYPE_7__ {int /*<<< orphan*/  FunctionalDeviceObject; int /*<<< orphan*/  TimerWorkQueueEnabled; int /*<<< orphan*/  SrbErrorHandlingActive; } ;
typedef  TYPE_2__* PIRP_CONTEXT ;
typedef  int /*<<< orphan*/  PIRP ;
typedef  TYPE_3__* PERRORHANDLER_WORKITEM_DATA ;
typedef  int /*<<< orphan*/  NTSTATUS ;
typedef  int /*<<< orphan*/  ERRORHANDLER_WORKITEM_DATA ;

/* Variables and functions */
 int /*<<< orphan*/  DPRINT1 (char*) ; 
 int /*<<< orphan*/  DelayedWorkQueue ; 
 int /*<<< orphan*/  ErrorHandlerWorkItemRoutine ; 
 TYPE_3__* ExAllocatePoolWithTag (int /*<<< orphan*/ ,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ExInitializeWorkItem (int /*<<< orphan*/ *,int /*<<< orphan*/ ,TYPE_3__*) ; 
 int /*<<< orphan*/  ExQueueWorkItem (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  FALSE ; 
 int /*<<< orphan*/  NonPagedPool ; 
 int /*<<< orphan*/  STATUS_INSUFFICIENT_RESOURCES ; 
 int /*<<< orphan*/  STATUS_MORE_PROCESSING_REQUIRED ; 
 int /*<<< orphan*/  TRUE ; 
 int /*<<< orphan*/  USB_STOR_TAG ; 

NTSTATUS
USBSTOR_QueueWorkItem(
    PIRP_CONTEXT Context,
    PIRP Irp)
{
    PERRORHANDLER_WORKITEM_DATA ErrorHandlerWorkItemData;

    //
    // Allocate Work Item Data
    //
    ErrorHandlerWorkItemData = ExAllocatePoolWithTag(NonPagedPool, sizeof(ERRORHANDLER_WORKITEM_DATA), USB_STOR_TAG);
    if (!ErrorHandlerWorkItemData)
    {
        //
        // no memory
        //
        return STATUS_INSUFFICIENT_RESOURCES;
    }

    //
    // error handling started
    //
    Context->FDODeviceExtension->SrbErrorHandlingActive = TRUE;

    //
    // srb error handling finished
    //
    Context->FDODeviceExtension->TimerWorkQueueEnabled = FALSE;

    //
    // Initialize and queue the work item to handle the error
    //
    ExInitializeWorkItem(&ErrorHandlerWorkItemData->WorkQueueItem,
                         ErrorHandlerWorkItemRoutine,
                         ErrorHandlerWorkItemData);

    ErrorHandlerWorkItemData->DeviceObject = Context->FDODeviceExtension->FunctionalDeviceObject;
    ErrorHandlerWorkItemData->Context = Context;
    ErrorHandlerWorkItemData->Irp = Irp;
    ErrorHandlerWorkItemData->DeviceObject = Context->FDODeviceExtension->FunctionalDeviceObject;

    DPRINT1("Queuing WorkItemROutine\n");
    ExQueueWorkItem(&ErrorHandlerWorkItemData->WorkQueueItem, DelayedWorkQueue);
    return STATUS_MORE_PROCESSING_REQUIRED;
}
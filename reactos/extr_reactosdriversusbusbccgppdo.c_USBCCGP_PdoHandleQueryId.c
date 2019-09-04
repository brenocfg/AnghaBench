#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_23__   TYPE_9__ ;
typedef  struct TYPE_22__   TYPE_8__ ;
typedef  struct TYPE_21__   TYPE_7__ ;
typedef  struct TYPE_20__   TYPE_6__ ;
typedef  struct TYPE_19__   TYPE_5__ ;
typedef  struct TYPE_18__   TYPE_4__ ;
typedef  struct TYPE_17__   TYPE_3__ ;
typedef  struct TYPE_16__   TYPE_2__ ;
typedef  struct TYPE_15__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  WCHAR ;
typedef  void* ULONG_PTR ;
struct TYPE_23__ {scalar_t__ DeviceExtension; } ;
struct TYPE_15__ {scalar_t__ IdType; } ;
struct TYPE_16__ {TYPE_1__ QueryId; } ;
struct TYPE_22__ {TYPE_2__ Parameters; } ;
struct TYPE_18__ {void* Information; int /*<<< orphan*/  Status; } ;
struct TYPE_21__ {TYPE_4__ IoStatus; } ;
struct TYPE_20__ {TYPE_3__* FunctionDescriptor; int /*<<< orphan*/  NextDeviceObject; } ;
struct TYPE_19__ {int Length; int /*<<< orphan*/  Buffer; } ;
struct TYPE_17__ {char* FunctionNumber; TYPE_5__ CompatibleId; TYPE_5__ HardwareId; } ;
typedef  int /*<<< orphan*/  PVOID ;
typedef  TYPE_5__* PUNICODE_STRING ;
typedef  TYPE_6__* PPDO_DEVICE_EXTENSION ;
typedef  TYPE_7__* PIRP ;
typedef  TYPE_8__* PIO_STACK_LOCATION ;
typedef  TYPE_9__* PDEVICE_OBJECT ;
typedef  int /*<<< orphan*/  NTSTATUS ;
typedef  char* LPWSTR ;

/* Variables and functions */
 int /*<<< orphan*/  ASSERT (void*) ; 
 char* AllocateItem (int /*<<< orphan*/ ,int) ; 
 scalar_t__ BusQueryCompatibleIDs ; 
 scalar_t__ BusQueryDeviceID ; 
 scalar_t__ BusQueryHardwareIDs ; 
 scalar_t__ BusQueryInstanceID ; 
 int /*<<< orphan*/  DPRINT (char*,char*) ; 
 int /*<<< orphan*/  ExFreePool (int /*<<< orphan*/ ) ; 
 TYPE_8__* IoGetCurrentIrpStackLocation (TYPE_7__*) ; 
 scalar_t__ NT_SUCCESS (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  NonPagedPool ; 
 int /*<<< orphan*/  RtlCopyMemory (char*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  STATUS_INSUFFICIENT_RESOURCES ; 
 int /*<<< orphan*/  STATUS_SUCCESS ; 
 char UNICODE_NULL ; 
 int /*<<< orphan*/  USBCCGP_SyncForwardIrp (int /*<<< orphan*/ ,TYPE_7__*) ; 
 int /*<<< orphan*/  swprintf (char*,char*,char*,...) ; 
 int wcslen (char*) ; 

NTSTATUS
USBCCGP_PdoHandleQueryId(
    PDEVICE_OBJECT DeviceObject,
    PIRP Irp)
{
    PIO_STACK_LOCATION IoStack;
    PUNICODE_STRING DeviceString = NULL;
    PPDO_DEVICE_EXTENSION PDODeviceExtension;
    NTSTATUS Status;
    LPWSTR Buffer;

    //
    // get current irp stack location
    //
    IoStack = IoGetCurrentIrpStackLocation(Irp);

    //
    // get device extension
    //
    PDODeviceExtension = (PPDO_DEVICE_EXTENSION)DeviceObject->DeviceExtension;


    if (IoStack->Parameters.QueryId.IdType == BusQueryDeviceID)
    {
        //
        // handle query device id
        //
        Status = USBCCGP_SyncForwardIrp(PDODeviceExtension->NextDeviceObject, Irp);
        if (NT_SUCCESS(Status))
        {
            //
            // allocate buffer
            //
            Buffer = AllocateItem(NonPagedPool, (wcslen((LPWSTR)Irp->IoStatus.Information) + 7) * sizeof(WCHAR));
            if (Buffer)
            {
                //
                // append interface number
                //
                ASSERT(Irp->IoStatus.Information);
                swprintf(Buffer, L"%s&MI_%02x", (LPWSTR)Irp->IoStatus.Information, PDODeviceExtension->FunctionDescriptor->FunctionNumber);
                DPRINT("BusQueryDeviceID %S\n", Buffer);

                ExFreePool((PVOID)Irp->IoStatus.Information);
                Irp->IoStatus.Information = (ULONG_PTR)Buffer;
            }
            else
            {
                //
                // no memory
                //
                Status = STATUS_INSUFFICIENT_RESOURCES;
            }
        }
        return Status;
    }
    else if (IoStack->Parameters.QueryId.IdType == BusQueryHardwareIDs)
    {
        //
        // handle instance id
        //
        DeviceString = &PDODeviceExtension->FunctionDescriptor->HardwareId;
    }
    else if (IoStack->Parameters.QueryId.IdType == BusQueryInstanceID)
    {
        //
        // handle instance id
        //
        Buffer = AllocateItem(NonPagedPool, 5 * sizeof(WCHAR));
        if (!Buffer)
        {
            //
            // no memory
            //
            return STATUS_INSUFFICIENT_RESOURCES;
        }

        //
        // use function number
        //
        swprintf(Buffer, L"%04x", PDODeviceExtension->FunctionDescriptor->FunctionNumber);
        Irp->IoStatus.Information = (ULONG_PTR)Buffer;
        return STATUS_SUCCESS;
    }
    else if (IoStack->Parameters.QueryId.IdType == BusQueryCompatibleIDs)
    {
        //
        // handle instance id
        //
        DeviceString = &PDODeviceExtension->FunctionDescriptor->CompatibleId;
    }
    else
    {
        //
        // unsupported query
        //
        return Irp->IoStatus.Status;
    }

    //
    // sanity check
    //
    ASSERT(DeviceString != NULL);

    //
    // allocate buffer
    //
    Buffer = AllocateItem(NonPagedPool, DeviceString->Length + sizeof(WCHAR));
    if (!Buffer)
    {
        //
        // no memory
        //
        return STATUS_INSUFFICIENT_RESOURCES;
    }

    //
    // copy buffer
    //
    RtlCopyMemory(Buffer, DeviceString->Buffer, DeviceString->Length);
    Buffer[DeviceString->Length / sizeof(WCHAR)] = UNICODE_NULL;
    Irp->IoStatus.Information = (ULONG_PTR)Buffer;

    return STATUS_SUCCESS;
}
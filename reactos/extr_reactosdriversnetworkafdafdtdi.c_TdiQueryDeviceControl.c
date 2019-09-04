#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  ULONG ;
struct TYPE_4__ {int /*<<< orphan*/  Information; } ;
typedef  int /*<<< orphan*/  PVOID ;
typedef  int /*<<< orphan*/ * PULONG ;
typedef  int /*<<< orphan*/  PIRP ;
typedef  int /*<<< orphan*/  PFILE_OBJECT ;
typedef  int /*<<< orphan*/  PDEVICE_OBJECT ;
typedef  int /*<<< orphan*/  NTSTATUS ;
typedef  int /*<<< orphan*/  KEVENT ;
typedef  TYPE_1__ IO_STATUS_BLOCK ;

/* Variables and functions */
 int /*<<< orphan*/  AFD_DbgPrint (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  FALSE ; 
 int /*<<< orphan*/  IoBuildDeviceIoControlRequest (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *,TYPE_1__*) ; 
 int /*<<< orphan*/  IoGetRelatedDeviceObject (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  KeInitializeEvent (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  MIN_TRACE ; 
 int /*<<< orphan*/  NotificationEvent ; 
 int /*<<< orphan*/  STATUS_INSUFFICIENT_RESOURCES ; 
 int /*<<< orphan*/  STATUS_INVALID_PARAMETER ; 
 int /*<<< orphan*/  TdiCall (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *,TYPE_1__*) ; 

NTSTATUS TdiQueryDeviceControl(
    PFILE_OBJECT FileObject,
    ULONG IoControlCode,
    PVOID InputBuffer,
    ULONG InputBufferLength,
    PVOID OutputBuffer,
    ULONG OutputBufferLength,
    PULONG Return)
/*
 * FUNCTION: Queries a device for information
 * ARGUMENTS:
 *     FileObject         = Pointer to file object
 *     IoControlCode      = I/O control code
 *     InputBuffer        = Pointer to buffer with input data
 *     InputBufferLength  = Length of InputBuffer
 *     OutputBuffer       = Address of buffer to place output data
 *     OutputBufferLength = Length of OutputBuffer
 * RETURNS:
 *     Status of operation
 */
{
    PDEVICE_OBJECT DeviceObject;
    IO_STATUS_BLOCK Iosb;
    NTSTATUS Status;
    KEVENT Event;
    PIRP Irp;

    if (!FileObject) {
        AFD_DbgPrint(MIN_TRACE, ("Bad file object.\n"));
        return STATUS_INVALID_PARAMETER;
    }

    DeviceObject = IoGetRelatedDeviceObject(FileObject);
    if (!DeviceObject) {
        AFD_DbgPrint(MIN_TRACE, ("Bad device object.\n"));
        return STATUS_INVALID_PARAMETER;
    }

    KeInitializeEvent(&Event, NotificationEvent, FALSE);

    Irp = IoBuildDeviceIoControlRequest(IoControlCode,
                                        DeviceObject,
                                        InputBuffer,
                                        InputBufferLength,
                                        OutputBuffer,
                                        OutputBufferLength,
                                        FALSE,
                                        &Event,
                                        &Iosb);
    if (!Irp)
        return STATUS_INSUFFICIENT_RESOURCES;

    Status = TdiCall(Irp, DeviceObject, &Event, &Iosb);

    if (Return)
        *Return = Iosb.Information;

    return Status;
}
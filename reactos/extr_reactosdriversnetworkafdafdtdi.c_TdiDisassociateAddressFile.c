#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */

/* Type definitions */
typedef  int /*<<< orphan*/  PIRP ;
typedef  int /*<<< orphan*/  PFILE_OBJECT ;
typedef  int /*<<< orphan*/  PDEVICE_OBJECT ;
typedef  int /*<<< orphan*/  NTSTATUS ;
typedef  int /*<<< orphan*/  KEVENT ;
typedef  int /*<<< orphan*/  IO_STATUS_BLOCK ;

/* Variables and functions */
 int /*<<< orphan*/  AFD_DbgPrint (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  FALSE ; 
 int /*<<< orphan*/  IoGetRelatedDeviceObject (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  KeInitializeEvent (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  MAX_TRACE ; 
 int /*<<< orphan*/  MIN_TRACE ; 
 int /*<<< orphan*/  NotificationEvent ; 
 int /*<<< orphan*/  STATUS_INSUFFICIENT_RESOURCES ; 
 int /*<<< orphan*/  STATUS_INVALID_PARAMETER ; 
 int /*<<< orphan*/  TDI_DISASSOCIATE_ADDRESS ; 
 int /*<<< orphan*/  TdiBuildDisassociateAddress (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  TdiBuildInternalDeviceControlIrp (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  TdiCall (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 

NTSTATUS TdiDisassociateAddressFile(
    PFILE_OBJECT ConnectionObject)
/*
 * FUNCTION: Disassociates a connection endpoint from an address file object
 * ARGUMENTS:
 *     ConnectionObject = Connection endpoint file object
 * RETURNS:
 *     Status of operation
 */
{
    PDEVICE_OBJECT DeviceObject;
    IO_STATUS_BLOCK Iosb;
    KEVENT Event;
    PIRP Irp;

    AFD_DbgPrint(MAX_TRACE, ("Called. ConnectionObject (%p)\n", ConnectionObject));

    if (!ConnectionObject) {
        AFD_DbgPrint(MIN_TRACE, ("Bad connection object.\n"));
        return STATUS_INVALID_PARAMETER;
    }

    DeviceObject = IoGetRelatedDeviceObject(ConnectionObject);
    if (!DeviceObject) {
        AFD_DbgPrint(MIN_TRACE, ("Bad device object.\n"));
        return STATUS_INVALID_PARAMETER;
    }

    KeInitializeEvent(&Event, NotificationEvent, FALSE);

    Irp = TdiBuildInternalDeviceControlIrp(TDI_DISASSOCIATE_ADDRESS,   /* Sub function */
                                           DeviceObject,            /* Device object */
                                           ConnectionObject,        /* File object */
                                           &Event,                  /* Event */
                                           &Iosb);                  /* Status */
    if (!Irp)
        return STATUS_INSUFFICIENT_RESOURCES;

    TdiBuildDisassociateAddress(Irp,
                                DeviceObject,
                                ConnectionObject,
                                NULL,
                                NULL);

    return TdiCall(Irp, DeviceObject, &Event, &Iosb);
}
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
typedef  int /*<<< orphan*/  PVOID ;
typedef  int /*<<< orphan*/  PTDI_CONNECTION_INFORMATION ;
typedef  int /*<<< orphan*/ * PIRP ;
typedef  int /*<<< orphan*/  PIO_COMPLETION_ROUTINE ;
typedef  int /*<<< orphan*/  PFILE_OBJECT ;
typedef  int /*<<< orphan*/  PDEVICE_OBJECT ;
typedef  int /*<<< orphan*/  NTSTATUS ;

/* Variables and functions */
 int /*<<< orphan*/  AFD_DbgPrint (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  ASSERT (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  IoGetRelatedDeviceObject (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  MAX_TRACE ; 
 int /*<<< orphan*/  MIN_TRACE ; 
 int /*<<< orphan*/  STATUS_INSUFFICIENT_RESOURCES ; 
 int /*<<< orphan*/  STATUS_INVALID_PARAMETER ; 
 int /*<<< orphan*/  STATUS_PENDING ; 
 int /*<<< orphan*/  TDI_LISTEN ; 
 int /*<<< orphan*/ * TdiBuildInternalDeviceControlIrp (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  TdiBuildListen (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  TdiCall (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 

NTSTATUS TdiListen(
    PIRP *Irp,
    PFILE_OBJECT ConnectionObject,
    PTDI_CONNECTION_INFORMATION *RequestConnectionInfo,
    PTDI_CONNECTION_INFORMATION *ReturnConnectionInfo,
    PIO_COMPLETION_ROUTINE  CompletionRoutine,
    PVOID CompletionContext)
/*
 * FUNCTION: Listen on a connection endpoint for a connection request from a remote peer
 * ARGUMENTS:
 *     CompletionRoutine = Routine to be called when IRP is completed
 *     CompletionContext = Context for CompletionRoutine
 * RETURNS:
 *     Status of operation
 *     May return STATUS_PENDING
 */
{
    PDEVICE_OBJECT DeviceObject;

    AFD_DbgPrint(MAX_TRACE, ("Called\n"));

    ASSERT(*Irp == NULL);

    if (!ConnectionObject) {
        AFD_DbgPrint(MIN_TRACE, ("Bad connection object.\n"));
        return STATUS_INVALID_PARAMETER;
    }

    DeviceObject = IoGetRelatedDeviceObject(ConnectionObject);
    if (!DeviceObject) {
        AFD_DbgPrint(MIN_TRACE, ("Bad device object.\n"));
        return STATUS_INVALID_PARAMETER;
    }

    *Irp = TdiBuildInternalDeviceControlIrp(TDI_LISTEN,              /* Sub function */
                                            DeviceObject,            /* Device object */
                                            ConnectionObject,        /* File object */
                                            NULL,                    /* Event */
                                            NULL);                   /* Status */
    if (*Irp == NULL)
        return STATUS_INSUFFICIENT_RESOURCES;

    TdiBuildListen(*Irp,                   /* IRP */
                   DeviceObject,           /* Device object */
                   ConnectionObject,       /* File object */
                   CompletionRoutine,      /* Completion routine */
                   CompletionContext,      /* Completion routine context */
                   0,                      /* Flags */
                   *RequestConnectionInfo, /* Request connection information */
                   *ReturnConnectionInfo);  /* Return connection information */

    TdiCall(*Irp, DeviceObject, NULL /* Don't wait for completion */, NULL);

    return STATUS_PENDING;
}
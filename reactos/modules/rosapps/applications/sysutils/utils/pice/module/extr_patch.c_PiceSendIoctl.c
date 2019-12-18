#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  ULONG ;
struct TYPE_3__ {scalar_t__ Status; } ;
typedef  int /*<<< orphan*/  PVOID ;
typedef  int /*<<< orphan*/ * PIRP ;
typedef  int /*<<< orphan*/  PDEVICE_OBJECT ;
typedef  scalar_t__ NTSTATUS ;
typedef  int /*<<< orphan*/  KEVENT ;
typedef  TYPE_1__ IO_STATUS_BLOCK ;

/* Variables and functions */
 int /*<<< orphan*/  ASSERT (int) ; 
 int /*<<< orphan*/  DPRINT (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  Executive ; 
 int /*<<< orphan*/  FALSE ; 
 int /*<<< orphan*/ * IoBuildDeviceIoControlRequest (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *,TYPE_1__*) ; 
 scalar_t__ IoCallDriver (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  KeInitializeEvent (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ KeWaitForSingleObject (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  KernelMode ; 
 int /*<<< orphan*/  NT_SUCCESS (scalar_t__) ; 
 int /*<<< orphan*/  NotificationEvent ; 
 scalar_t__ STATUS_INSUFFICIENT_RESOURCES ; 
 scalar_t__ STATUS_PENDING ; 
 scalar_t__ STATUS_SUCCESS ; 
 int /*<<< orphan*/  TRUE ; 

NTSTATUS PiceSendIoctl(PDEVICE_OBJECT Target, ULONG Ioctl,
					PVOID InputBuffer, ULONG InputBufferLength)
{
    KEVENT          event;
    NTSTATUS        status = STATUS_SUCCESS;
    IO_STATUS_BLOCK iosb;
    PIRP            irp;

    KeInitializeEvent(&event,
                      NotificationEvent,
                      FALSE
                      );

    if (NULL == (irp = IoBuildDeviceIoControlRequest(Ioctl,
                                                     Target,
                                                     InputBuffer,
                                                     InputBufferLength,
                                                     0,
                                                     0,
                                                     TRUE,
                                                     &event,
                                                     &iosb))) {
		DPRINT((0,"PiceSendIoctl: STATUS_INSUFFICIENT_RESOURCES\n"));
        return STATUS_INSUFFICIENT_RESOURCES;
    }

    status = IoCallDriver(Target, irp);

    if (STATUS_PENDING == status) {

		status = KeWaitForSingleObject(&event,
                                       Executive,
                                       KernelMode,
                                       FALSE,
                                       NULL);

        ASSERT(STATUS_SUCCESS == status);
        status = iosb.Status;
    }
	DPRINT((0,"PiceSendIoctl: status: %d\n",NT_SUCCESS(status)));
    return status;
}
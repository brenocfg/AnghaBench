#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_20__   TYPE_7__ ;
typedef  struct TYPE_19__   TYPE_6__ ;
typedef  struct TYPE_18__   TYPE_5__ ;
typedef  struct TYPE_17__   TYPE_4__ ;
typedef  struct TYPE_16__   TYPE_3__ ;
typedef  struct TYPE_15__   TYPE_2__ ;
typedef  struct TYPE_14__   TYPE_1__ ;

/* Type definitions */
typedef  int ULONG ;
struct TYPE_20__ {int /*<<< orphan*/  Reserved; } ;
struct TYPE_14__ {int InputBufferLength; int /*<<< orphan*/  OutputBufferLength; scalar_t__ Type3InputBuffer; } ;
struct TYPE_15__ {TYPE_1__ DeviceIoControl; } ;
struct TYPE_19__ {TYPE_2__ Parameters; } ;
struct TYPE_18__ {int /*<<< orphan*/  UserBuffer; } ;
struct TYPE_17__ {int /*<<< orphan*/  FileObject; } ;
struct TYPE_16__ {int /*<<< orphan*/  KsAudioDeviceList; } ;
typedef  int /*<<< orphan*/  PVOID ;
typedef  TYPE_3__* PSYSAUDIODEVEXT ;
typedef  scalar_t__ PKSPROPERTY ;
typedef  TYPE_4__* PKSAUDIO_DEVICE_ENTRY ;
typedef  TYPE_5__* PIRP ;
typedef  TYPE_6__* PIO_STACK_LOCATION ;
typedef  int /*<<< orphan*/  NTSTATUS ;
typedef  TYPE_7__ KSP_PIN ;
typedef  int /*<<< orphan*/  KSPROPERTY ;

/* Variables and functions */
 TYPE_4__* GetListEntry (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  IOCTL_KS_PROPERTY ; 
 TYPE_6__* IoGetCurrentIrpStackLocation (TYPE_5__*) ; 
 int /*<<< orphan*/  KernelMode ; 
 int /*<<< orphan*/  KsSynchronousIoControlDevice (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int*) ; 
 int /*<<< orphan*/  STATUS_BUFFER_TOO_SMALL ; 
 int /*<<< orphan*/  STATUS_INVALID_PARAMETER ; 
 int /*<<< orphan*/  SetIrpIoStatus (TYPE_5__*,int /*<<< orphan*/ ,int) ; 

NTSTATUS
HandleSysAudioFilterPinProperties(
    PIRP Irp,
    PKSPROPERTY Property,
    PSYSAUDIODEVEXT DeviceExtension)
{
    PIO_STACK_LOCATION IoStack;
    NTSTATUS Status;
    PKSAUDIO_DEVICE_ENTRY Entry;
    ULONG BytesReturned;

    // in order to access pin properties of a sysaudio device
    // the caller must provide a KSP_PIN struct, where
    // Reserved member points to virtual device index

    IoStack = IoGetCurrentIrpStackLocation(Irp);
    if (IoStack->Parameters.DeviceIoControl.InputBufferLength < sizeof(KSP_PIN))
    {
        /* too small buffer */
        return SetIrpIoStatus(Irp, STATUS_BUFFER_TOO_SMALL, sizeof(KSPROPERTY) + sizeof(ULONG));
    }

    Entry = GetListEntry(&DeviceExtension->KsAudioDeviceList, ((KSP_PIN*)Property)->Reserved);
    if (!Entry)
    {
        /* invalid device index */
        return SetIrpIoStatus(Irp, STATUS_INVALID_PARAMETER, 0);
    }

    /* forward request to the filter implementing the property */
    Status = KsSynchronousIoControlDevice(Entry->FileObject, KernelMode, IOCTL_KS_PROPERTY,
                                             (PVOID)IoStack->Parameters.DeviceIoControl.Type3InputBuffer,
                                             IoStack->Parameters.DeviceIoControl.InputBufferLength,
                                             Irp->UserBuffer,
                                             IoStack->Parameters.DeviceIoControl.OutputBufferLength,
                                             &BytesReturned);

    return SetIrpIoStatus(Irp, Status, BytesReturned);
}
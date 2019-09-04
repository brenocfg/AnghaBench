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
typedef  int /*<<< orphan*/  UNICODE_STRING ;
typedef  int /*<<< orphan*/  PUNICODE_STRING ;
typedef  int /*<<< orphan*/  PDRIVER_OBJECT ;
typedef  int /*<<< orphan*/  PDEVICE_OBJECT ;
typedef  int /*<<< orphan*/  NTSTATUS ;

/* Variables and functions */
 int /*<<< orphan*/  DPRINT1 (char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  FALSE ; 
 int /*<<< orphan*/  FILE_DEVICE_RASACD ; 
 int /*<<< orphan*/  IoCreateDevice (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  NT_SUCCESS (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  RtlInitUnicodeString (int /*<<< orphan*/ *,char*) ; 
 int /*<<< orphan*/  STATUS_SUCCESS ; 

NTSTATUS
DriverEntry(PDRIVER_OBJECT  pDriverObject,
            PUNICODE_STRING pRegistryPath)
{
    UNICODE_STRING DeviceName;
    PDEVICE_OBJECT pDeviceObject;
    NTSTATUS Status;

    RtlInitUnicodeString(&DeviceName, L"RasAcd");

    Status = IoCreateDevice(pDriverObject,
                            0,
                            &DeviceName,
                            FILE_DEVICE_RASACD,
                            0,
                            FALSE,
                            &pDeviceObject);

    if (!NT_SUCCESS(Status))
    {
        DPRINT1("IoCreateDevice() failed (Status %lx)\n", Status);
        return Status;
    }

    return STATUS_SUCCESS;
}
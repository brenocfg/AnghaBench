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
typedef  int /*<<< orphan*/  UNICODE_STRING ;
struct TYPE_4__ {scalar_t__ Status; scalar_t__ Information; } ;
typedef  scalar_t__* PULONG ;
typedef  int /*<<< orphan*/  OBJECT_ATTRIBUTES ;
typedef  scalar_t__ NTSTATUS ;
typedef  int /*<<< orphan*/  LPVOID ;
typedef  TYPE_1__ IO_STATUS_BLOCK ;
typedef  scalar_t__ HANDLE ;
typedef  int /*<<< orphan*/  DWORD ;
typedef  scalar_t__ BOOL ;

/* Variables and functions */
 int /*<<< orphan*/  CloseHandle (scalar_t__) ; 
 scalar_t__ CreateEventW (int /*<<< orphan*/ *,scalar_t__,scalar_t__,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  ERROR_SUCCESS ; 
 scalar_t__ FALSE ; 
 int /*<<< orphan*/  FILE_ATTRIBUTE_NORMAL ; 
 int /*<<< orphan*/  FILE_OPEN_IF ; 
 int FILE_SHARE_READ ; 
 int FILE_SHARE_WRITE ; 
 int /*<<< orphan*/  FIXME (char*) ; 
 int /*<<< orphan*/  GENERIC_EXECUTE ; 
 int /*<<< orphan*/  GetLastError () ; 
 scalar_t__ INVALID_HANDLE_VALUE ; 
 int /*<<< orphan*/  InitializeObjectAttributes (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  NT_SUCCESS (scalar_t__) ; 
 scalar_t__ NtCreateFile (scalar_t__*,int /*<<< orphan*/ ,int /*<<< orphan*/ *,TYPE_1__*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 scalar_t__ NtDeviceIoControlFile (scalar_t__,scalar_t__,int /*<<< orphan*/ *,int /*<<< orphan*/ *,TYPE_1__*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,scalar_t__,int /*<<< orphan*/ ,scalar_t__) ; 
 int /*<<< orphan*/  NtWaitForSingleObject (scalar_t__,scalar_t__,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  OBJ_CASE_INSENSITIVE ; 
 int /*<<< orphan*/  RTL_CONSTANT_STRING (char*) ; 
 int /*<<< orphan*/  RtlNtStatusToDosError (scalar_t__) ; 
 scalar_t__ STATUS_PENDING ; 
 scalar_t__ STATUS_SUCCESS ; 
 scalar_t__ TRUE ; 

DWORD TCPSendIoctl(HANDLE hDevice, DWORD dwIoControlCode, LPVOID lpInBuffer, PULONG pInBufferSize, LPVOID lpOutBuffer, PULONG pOutBufferSize)
{
    BOOL Hack = FALSE;
    HANDLE Event;
    IO_STATUS_BLOCK IoStatusBlock;
    NTSTATUS Status;

    /* FIXME: We don't have a global handle opened to \Device\Ip, so open one each time
     * we need. In a future, it would be cool, just to pass it to TCPSendIoctl using the first arg
     */
    if (hDevice == INVALID_HANDLE_VALUE)
    {
        UNICODE_STRING DevName = RTL_CONSTANT_STRING(L"\\Device\\Ip");
        OBJECT_ATTRIBUTES ObjectAttributes;

        FIXME("Using the handle hack\n");
        Hack = TRUE;

        InitializeObjectAttributes(&ObjectAttributes,
                                   &DevName,
                                   OBJ_CASE_INSENSITIVE,
                                   NULL,
                                   NULL);

        Status = NtCreateFile(&hDevice, GENERIC_EXECUTE, &ObjectAttributes,
                              &IoStatusBlock, 0, FILE_ATTRIBUTE_NORMAL, FILE_SHARE_READ | FILE_SHARE_WRITE, FILE_OPEN_IF,
                              0, NULL, 0);
        if (!NT_SUCCESS(Status))
        {
          return RtlNtStatusToDosError(Status);
        }
    }

    /* Sync event */
    Event = CreateEventW(NULL, TRUE, FALSE, NULL);
    if (Event == NULL)
    {
        /* FIXME: See upper */
        if (Hack)
        {
            CloseHandle(hDevice);
        }
        return GetLastError();
    }

    /* Reinit, and call the networking stack */
    IoStatusBlock.Status = STATUS_SUCCESS;
    IoStatusBlock.Information = 0;
    Status = NtDeviceIoControlFile(hDevice, Event, NULL, NULL, &IoStatusBlock, dwIoControlCode, lpInBuffer, *pInBufferSize, lpOutBuffer, *pOutBufferSize);
    if (Status == STATUS_PENDING)
    {
        NtWaitForSingleObject(Event, FALSE, NULL);
        Status = IoStatusBlock.Status;
    }

    /* Close & return size info */
    CloseHandle(Event);
    *pOutBufferSize = IoStatusBlock.Information;

    /* FIXME: See upper */
    if (Hack)
    {
        CloseHandle(hDevice);
    }

    /* Return result */
    if (!NT_SUCCESS(Status))
    {
        return RtlNtStatusToDosError(Status);
    }

    return ERROR_SUCCESS;
}
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
struct TYPE_4__ {int /*<<< orphan*/  DriverName; } ;
typedef  TYPE_1__ SYSTEM_GDI_DRIVER_INFORMATION ;
typedef  scalar_t__ NTSTATUS ;
typedef  int /*<<< orphan*/  LPWSTR ;
typedef  int DWORD ;
typedef  int /*<<< orphan*/  BOOL ;

/* Variables and functions */
 int /*<<< orphan*/  FALSE ; 
 scalar_t__ NtSetSystemInformation (int /*<<< orphan*/ ,TYPE_1__*,int) ; 
 int /*<<< orphan*/  NtUnloadDriver (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  RtlInitUnicodeString (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int RtlNtStatusToDosError (scalar_t__) ; 
 scalar_t__ STATUS_PRIVILEGE_NOT_HELD ; 
 scalar_t__ STATUS_SUCCESS ; 
 scalar_t__ SetPrivilege (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  SystemLoadGdiDriverInformation ; 
 int /*<<< orphan*/  TRUE ; 
 int /*<<< orphan*/  ZeroMemory (TYPE_1__*,int) ; 
 int /*<<< orphan*/  wprintf (char*,...) ; 

BOOL
LoadVia_SystemLoadGdiDriverInformation(LPWSTR lpDriverPath)
{
    NTSTATUS Status;
    SYSTEM_GDI_DRIVER_INFORMATION Buffer;
    DWORD bufSize;

    bufSize = sizeof(SYSTEM_GDI_DRIVER_INFORMATION);

    ZeroMemory(&Buffer, bufSize);
    RtlInitUnicodeString(&Buffer.DriverName, lpDriverPath);

    if (SetPrivilege(TRUE))
    {
        Status = NtSetSystemInformation(SystemLoadGdiDriverInformation,
                                        &Buffer,
                                        bufSize);
        if (Status == STATUS_PRIVILEGE_NOT_HELD)
        {
            wprintf(L"SystemLoadGdiDriverInformation can only be used in kmode.\n");
        }
        else if (Status == STATUS_SUCCESS)
        {
            wprintf(L"SystemLoadGdiDriverInformation incorrectly loaded the driver\n");
            NtUnloadDriver(&Buffer.DriverName);

            return TRUE;
        }
        else
        {
            DWORD err = RtlNtStatusToDosError(Status);
            wprintf(L"LoadVia_SystemLoadGdiDriverInformation failed [%lu]\n", err);
        }

        SetPrivilege(FALSE);
    }

    return FALSE;
}
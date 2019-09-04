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
typedef  scalar_t__ NTSTATUS ;
typedef  int /*<<< orphan*/  LPWSTR ;
typedef  int DWORD ;
typedef  int /*<<< orphan*/  BOOL ;

/* Variables and functions */
 int /*<<< orphan*/  FALSE ; 
 scalar_t__ NtSetSystemInformation (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  NtUnloadDriver (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  RtlInitUnicodeString (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int RtlNtStatusToDosError (scalar_t__) ; 
 scalar_t__ STATUS_PRIVILEGE_NOT_HELD ; 
 scalar_t__ STATUS_SUCCESS ; 
 scalar_t__ SetPrivilege (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  SystemExtendServiceTableInformation ; 
 int /*<<< orphan*/  TRUE ; 
 int /*<<< orphan*/  wprintf (char*,...) ; 

BOOL
LoadVia_SystemExtendServiceTableInformation(LPWSTR lpDriverPath)
{
    NTSTATUS Status;
    UNICODE_STRING Buffer;
    DWORD bufSize;

    RtlInitUnicodeString(&Buffer, lpDriverPath);
    bufSize = sizeof(UNICODE_STRING);

    if (SetPrivilege(TRUE))
    {
        Status = NtSetSystemInformation(SystemExtendServiceTableInformation,
                                        &Buffer,
                                        bufSize);
        if (Status == STATUS_PRIVILEGE_NOT_HELD)
        {
            wprintf(L"SystemExtendServiceTableInformation can only be used in kmode.\n");
        }
        else if (Status == STATUS_SUCCESS)
        {
            wprintf(L"SystemExtendServiceTableInformation incorrectly loaded the driver\n");
            NtUnloadDriver(&Buffer);

            return TRUE;
        }
        else
        {
            DWORD err = RtlNtStatusToDosError(Status);
            wprintf(L"LoadVia_SystemExtendServiceTableInformation failed [%lu] - 0x%x\n", err, Status);
        }

        SetPrivilege(FALSE);
    }

    return FALSE;
}
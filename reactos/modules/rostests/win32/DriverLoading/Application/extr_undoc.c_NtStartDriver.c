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
typedef  int /*<<< orphan*/  WCHAR ;
typedef  int /*<<< orphan*/  UNICODE_STRING ;
typedef  scalar_t__ NTSTATUS ;
typedef  int /*<<< orphan*/  LPCWSTR ;
typedef  int /*<<< orphan*/  DWORD ;
typedef  int BOOL ;

/* Variables and functions */
 int /*<<< orphan*/  FALSE ; 
 int MAX_PATH ; 
 scalar_t__ NtLoadDriver (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  RtlInitUnicodeString (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  RtlNtStatusToDosError (scalar_t__) ; 
 scalar_t__ STATUS_SUCCESS ; 
 scalar_t__ SetPrivilege (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  TRUE ; 
 int /*<<< orphan*/  wcscat (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  wcscpy (int /*<<< orphan*/ *,char*) ; 
 int /*<<< orphan*/  wprintf (char*,int /*<<< orphan*/ ) ; 

BOOL
NtStartDriver(LPCWSTR lpService)
{
    WCHAR szDriverPath[MAX_PATH];
    UNICODE_STRING DriverPath;
    NTSTATUS Status = -1;

    wcscpy(szDriverPath,
           L"\\Registry\\Machine\\System\\CurrentControlSet\\Services\\");
    wcscat(szDriverPath,
           lpService);

    RtlInitUnicodeString(&DriverPath,
                         szDriverPath);

    if (SetPrivilege(TRUE))
    {
        Status = NtLoadDriver(&DriverPath);
        if (Status != STATUS_SUCCESS)
        {
            DWORD err = RtlNtStatusToDosError(Status);
            wprintf(L"NtUnloadDriver failed [%lu]\n", err);
        }

        SetPrivilege(FALSE);
    }

    return (Status == STATUS_SUCCESS);
}
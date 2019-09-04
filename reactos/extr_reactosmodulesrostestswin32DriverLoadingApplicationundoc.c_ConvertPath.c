#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_13__   TYPE_2__ ;
typedef  struct TYPE_12__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  WCHAR ;
struct TYPE_12__ {int Length; int /*<<< orphan*/  Buffer; } ;
struct TYPE_13__ {TYPE_1__ Name; } ;
typedef  TYPE_2__* POBJECT_NAME_INFORMATION ;
typedef  scalar_t__ NTSTATUS ;
typedef  TYPE_2__* LPWSTR ;
typedef  scalar_t__ LPCWSTR ;
typedef  scalar_t__ HANDLE ;
typedef  int DWORD ;
typedef  int /*<<< orphan*/  BOOL ;

/* Variables and functions */
 scalar_t__ CreateFileW (TYPE_2__*,int,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 char* DRIVER_NAME ; 
 int /*<<< orphan*/  FALSE ; 
 int /*<<< orphan*/  FILE_ATTRIBUTE_NORMAL ; 
 int GENERIC_READ ; 
 int GENERIC_WRITE ; 
 int GetLastError () ; 
 int GetLongPathNameW (scalar_t__,TYPE_2__*,int) ; 
 int /*<<< orphan*/  GetProcessHeap () ; 
 TYPE_2__* HeapAlloc (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  HeapFree (int /*<<< orphan*/ ,int /*<<< orphan*/ ,TYPE_2__*) ; 
 scalar_t__ INVALID_HANDLE_VALUE ; 
 int MAX_PATH ; 
 scalar_t__ NtQueryObject (scalar_t__,int /*<<< orphan*/ ,TYPE_2__*,int,int*) ; 
 int /*<<< orphan*/  OPEN_EXISTING ; 
 int /*<<< orphan*/  ObjectNameInformation ; 
 scalar_t__ STATUS_SUCCESS ; 
 int /*<<< orphan*/  TRUE ; 
 TYPE_2__ UNICODE_NULL ; 
 int /*<<< orphan*/  wcsncpy (TYPE_2__*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  wprintf (char*,int,char*) ; 

BOOL
ConvertPath(LPCWSTR lpPath,
            LPWSTR lpDevice)
{
    LPWSTR lpFullPath = NULL;
    DWORD size;

    if (lpPath)
    {
        size = GetLongPathNameW(lpPath,
                                0,
                                0);
        if (!size)
            return FALSE;

        size = (size + 1) * sizeof(WCHAR);

        lpFullPath = HeapAlloc(GetProcessHeap(),
                               0,
                               size);
        if (!lpFullPath)
            return FALSE;

        if (GetLongPathNameW(lpPath,
                             lpFullPath,
                             size))
        {
            HANDLE hDevice;
            POBJECT_NAME_INFORMATION pObjName;
            NTSTATUS Status;
            DWORD len;

            hDevice = CreateFileW(lpFullPath,
                                  GENERIC_READ | GENERIC_WRITE,
                                  0,
                                  NULL,
                                  OPEN_EXISTING,
                                  FILE_ATTRIBUTE_NORMAL,
                                  NULL);

            HeapFree(GetProcessHeap(), 0, lpFullPath);

            if(hDevice == INVALID_HANDLE_VALUE)
            {
                wprintf(L"[%x] Failed to open %s\n", GetLastError(), DRIVER_NAME);
                return FALSE;
            }

            size = MAX_PATH * sizeof(WCHAR);
            pObjName = HeapAlloc(GetProcessHeap(), 0, size);
            if (!pObjName)
                return FALSE;

            Status = NtQueryObject(hDevice,
                                   ObjectNameInformation,
                                   pObjName,
                                   size,
                                   &size);
            if (Status == STATUS_SUCCESS)
            {
                len = pObjName->Name.Length / sizeof(WCHAR);
                wcsncpy(lpDevice, pObjName->Name.Buffer, len);
                lpDevice[len] = UNICODE_NULL;

                HeapFree(GetProcessHeap(), 0, pObjName);

                return TRUE;
            }

            HeapFree(GetProcessHeap(), 0, pObjName);
        }
    }

    return FALSE;
}
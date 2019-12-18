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
typedef  char* LPWSTR ;
typedef  char* LPCWSTR ;
typedef  scalar_t__ LONG ;
typedef  scalar_t__ HKEY ;
typedef  int DWORD ;
typedef  scalar_t__ BOOL ;

/* Variables and functions */
 scalar_t__ ERROR_SUCCESS ; 
 scalar_t__ FALSE ; 
 int /*<<< orphan*/  GetProcessHeap () ; 
 scalar_t__ HKEY_LOCAL_MACHINE ; 
 scalar_t__ HeapAlloc (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  HeapFree (int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*) ; 
 int KEY_CREATE_SUB_KEY ; 
 int KEY_ENUMERATE_SUB_KEYS ; 
 int KEY_QUERY_VALUE ; 
 int /*<<< orphan*/  RegCloseKey (scalar_t__) ; 
 int /*<<< orphan*/  RegDeleteKeyW (scalar_t__,char*) ; 
 scalar_t__ RegEnumKeyExW (scalar_t__,int /*<<< orphan*/ ,char*,int*,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  RegFlushKey (scalar_t__) ; 
 scalar_t__ RegOpenKeyExW (scalar_t__,char*,int /*<<< orphan*/ ,int,scalar_t__*) ; 
 scalar_t__ RegQueryInfoKeyW (scalar_t__,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int*,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 scalar_t__ TRUE ; 
 int /*<<< orphan*/  wprintf (char*,...) ; 

BOOL RemoveEventLog(LPCWSTR EventLogName)
{
    BOOL Success = FALSE;
    LONG lRet;
    HKEY hKey, hEventKey;
    DWORD MaxKeyNameLen, KeyNameLen;
    LPWSTR Buf = NULL;

    wprintf(L"Deleting log %s...", EventLogName);

    lRet = RegOpenKeyExW(HKEY_LOCAL_MACHINE,
                         L"SYSTEM\\CurrentControlSet\\Services\\Eventlog",
                         0, KEY_CREATE_SUB_KEY,
                         &hKey);
    if (lRet != ERROR_SUCCESS)
        goto Quit;

    lRet = RegOpenKeyExW(hKey,
                         EventLogName,
                         0, KEY_ENUMERATE_SUB_KEYS | KEY_QUERY_VALUE,
                         &hEventKey);
    if (lRet != ERROR_SUCCESS)
        goto Quit;

    lRet = RegQueryInfoKeyW(hEventKey,
                            NULL, NULL, NULL, NULL,
                            &MaxKeyNameLen,
                            NULL, NULL, NULL, NULL, NULL, NULL);
    if (lRet != ERROR_SUCCESS)
        goto Quit;

    MaxKeyNameLen++;

    Buf = (LPWSTR)HeapAlloc(GetProcessHeap(), 0, MaxKeyNameLen * sizeof(WCHAR));
    if (!Buf)
        goto Quit;

    KeyNameLen = MaxKeyNameLen;
    while (RegEnumKeyExW(hEventKey,
                         0,
                         Buf,
                         &KeyNameLen,
                         NULL, NULL, NULL, NULL) == ERROR_SUCCESS)
    {
        RegDeleteKeyW(hEventKey, Buf);
        KeyNameLen = MaxKeyNameLen;
    }

    RegFlushKey(hEventKey);

    HeapFree(GetProcessHeap(), 0, Buf);

    Success = TRUE;

Quit:
    if (Success)
    {
        RegCloseKey(hEventKey);
        RegDeleteKeyW(hKey, EventLogName);

        wprintf(L"Success\n");
    }
    else
    {
        if (hEventKey)
            RegCloseKey(hEventKey);

        wprintf(L"Failure\n");
    }

    if (hKey)
        RegCloseKey(hKey);

    return Success;
}
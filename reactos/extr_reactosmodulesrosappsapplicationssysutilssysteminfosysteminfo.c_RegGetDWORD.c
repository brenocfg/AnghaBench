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
typedef  scalar_t__* LPDWORD ;
typedef  char* LPCWSTR ;
typedef  int /*<<< orphan*/  LPBYTE ;
typedef  int /*<<< orphan*/  HKEY ;
typedef  scalar_t__ DWORD ;
typedef  int /*<<< orphan*/  BOOL ;

/* Variables and functions */
 scalar_t__ ERROR_SUCCESS ; 
 int /*<<< orphan*/  FALSE ; 
 int /*<<< orphan*/  GetLastError () ; 
 int /*<<< orphan*/  KEY_QUERY_VALUE ; 
 scalar_t__ REG_DWORD ; 
 int /*<<< orphan*/  RegCloseKey (int /*<<< orphan*/ ) ; 
 scalar_t__ RegOpenKeyExW (int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 scalar_t__ RegQueryValueExW (int /*<<< orphan*/ ,char*,int /*<<< orphan*/ *,scalar_t__*,int /*<<< orphan*/ ,scalar_t__*) ; 
 int /*<<< orphan*/  TRUE ; 
 int /*<<< orphan*/  wprintf (char*,char*,int /*<<< orphan*/ ,...) ; 

__attribute__((used)) static
BOOL
RegGetDWORD(HKEY hKey, LPCWSTR lpSubKey, LPCWSTR lpValueName, LPDWORD lpData)
{
    DWORD dwBytes = sizeof(*lpData), dwType;
    BOOL bRet = TRUE;

    /* If SubKey is specified open it */
    if (lpSubKey && RegOpenKeyExW(hKey,
                                 lpSubKey,
                                 0,
                                 KEY_QUERY_VALUE,
                                 &hKey) != ERROR_SUCCESS)
    {
        wprintf(L"Warning! Cannot open %s. Last error: %lu.\n", lpSubKey, GetLastError());
        return FALSE;
    }

    /* Query registry value and check its type */
    if (RegQueryValueExW(hKey,
                         lpValueName,
                         NULL,
                         &dwType,
                         (LPBYTE)lpData,
                         &dwBytes) != ERROR_SUCCESS || dwType != REG_DWORD)
    {
        wprintf(L"Warning! Cannot query %s. Last err: %lu, type: %lu\n", lpValueName, GetLastError(), dwType);
        *lpData = 0;
        bRet = FALSE;
    }

    /* Close key if we opened it */
    if (lpSubKey)
        RegCloseKey(hKey);

    return bRet;
}
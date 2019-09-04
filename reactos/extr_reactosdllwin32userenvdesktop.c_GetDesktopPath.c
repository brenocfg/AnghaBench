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
typedef  int /*<<< orphan*/  LPWSTR ;
typedef  int /*<<< orphan*/  LPBYTE ;
typedef  scalar_t__ LONG ;
typedef  int /*<<< orphan*/  HKEY ;
typedef  scalar_t__ DWORD ;
typedef  scalar_t__ BOOL ;

/* Variables and functions */
 int /*<<< orphan*/  DPRINT (char*) ; 
 int /*<<< orphan*/  DPRINT1 (char*) ; 
 scalar_t__ ERROR_SUCCESS ; 
 int /*<<< orphan*/  ExpandEnvironmentStringsW (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int) ; 
 scalar_t__ FALSE ; 
 int /*<<< orphan*/  HKEY_CURRENT_USER ; 
 int /*<<< orphan*/  KEY_QUERY_VALUE ; 
 int MAX_PATH ; 
 scalar_t__ REG_EXPAND_SZ ; 
 int /*<<< orphan*/  RegCloseKey (int /*<<< orphan*/ ) ; 
 scalar_t__ RegOpenKeyExW (int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 scalar_t__ RegQueryValueExW (int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ,scalar_t__*,int /*<<< orphan*/ ,scalar_t__*) ; 
 int /*<<< orphan*/  SetLastError (scalar_t__) ; 
 scalar_t__ TRUE ; 
 int /*<<< orphan*/  wcscpy (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 

__attribute__((used)) static
BOOL
GetDesktopPath(BOOL bCommonPath,
               LPWSTR lpDesktopPath)
{
    WCHAR szPath[MAX_PATH];
    DWORD dwLength;
    DWORD dwType;
    HKEY hKey;
    LONG Error;

    DPRINT("GetDesktopPath() called\n");

    Error = RegOpenKeyExW(HKEY_CURRENT_USER,
                          L"Software\\Microsoft\\Windows\\CurrentVersion\\Explorer\\User Shell Folders",
                          0,
                          KEY_QUERY_VALUE,
                          &hKey);
    if (Error != ERROR_SUCCESS)
    {
        DPRINT1("RegOpenKeyExW() failed\n");
        SetLastError((DWORD)Error);
        return FALSE;
    }

    dwLength = MAX_PATH * sizeof(WCHAR);
    Error = RegQueryValueExW(hKey,
                             bCommonPath ? L"Common Desktop" : L"Desktop",
                             0,
                             &dwType,
                             (LPBYTE)szPath,
                             &dwLength);
    if (Error != ERROR_SUCCESS)
    {
        DPRINT1("RegQueryValueExW() failed\n");
        RegCloseKey(hKey);
        SetLastError((DWORD)Error);
        return FALSE;
    }

    RegCloseKey(hKey);

    if (dwType == REG_EXPAND_SZ)
    {
        ExpandEnvironmentStringsW(szPath,
                                  lpDesktopPath,
                                  MAX_PATH);
    }
    else
    {
        wcscpy(lpDesktopPath, szPath);
    }

    DPRINT("GetDesktopPath() done\n");

    return TRUE;
}
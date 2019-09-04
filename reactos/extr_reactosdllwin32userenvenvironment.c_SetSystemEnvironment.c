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
typedef  int /*<<< orphan*/  PWSTR ;
typedef  int /*<<< orphan*/ * LPWSTR ;
typedef  int /*<<< orphan*/  LPBYTE ;
typedef  scalar_t__ LONG ;
typedef  int /*<<< orphan*/  HKEY ;
typedef  scalar_t__ DWORD ;
typedef  int /*<<< orphan*/  BOOL ;

/* Variables and functions */
 int /*<<< orphan*/  DPRINT1 (char*,scalar_t__) ; 
 scalar_t__ ERROR_SUCCESS ; 
 int /*<<< orphan*/  FALSE ; 
 int /*<<< orphan*/  HKEY_LOCAL_MACHINE ; 
 int /*<<< orphan*/  KEY_QUERY_VALUE ; 
 int /*<<< orphan*/  LPTR ; 
 int /*<<< orphan*/ * LocalAlloc (int /*<<< orphan*/ ,scalar_t__) ; 
 int /*<<< orphan*/  LocalFree (int /*<<< orphan*/ *) ; 
 scalar_t__ REG_EXPAND_SZ ; 
 int /*<<< orphan*/  RegCloseKey (int /*<<< orphan*/ ) ; 
 scalar_t__ RegEnumValueW (int /*<<< orphan*/ ,scalar_t__,int /*<<< orphan*/ *,scalar_t__*,int /*<<< orphan*/ *,scalar_t__*,int /*<<< orphan*/ ,scalar_t__*) ; 
 scalar_t__ RegOpenKeyExW (int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 scalar_t__ RegQueryInfoKey (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *,scalar_t__*,scalar_t__*,scalar_t__*,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  SetUserEnvironmentVariable (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  TRUE ; 

__attribute__((used)) static
BOOL
SetSystemEnvironment(PWSTR* Environment)
{
    LONG Error;
    HKEY hEnvKey;
    DWORD dwValues;
    DWORD dwMaxValueNameLength;
    DWORD dwMaxValueDataLength;
    DWORD dwValueNameLength;
    DWORD dwValueDataLength;
    DWORD dwType;
    DWORD i;
    LPWSTR lpValueName;
    LPWSTR lpValueData;

    Error = RegOpenKeyExW(HKEY_LOCAL_MACHINE,
                          L"SYSTEM\\CurrentControlSet\\Control\\Session Manager\\Environment",
                          0,
                          KEY_QUERY_VALUE,
                          &hEnvKey);
    if (Error != ERROR_SUCCESS)
    {
        DPRINT1("RegOpenKeyExW() failed (Error %ld)\n", Error);
        return FALSE;
    }

    Error = RegQueryInfoKey(hEnvKey,
                            NULL,
                            NULL,
                            NULL,
                            NULL,
                            NULL,
                            NULL,
                            &dwValues,
                            &dwMaxValueNameLength,
                            &dwMaxValueDataLength,
                            NULL,
                            NULL);
    if (Error != ERROR_SUCCESS)
    {
        DPRINT1("RegQueryInforKey() failed (Error %ld)\n", Error);
        RegCloseKey(hEnvKey);
        return FALSE;
    }

    if (dwValues == 0)
    {
        RegCloseKey(hEnvKey);
        return TRUE;
    }

    /* Allocate buffers */
    dwMaxValueNameLength++;
    lpValueName = LocalAlloc(LPTR, dwMaxValueNameLength * sizeof(WCHAR));
    if (lpValueName == NULL)
    {
        RegCloseKey(hEnvKey);
        return FALSE;
    }

    lpValueData = LocalAlloc(LPTR, dwMaxValueDataLength);
    if (lpValueData == NULL)
    {
        LocalFree(lpValueName);
        RegCloseKey(hEnvKey);
        return FALSE;
    }

    /* Enumerate values */
    for (i = 0; i < dwValues; i++)
    {
        dwValueNameLength = dwMaxValueNameLength;
        dwValueDataLength = dwMaxValueDataLength;

        Error = RegEnumValueW(hEnvKey,
                              i,
                              lpValueName,
                              &dwValueNameLength,
                              NULL,
                              &dwType,
                              (LPBYTE)lpValueData,
                              &dwValueDataLength);
        if (Error == ERROR_SUCCESS)
        {
            /* Set environment variable */
            SetUserEnvironmentVariable(Environment,
                                       lpValueName,
                                       lpValueData,
                                       (dwType == REG_EXPAND_SZ));
        }
        else
        {
            LocalFree(lpValueData);
            LocalFree(lpValueName);
            RegCloseKey(hEnvKey);

            return FALSE;
        }
    }

    LocalFree(lpValueData);
    LocalFree(lpValueName);
    RegCloseKey(hEnvKey);

    return TRUE;
}
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
typedef  int /*<<< orphan*/  szNameBuf ;
typedef  int /*<<< orphan*/  REGSAM ;
typedef  scalar_t__ LSTATUS ;
typedef  char* LPCSTR ;
typedef  scalar_t__ LONG ;
typedef  int /*<<< orphan*/  HKEY ;
typedef  int DWORD ;

/* Variables and functions */
 scalar_t__ ERROR_NOT_ENOUGH_MEMORY ; 
 int /*<<< orphan*/  GetProcessHeap () ; 
 char* HeapAlloc (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  HeapFree (int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*) ; 
 int MAX_PATH ; 
 int /*<<< orphan*/  RegCloseKey (int /*<<< orphan*/ ) ; 
 scalar_t__ RegDeleteKeyA (int /*<<< orphan*/ ,char*) ; 
 scalar_t__ RegDeleteValueA (int /*<<< orphan*/ ,char*) ; 
 scalar_t__ RegEnumKeyExA (int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*,int*,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 scalar_t__ RegEnumValueA (int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*,int*,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 scalar_t__ RegOpenKeyExA (int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 scalar_t__ RegQueryInfoKeyA (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int*,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int*,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 scalar_t__ TRUE ; 
 int max (int,int) ; 
 scalar_t__ pRegDeleteKeyExA (int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static LSTATUS action_RegDeleteTreeA(HKEY hKey, LPCSTR lpszSubKey, REGSAM access)
{
    LONG ret;
    DWORD dwMaxSubkeyLen, dwMaxValueLen;
    DWORD dwMaxLen, dwSize;
    char szNameBuf[MAX_PATH], *lpszName = szNameBuf;
    HKEY hSubKey = hKey;

    if(lpszSubKey)
    {
        ret = RegOpenKeyExA(hKey, lpszSubKey, 0, access, &hSubKey);
        if (ret) return ret;
    }

    ret = RegQueryInfoKeyA(hSubKey, NULL, NULL, NULL, NULL,
            &dwMaxSubkeyLen, NULL, NULL, &dwMaxValueLen, NULL, NULL, NULL);
    if (ret) goto cleanup;

    dwMaxSubkeyLen++;
    dwMaxValueLen++;
    dwMaxLen = max(dwMaxSubkeyLen, dwMaxValueLen);
    if (dwMaxLen > sizeof(szNameBuf))
    {
        /* Name too big: alloc a buffer for it */
        if (!(lpszName = HeapAlloc( GetProcessHeap(), 0, dwMaxLen)))
        {
            ret = ERROR_NOT_ENOUGH_MEMORY;
            goto cleanup;
        }
    }

    /* Recursively delete all the subkeys */
    while (TRUE)
    {
        dwSize = dwMaxLen;
        if (RegEnumKeyExA(hSubKey, 0, lpszName, &dwSize, NULL,
                          NULL, NULL, NULL)) break;

        ret = action_RegDeleteTreeA(hSubKey, lpszName, access);
        if (ret) goto cleanup;
    }

    if (lpszSubKey)
    {
        if (pRegDeleteKeyExA)
            ret = pRegDeleteKeyExA(hKey, lpszSubKey, access, 0);
        else
            ret = RegDeleteKeyA(hKey, lpszSubKey);
    }
    else
        while (TRUE)
        {
            dwSize = dwMaxLen;
            if (RegEnumValueA(hKey, 0, lpszName, &dwSize,
                  NULL, NULL, NULL, NULL)) break;

            ret = RegDeleteValueA(hKey, lpszName);
            if (ret) goto cleanup;
        }

cleanup:
    if (lpszName != szNameBuf)
        HeapFree(GetProcessHeap(), 0, lpszName);
    if(lpszSubKey)
        RegCloseKey(hSubKey);
    return ret;
}
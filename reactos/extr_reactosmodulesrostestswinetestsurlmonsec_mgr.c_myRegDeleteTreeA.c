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
typedef  int /*<<< orphan*/ * LPCSTR ;
typedef  scalar_t__ LONG ;
typedef  int /*<<< orphan*/  HKEY ;
typedef  int DWORD ;
typedef  int /*<<< orphan*/  CHAR ;

/* Variables and functions */
 int ARRAY_SIZE (int /*<<< orphan*/ *) ; 
 scalar_t__ ERROR_NOT_ENOUGH_MEMORY ; 
 int /*<<< orphan*/  GetProcessHeap () ; 
 int /*<<< orphan*/ * HeapAlloc (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  KEY_READ ; 
 int MAX_PATH ; 
 int /*<<< orphan*/  RegCloseKey (int /*<<< orphan*/ ) ; 
 scalar_t__ RegDeleteKeyA (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 scalar_t__ RegDeleteValueA (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 scalar_t__ RegEnumKeyExA (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int*,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 scalar_t__ RegEnumValueA (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int*,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 scalar_t__ RegOpenKeyExA (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 scalar_t__ RegQueryInfoKeyA (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int*,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int*,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 scalar_t__ TRUE ; 
 int /*<<< orphan*/  heap_free (int /*<<< orphan*/ *) ; 
 int max (int,int) ; 

__attribute__((used)) static LONG myRegDeleteTreeA(HKEY hKey, LPCSTR lpszSubKey)
{
    LONG ret;
    DWORD dwMaxSubkeyLen, dwMaxValueLen;
    DWORD dwMaxLen, dwSize;
    CHAR szNameBuf[MAX_PATH], *lpszName = szNameBuf;
    HKEY hSubKey = hKey;

    if(lpszSubKey)
    {
        ret = RegOpenKeyExA(hKey, lpszSubKey, 0, KEY_READ, &hSubKey);
        if (ret) return ret;
    }

    /* Get highest length for keys, values */
    ret = RegQueryInfoKeyA(hSubKey, NULL, NULL, NULL, NULL,
            &dwMaxSubkeyLen, NULL, NULL, &dwMaxValueLen, NULL, NULL, NULL);
    if (ret) goto cleanup;

    dwMaxSubkeyLen++;
    dwMaxValueLen++;
    dwMaxLen = max(dwMaxSubkeyLen, dwMaxValueLen);
    if (dwMaxLen > ARRAY_SIZE(szNameBuf))
    {
        /* Name too big: alloc a buffer for it */
        if (!(lpszName = HeapAlloc( GetProcessHeap(), 0, dwMaxLen*sizeof(CHAR))))
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

        ret = myRegDeleteTreeA(hSubKey, lpszName);
        if (ret) goto cleanup;
    }

    if (lpszSubKey)
        ret = RegDeleteKeyA(hKey, lpszSubKey);
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
    /* Free buffer if allocated */
    if (lpszName != szNameBuf)
        heap_free(lpszName);
    if(lpszSubKey)
        RegCloseKey(hSubKey);
    return ret;
}
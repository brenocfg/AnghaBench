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
typedef  int* LPWSTR ;
typedef  char* LPCWSTR ;
typedef  int /*<<< orphan*/  LPBYTE ;
typedef  int /*<<< orphan*/  HKEY ;
typedef  int DWORD ;

/* Variables and functions */
 scalar_t__ ERROR_SUCCESS ; 
 int /*<<< orphan*/  GetLastError () ; 
 int /*<<< orphan*/  KEY_QUERY_VALUE ; 
 int REG_MULTI_SZ ; 
 int REG_SZ ; 
 int /*<<< orphan*/  RegCloseKey (int /*<<< orphan*/ ) ; 
 scalar_t__ RegOpenKeyExW (int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 scalar_t__ RegQueryValueExW (int /*<<< orphan*/ ,char*,int /*<<< orphan*/ *,int*,int /*<<< orphan*/ ,int*) ; 
 size_t min (int,unsigned int) ; 
 int /*<<< orphan*/  wcscpy (int*,char*) ; 
 int /*<<< orphan*/  wprintf (char*,char*,int /*<<< orphan*/ ,...) ; 

__attribute__((used)) static
unsigned
RegGetSZ(HKEY hKey, LPCWSTR lpSubKey, LPCWSTR lpValueName, LPWSTR lpBuf, DWORD cchBuf)
{
    DWORD dwBytes = cchBuf*sizeof(WCHAR), dwType = 0;
    unsigned cChars;

    /* If SubKey is specified open it */
    if (lpSubKey && RegOpenKeyExW(hKey,
                                  lpSubKey,
                                  0,
                                  KEY_QUERY_VALUE,
                                  &hKey) != ERROR_SUCCESS)
    {
        wprintf(L"Warning! Cannot open %s. Last error: %lu.\n", lpSubKey, GetLastError());
        return 0;
    }

    /* Query registry value and check its type */
    if (RegQueryValueExW(hKey,
                         lpValueName,
                         NULL,
                         &dwType,
                         (LPBYTE)lpBuf,
                         &dwBytes) != ERROR_SUCCESS || (dwType != REG_SZ && dwType != REG_MULTI_SZ))
    {
        wprintf(L"Warning! Cannot query %s. Last error: %lu, type: %lu.\n", lpValueName, GetLastError(), dwType);
        dwBytes = 0;
    }
    else if (dwBytes == 0)
    {
        wcscpy(lpBuf, L"N/A");
        dwBytes = 6;
    }

    /* Close key if we opened it */
    if (lpSubKey)
        RegCloseKey(hKey);

    cChars = dwBytes/sizeof(WCHAR);

    /* NULL-terminate string */
    lpBuf[min(cchBuf-1, cChars)] = L'\0';
    
    /* Don't count NULL characters */
    while(cChars && !lpBuf[cChars-1])
        --cChars;

    return cChars;
}
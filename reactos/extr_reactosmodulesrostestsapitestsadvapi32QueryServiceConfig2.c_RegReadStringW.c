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
typedef  int /*<<< orphan*/ * LPWSTR ;
typedef  int /*<<< orphan*/ * LPBYTE ;
typedef  int /*<<< orphan*/  HKEY ;
typedef  scalar_t__ DWORD ;

/* Variables and functions */
 scalar_t__ ERROR_NOT_ENOUGH_MEMORY ; 
 scalar_t__ ERROR_SUCCESS ; 
 int /*<<< orphan*/  GetProcessHeap () ; 
 int /*<<< orphan*/ * HeapAlloc (int /*<<< orphan*/ ,int /*<<< orphan*/ ,scalar_t__) ; 
 int /*<<< orphan*/  HeapFree (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 scalar_t__ RegQueryValueExW (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ,scalar_t__*,int /*<<< orphan*/ *,scalar_t__*) ; 

__attribute__((used)) static DWORD
RegReadStringW(HKEY   hKey,
               LPWSTR lpValueName,
               LPWSTR *lpValue)
{
    DWORD dwError;
    DWORD dwSize;
    DWORD dwType;

    *lpValue = NULL;

    dwSize  = 0;
    dwError = RegQueryValueExW(hKey,
                               lpValueName,
                               0,
                               &dwType,
                               NULL,
                               &dwSize);
    if (dwError != ERROR_SUCCESS)
        return dwError;

    *lpValue = HeapAlloc(GetProcessHeap(), 0, dwSize);
    if (*lpValue == NULL)
        return ERROR_NOT_ENOUGH_MEMORY;

    dwError = RegQueryValueExW(hKey,
                               lpValueName,
                               0,
                               &dwType,
                               (LPBYTE)*lpValue,
                               &dwSize);
    if (dwError != ERROR_SUCCESS)
    {
        HeapFree(GetProcessHeap(), 0, *lpValue);
        *lpValue = NULL;
    }

    return dwError;
}
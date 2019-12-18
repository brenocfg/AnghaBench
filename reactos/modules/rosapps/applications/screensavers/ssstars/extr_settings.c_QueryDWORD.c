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
typedef  int /*<<< orphan*/  LPCTSTR ;
typedef  int /*<<< orphan*/  LPBYTE ;
typedef  scalar_t__ LONG ;
typedef  int /*<<< orphan*/  HKEY ;
typedef  scalar_t__ DWORD ;

/* Variables and functions */
 scalar_t__ ERROR_SUCCESS ; 
 scalar_t__ REG_DWORD ; 
 scalar_t__ RegQueryValueEx (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *,scalar_t__*,int /*<<< orphan*/ ,scalar_t__*) ; 

__attribute__((used)) static DWORD QueryDWORD(HKEY hKey, LPCTSTR pszValueName, DWORD Default)
{
    DWORD dwData, dwType, cbData;
    LONG  lRes;

    dwType = REG_DWORD;
    cbData = sizeof(DWORD);

    lRes = RegQueryValueEx(
                hKey,
                pszValueName,
                NULL,
                &dwType,
                (LPBYTE)&dwData,
                &cbData);

    if (lRes != ERROR_SUCCESS || dwType != REG_DWORD)
        return Default;

    return dwData;
}
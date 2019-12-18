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
typedef  int /*<<< orphan*/ * PWSTR ;
typedef  int /*<<< orphan*/  PCWSTR ;
typedef  int DWORD ;

/* Variables and functions */
 int /*<<< orphan*/  CopyMemory (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/ * DllAllocSplMem (int) ; 
 int /*<<< orphan*/  ERR (char*,int /*<<< orphan*/ ) ; 
 int ERROR_NOT_ENOUGH_MEMORY ; 
 int ERROR_SUCCESS ; 
 int /*<<< orphan*/  GetLastError () ; 
 int cchNonspooledPrefix ; 
 int wcslen (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  wszNonspooledPrefix ; 

__attribute__((used)) static __inline DWORD
_GetNonspooledPortName(PCWSTR pwszPortNameWithoutColon, PWSTR* ppwszNonspooledPortName)
{
    DWORD cchPortNameWithoutColon;

    cchPortNameWithoutColon = wcslen(pwszPortNameWithoutColon);

    *ppwszNonspooledPortName = DllAllocSplMem((cchNonspooledPrefix + cchPortNameWithoutColon + 1) * sizeof(WCHAR));
    if (!*ppwszNonspooledPortName)
    {
        ERR("DllAllocSplMem failed with error %lu!\n", GetLastError());
        return ERROR_NOT_ENOUGH_MEMORY;
    }

    CopyMemory(*ppwszNonspooledPortName, wszNonspooledPrefix, cchNonspooledPrefix * sizeof(WCHAR));
    CopyMemory(&(*ppwszNonspooledPortName)[cchNonspooledPrefix], pwszPortNameWithoutColon, (cchPortNameWithoutColon + 1) * sizeof(WCHAR));

    return ERROR_SUCCESS;
}
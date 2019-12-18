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
typedef  int* PCWSTR ;
typedef  size_t DWORD ;

/* Variables and functions */
 int /*<<< orphan*/  CopyMemory (int /*<<< orphan*/ ,int*,size_t) ; 
 int /*<<< orphan*/  DllAllocSplMem (size_t) ; 
 int /*<<< orphan*/  ERR (char*,int /*<<< orphan*/ ) ; 
 size_t ERROR_INVALID_PARAMETER ; 
 size_t ERROR_NOT_ENOUGH_MEMORY ; 
 size_t ERROR_SUCCESS ; 
 int /*<<< orphan*/  GetLastError () ; 
 size_t wcslen (int*) ; 

DWORD
GetPortNameWithoutColon(PCWSTR pwszPortName, PWSTR* ppwszPortNameWithoutColon)
{
    DWORD cchPortNameWithoutColon;

    // Compute the string length of pwszPortNameWithoutColon.
    cchPortNameWithoutColon = wcslen(pwszPortName) - 1;

    // Check if pwszPortName really has a colon as the last character.
    if (pwszPortName[cchPortNameWithoutColon] != L':')
        return ERROR_INVALID_PARAMETER;

    // Allocate the output buffer.
    *ppwszPortNameWithoutColon = DllAllocSplMem((cchPortNameWithoutColon + 1) * sizeof(WCHAR));
    if (!*ppwszPortNameWithoutColon)
    {
        ERR("DllAllocSplMem failed with error %lu!\n", GetLastError());
        return ERROR_NOT_ENOUGH_MEMORY;
    }

    // Copy the port name without colon into the buffer.
    // The buffer is already zero-initialized, so no additional null-termination is necessary.
    CopyMemory(*ppwszPortNameWithoutColon, pwszPortName, cchPortNameWithoutColon * sizeof(WCHAR));

    return ERROR_SUCCESS;
}
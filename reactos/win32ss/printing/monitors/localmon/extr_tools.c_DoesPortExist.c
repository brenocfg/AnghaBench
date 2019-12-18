#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_4__ {int /*<<< orphan*/  pName; } ;
typedef  TYPE_1__* PPORT_INFO_1W ;
typedef  int /*<<< orphan*/  PCWSTR ;
typedef  int /*<<< orphan*/ * PBYTE ;
typedef  scalar_t__ DWORD ;
typedef  int /*<<< orphan*/  BOOL ;

/* Variables and functions */
 TYPE_1__* DllAllocSplMem (scalar_t__) ; 
 int /*<<< orphan*/  DllFreeSplMem (TYPE_1__*) ; 
 int /*<<< orphan*/  ERR (char*,scalar_t__) ; 
 scalar_t__ ERROR_INSUFFICIENT_BUFFER ; 
 scalar_t__ ERROR_NOT_ENOUGH_MEMORY ; 
 scalar_t__ ERROR_SUCCESS ; 
 int /*<<< orphan*/  EnumPortsW (int /*<<< orphan*/ *,int,int /*<<< orphan*/ *,scalar_t__,scalar_t__*,scalar_t__*) ; 
 int /*<<< orphan*/  FALSE ; 
 scalar_t__ GetLastError () ; 
 int /*<<< orphan*/  SetLastError (scalar_t__) ; 
 int /*<<< orphan*/  TRUE ; 
 scalar_t__ wcsicmp (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

BOOL
DoesPortExist(PCWSTR pwszPortName)
{
    BOOL bReturnValue = FALSE;
    DWORD cbNeeded;
    DWORD dwErrorCode;
    DWORD dwReturned;
    DWORD i;
    PPORT_INFO_1W p;
    PPORT_INFO_1W pPortInfo1 = NULL;

    // Determine the required buffer size.
    EnumPortsW(NULL, 1, NULL, 0, &cbNeeded, &dwReturned);
    if (GetLastError() != ERROR_INSUFFICIENT_BUFFER)
    {
        dwErrorCode = GetLastError();
        ERR("EnumPortsW failed with error %lu!\n", dwErrorCode);
        goto Cleanup;
    }

    // Allocate a buffer large enough.
    pPortInfo1 = DllAllocSplMem(cbNeeded);
    if (!pPortInfo1)
    {
        dwErrorCode = ERROR_NOT_ENOUGH_MEMORY;
        ERR("DllAllocSplMem failed with error %lu!\n", GetLastError());
        goto Cleanup;
    }

    // Now get the actual port information.
    if (!EnumPortsW(NULL, 1, (PBYTE)pPortInfo1, cbNeeded, &cbNeeded, &dwReturned))
    {
        dwErrorCode = GetLastError();
        ERR("EnumPortsW failed with error %lu!\n", dwErrorCode);
        goto Cleanup;
    }

    // We were successful! Loop through all returned ports.
    dwErrorCode = ERROR_SUCCESS;
    p = pPortInfo1;

    for (i = 0; i < dwReturned; i++)
    {
        // Check if this existing port matches our queried one.
        if (wcsicmp(p->pName, pwszPortName) == 0)
        {
            bReturnValue = TRUE;
            goto Cleanup;
        }

        p++;
    }

Cleanup:
    if (pPortInfo1)
        DllFreeSplMem(pPortInfo1);

    SetLastError(dwErrorCode);
    return bReturnValue;
}
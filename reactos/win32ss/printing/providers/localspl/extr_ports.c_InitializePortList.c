#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_18__   TYPE_7__ ;
typedef  struct TYPE_17__   TYPE_6__ ;
typedef  struct TYPE_16__   TYPE_5__ ;
typedef  struct TYPE_15__   TYPE_4__ ;
typedef  struct TYPE_14__   TYPE_3__ ;
typedef  struct TYPE_13__   TYPE_2__ ;
typedef  struct TYPE_12__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  WCHAR ;
struct TYPE_12__ {int (* pfnEnumPorts ) (int /*<<< orphan*/ *,int,int /*<<< orphan*/ *,scalar_t__,scalar_t__*,scalar_t__*) ;} ;
struct TYPE_18__ {TYPE_1__ Monitor; } ;
struct TYPE_17__ {struct TYPE_17__* Flink; } ;
struct TYPE_16__ {int /*<<< orphan*/  Entry; scalar_t__ pwszName; TYPE_4__* pPrintMonitor; } ;
struct TYPE_15__ {int /*<<< orphan*/  pwszName; scalar_t__ pMonitor; int /*<<< orphan*/  hMonitor; scalar_t__ bIsLevel2; } ;
struct TYPE_14__ {int (* pfnEnumPorts ) (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int,int /*<<< orphan*/ *,scalar_t__,scalar_t__*,scalar_t__*) ;} ;
struct TYPE_13__ {int /*<<< orphan*/  pName; } ;
typedef  scalar_t__ PWSTR ;
typedef  TYPE_2__* PPORT_INFO_1W ;
typedef  TYPE_3__* PMONITOR2 ;
typedef  TYPE_4__* PLOCAL_PRINT_MONITOR ;
typedef  TYPE_5__* PLOCAL_PORT ;
typedef  TYPE_6__* PLIST_ENTRY ;
typedef  int /*<<< orphan*/ * PBYTE ;
typedef  TYPE_7__* LPMONITOREX ;
typedef  int /*<<< orphan*/  LOCAL_PORT ;
typedef  scalar_t__ DWORD ;
typedef  int BOOL ;

/* Variables and functions */
 TYPE_4__* CONTAINING_RECORD (TYPE_6__*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  CopyMemory (scalar_t__,int /*<<< orphan*/ ,scalar_t__) ; 
 void* DllAllocSplMem (int) ; 
 int /*<<< orphan*/  DllFreeSplMem (TYPE_2__*) ; 
 int /*<<< orphan*/  ERR (char*,...) ; 
 scalar_t__ ERROR_INSUFFICIENT_BUFFER ; 
 scalar_t__ ERROR_NOT_ENOUGH_MEMORY ; 
 scalar_t__ ERROR_SUCCESS ; 
 int /*<<< orphan*/  Entry ; 
 scalar_t__ GetLastError () ; 
 int /*<<< orphan*/  InitializeListHead (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  InsertTailList (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  LOCAL_PRINT_MONITOR ; 
 TYPE_6__ PrintMonitorList ; 
 int /*<<< orphan*/  SetLastError (scalar_t__) ; 
 int /*<<< orphan*/  TRACE (char*) ; 
 int /*<<< orphan*/  _PortList ; 
 int stub1 (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int,int /*<<< orphan*/ *,scalar_t__,scalar_t__*,scalar_t__*) ; 
 int stub2 (int /*<<< orphan*/ *,int,int /*<<< orphan*/ *,scalar_t__,scalar_t__*,scalar_t__*) ; 
 int stub3 (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int,int /*<<< orphan*/ *,scalar_t__,scalar_t__*,scalar_t__*) ; 
 int stub4 (int /*<<< orphan*/ *,int,int /*<<< orphan*/ *,scalar_t__,scalar_t__*,scalar_t__*) ; 
 int wcslen (int /*<<< orphan*/ ) ; 

BOOL
InitializePortList(void)
{
    BOOL bReturnValue;
    DWORD cbNeeded;
    DWORD cbPortName;
    DWORD dwErrorCode;
    DWORD dwReturned;
    DWORD i;
    PLOCAL_PORT pPort;
    PLOCAL_PRINT_MONITOR pPrintMonitor;
    PLIST_ENTRY pEntry;
    PPORT_INFO_1W p;
    PPORT_INFO_1W pPortInfo1 = NULL;

    TRACE("InitializePortList()\n");

    // Initialize an empty list for our Ports.
    InitializeListHead(&_PortList);

    // Loop through all Print Monitors.
    for (pEntry = PrintMonitorList.Flink; pEntry != &PrintMonitorList; pEntry = pEntry->Flink)
    {
        // Cleanup from the previous run.
        if (pPortInfo1)
        {
            DllFreeSplMem(pPortInfo1);
            pPortInfo1 = NULL;
        }

        pPrintMonitor = CONTAINING_RECORD(pEntry, LOCAL_PRINT_MONITOR, Entry);

        // Determine the required buffer size for EnumPorts.
        if (pPrintMonitor->bIsLevel2)
            bReturnValue = ((PMONITOR2)pPrintMonitor->pMonitor)->pfnEnumPorts(pPrintMonitor->hMonitor, NULL, 1, NULL, 0, &cbNeeded, &dwReturned);
        else
            bReturnValue = ((LPMONITOREX)pPrintMonitor->pMonitor)->Monitor.pfnEnumPorts(NULL, 1, NULL, 0, &cbNeeded, &dwReturned);

        // Check the returned error code.
        if (GetLastError() != ERROR_INSUFFICIENT_BUFFER)
        {
            ERR("Print Monitor \"%S\" failed with error %lu on EnumPorts!\n", pPrintMonitor->pwszName, GetLastError());
            continue;
        }

        // Allocate a buffer large enough.
        pPortInfo1 = DllAllocSplMem(cbNeeded);
        if (!pPortInfo1)
        {
            dwErrorCode = ERROR_NOT_ENOUGH_MEMORY;
            ERR("DllAllocSplMem failed!\n");
            goto Cleanup;
        }

        // Get the ports handled by this monitor.
        if (pPrintMonitor->bIsLevel2)
            bReturnValue = ((PMONITOR2)pPrintMonitor->pMonitor)->pfnEnumPorts(pPrintMonitor->hMonitor, NULL, 1, (PBYTE)pPortInfo1, cbNeeded, &cbNeeded, &dwReturned);
        else
            bReturnValue = ((LPMONITOREX)pPrintMonitor->pMonitor)->Monitor.pfnEnumPorts(NULL, 1, (PBYTE)pPortInfo1, cbNeeded, &cbNeeded, &dwReturned);

        // Check the return value.
        if (!bReturnValue)
        {
            ERR("Print Monitor \"%S\" failed with error %lu on EnumPorts!\n", pPrintMonitor->pwszName, GetLastError());
            continue;
        }

        // Loop through all returned ports.
        p = pPortInfo1;

        for (i = 0; i < dwReturned; i++)
        {
            cbPortName = (wcslen(p->pName) + 1) * sizeof(WCHAR);

            // Create a new LOCAL_PORT structure for it.
            pPort = DllAllocSplMem(sizeof(LOCAL_PORT) + cbPortName);
            if (!pPort)
            {
                dwErrorCode = ERROR_NOT_ENOUGH_MEMORY;
                ERR("DllAllocSplMem failed!\n");
                goto Cleanup;
            }

            pPort->pPrintMonitor = pPrintMonitor;
            pPort->pwszName = (PWSTR)((PBYTE)pPort + sizeof(LOCAL_PORT));
            CopyMemory(pPort->pwszName, p->pName, cbPortName);

            // Insert it into the list and advance to the next port.
            InsertTailList(&_PortList, &pPort->Entry);
            p++;
        }
    }

    dwErrorCode = ERROR_SUCCESS;

Cleanup:
    // Inside the loop
    if (pPortInfo1)
        DllFreeSplMem(pPortInfo1);

    SetLastError(dwErrorCode);
    return (dwErrorCode == ERROR_SUCCESS);
}
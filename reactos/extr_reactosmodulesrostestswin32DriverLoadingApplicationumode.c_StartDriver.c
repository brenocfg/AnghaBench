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
typedef  int /*<<< orphan*/  SC_HANDLE ;
typedef  int /*<<< orphan*/  LPCWSTR ;
typedef  scalar_t__ BOOL ;

/* Variables and functions */
 int /*<<< orphan*/  CloseServiceHandle (int /*<<< orphan*/ ) ; 
 char* DRIVER_NAME ; 
 scalar_t__ ERROR_SERVICE_ALREADY_RUNNING ; 
 scalar_t__ FALSE ; 
 scalar_t__ GetLastError () ; 
 int /*<<< orphan*/  OpenSCManagerW (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  OpenServiceW (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  SC_MANAGER_ALL_ACCESS ; 
 int /*<<< orphan*/  SERVICE_ALL_ACCESS ; 
 scalar_t__ StartServiceW (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 scalar_t__ TRUE ; 
 int /*<<< orphan*/  wprintf (char*,char*) ; 

BOOL
StartDriver(LPCWSTR lpDriverName)
{
    SC_HANDLE hSCManager;
    SC_HANDLE hService;
    BOOL bRet;

    hSCManager = OpenSCManagerW(NULL,
                                NULL,
                                SC_MANAGER_ALL_ACCESS);
    if (!hSCManager)
        return FALSE;

    hService = OpenServiceW(hSCManager,
                            lpDriverName,
                            SERVICE_ALL_ACCESS);
    if (!hService)
    {
        CloseServiceHandle(hSCManager);
        return FALSE;
    }

    bRet = StartServiceW(hService, 0, NULL);
    if (!bRet)
    {
        if (GetLastError() == ERROR_SERVICE_ALREADY_RUNNING)
        {
            wprintf(L"%s.sys already running\n", DRIVER_NAME);
            bRet = TRUE;
        }
    }

    CloseServiceHandle(hService);
    CloseServiceHandle(hSCManager);

    return bRet;
}
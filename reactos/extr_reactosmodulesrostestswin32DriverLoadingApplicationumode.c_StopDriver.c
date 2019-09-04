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
typedef  int /*<<< orphan*/  SERVICE_STATUS ;
typedef  int /*<<< orphan*/  SC_HANDLE ;
typedef  int /*<<< orphan*/  LPCWSTR ;
typedef  scalar_t__ BOOL ;

/* Variables and functions */
 int /*<<< orphan*/  CloseServiceHandle (int /*<<< orphan*/ ) ; 
 scalar_t__ ControlService (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 char* DRIVER_NAME ; 
 scalar_t__ ERROR_SERVICE_NOT_ACTIVE ; 
 scalar_t__ FALSE ; 
 scalar_t__ GetLastError () ; 
 int /*<<< orphan*/  OpenSCManagerW (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  OpenServiceW (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  SC_MANAGER_ALL_ACCESS ; 
 int /*<<< orphan*/  SERVICE_ALL_ACCESS ; 
 int /*<<< orphan*/  SERVICE_CONTROL_STOP ; 
 scalar_t__ TRUE ; 
 int /*<<< orphan*/  wprintf (char*,char*) ; 

BOOL
StopDriver(LPCWSTR lpDriverName)
{
    SC_HANDLE hSCManager;
    SC_HANDLE hService;
    SERVICE_STATUS serviceStatus;
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

    bRet = ControlService(hService,
                          SERVICE_CONTROL_STOP,
                          &serviceStatus);
    if (!bRet)
    {
        if (GetLastError() == ERROR_SERVICE_NOT_ACTIVE)
        {
            wprintf(L"%s.sys wasn't running\n", DRIVER_NAME);
            bRet = TRUE;
        }
    }

    CloseServiceHandle(hService);
    CloseServiceHandle(hSCManager);

    return bRet;
}
#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_2__ ;
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  WCHAR ;
struct TYPE_8__ {int /*<<< orphan*/  lpBinaryPathName; int /*<<< orphan*/  lpDisplayName; } ;
struct TYPE_7__ {scalar_t__ dwCurrentState; } ;
typedef  TYPE_1__ SERVICE_STATUS ;
typedef  int /*<<< orphan*/ * SC_HANDLE ;
typedef  TYPE_2__* LPQUERY_SERVICE_CONFIGW ;
typedef  int /*<<< orphan*/  LPARAM ;
typedef  int /*<<< orphan*/  INT_PTR ;
typedef  int /*<<< orphan*/  HWND ;
typedef  int /*<<< orphan*/  DWORD ;

/* Variables and functions */
 int /*<<< orphan*/  CloseServiceHandle (int /*<<< orphan*/ *) ; 
 scalar_t__ ERROR_INSUFFICIENT_BUFFER ; 
 int /*<<< orphan*/  EnableWindow (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  FALSE ; 
 int /*<<< orphan*/  GetDlgItem (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ GetLastError () ; 
 int /*<<< orphan*/  GetProcessHeap () ; 
 TYPE_2__* HeapAlloc (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  HeapFree (int /*<<< orphan*/ ,int /*<<< orphan*/ ,TYPE_2__*) ; 
 int /*<<< orphan*/  IDC_DRIVERINFO ; 
 int /*<<< orphan*/  IDC_DRIVERINSTALL ; 
 int /*<<< orphan*/  IDC_DRIVERREMOVE ; 
 int MAX_PATH ; 
 int /*<<< orphan*/ * OpenSCManager (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * OpenService (int /*<<< orphan*/ *,char*,int) ; 
 scalar_t__ QueryServiceConfig (int /*<<< orphan*/ *,TYPE_2__*,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 scalar_t__ QueryServiceStatus (int /*<<< orphan*/ *,TYPE_1__*) ; 
 int /*<<< orphan*/  SC_MANAGER_CONNECT ; 
 int SERVICE_QUERY_CONFIG ; 
 int SERVICE_QUERY_STATUS ; 
 scalar_t__ SERVICE_RUNNING ; 
 scalar_t__ SERVICE_START_PENDING ; 
 int /*<<< orphan*/  SW_SHOW ; 
 int /*<<< orphan*/  SendMessage (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  SetServiceState (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ShowWindow (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  TRUE ; 
 int /*<<< orphan*/  WM_SETTEXT ; 
 int /*<<< orphan*/  hDriverWnd ; 
 int /*<<< orphan*/  wsprintf (int /*<<< orphan*/ *,char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

INT_PTR
QueryDriverInfo(HWND hDlg)
{
    DWORD dwSize;
    SC_HANDLE hMgr, hSvc;
    LPQUERY_SERVICE_CONFIGW pConfig;
    WCHAR szText[2 * MAX_PATH];
    HWND hControl;
    SERVICE_STATUS Status;

    hDriverWnd = hDlg;

    /* Open service manager */
    hMgr = OpenSCManager(NULL, NULL, SC_MANAGER_CONNECT);
    if (hMgr != NULL)
    {
        /* Open our service */
        hSvc = OpenService(hMgr, L"Vcdrom", SERVICE_QUERY_CONFIG | SERVICE_QUERY_STATUS);
        if (hSvc != NULL)
        {
            /* Probe its config size */
            if (!QueryServiceConfig(hSvc, NULL, 0, &dwSize) &&
                GetLastError() == ERROR_INSUFFICIENT_BUFFER)
            {
                /* And get its config */
                pConfig = HeapAlloc(GetProcessHeap(), 0, dwSize);

                if (QueryServiceConfig(hSvc, pConfig, dwSize, &dwSize))
                {
                    /* Display name & driver */
                    wsprintf(szText, L"%s:\n(%s)", pConfig->lpDisplayName, pConfig->lpBinaryPathName);
                    hControl = GetDlgItem(hDriverWnd, IDC_DRIVERINFO);
                    SendMessage(hControl, WM_SETTEXT, 0, (LPARAM)szText);
                }

                HeapFree(GetProcessHeap(), 0, pConfig);
            }

            /* Get its status */
            if (QueryServiceStatus(hSvc, &Status))
            {
                if (Status.dwCurrentState != SERVICE_RUNNING &&
                    Status.dwCurrentState != SERVICE_START_PENDING)
                {
                    SetServiceState(FALSE);
                }
                else
                {
                    SetServiceState(TRUE);
                }
            }

            CloseServiceHandle(hSvc);
        }

        CloseServiceHandle(hMgr);
    }

    /* FIXME: we don't allow uninstall/install */
    {
        hControl = GetDlgItem(hDriverWnd, IDC_DRIVERINSTALL);
        EnableWindow(hControl, FALSE);
        hControl = GetDlgItem(hDriverWnd, IDC_DRIVERREMOVE);
        EnableWindow(hControl, FALSE);
    }

    /* Display our sub window */
    ShowWindow(hDlg, SW_SHOW);

    return TRUE;
}
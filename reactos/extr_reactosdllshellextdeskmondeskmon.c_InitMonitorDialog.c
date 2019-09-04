#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_16__   TYPE_4__ ;
typedef  struct TYPE_15__   TYPE_3__ ;
typedef  struct TYPE_14__   TYPE_2__ ;
typedef  struct TYPE_13__   TYPE_1__ ;
typedef  struct TYPE_12__   TYPE_10__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  dd ;
typedef  int /*<<< orphan*/  WPARAM ;
typedef  int /*<<< orphan*/  VOID ;
struct TYPE_16__ {int cb; } ;
struct TYPE_12__ {int /*<<< orphan*/ * DeviceString; } ;
struct TYPE_15__ {struct TYPE_15__* Next; TYPE_10__ dd; } ;
struct TYPE_14__ {int dwMonitorCount; int /*<<< orphan*/  hwndDlg; TYPE_3__* SelMonitor; TYPE_3__* Monitors; int /*<<< orphan*/  pdtobj; int /*<<< orphan*/ * lpDevModeOnInit; int /*<<< orphan*/ * lpSelDevMode; TYPE_1__* DeskExtInterface; int /*<<< orphan*/ * lpDisplayDevice; } ;
struct TYPE_13__ {int /*<<< orphan*/  Context; int /*<<< orphan*/ * (* GetCurrentMode ) (int /*<<< orphan*/ ) ;} ;
typedef  TYPE_2__* PDESKMONITOR ;
typedef  TYPE_3__* PDESKMONINFO ;
typedef  int /*<<< orphan*/ * LPTSTR ;
typedef  int /*<<< orphan*/  LPARAM ;
typedef  scalar_t__ INT ;
typedef  int /*<<< orphan*/  HLOCAL ;
typedef  scalar_t__ DWORD ;
typedef  TYPE_4__ DISPLAY_DEVICE ;
typedef  scalar_t__ BOOL ;

/* Variables and functions */
 int /*<<< orphan*/  CopyMemory (TYPE_10__*,TYPE_4__*,int) ; 
 int /*<<< orphan*/  DESK_EXT_DISPLAYDEVICE ; 
 int /*<<< orphan*/  DESK_EXT_MONITORNAME ; 
 scalar_t__ EnumDisplayDevices (int /*<<< orphan*/ *,int /*<<< orphan*/ ,TYPE_4__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  GetDlgItem (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  IDC_MONITORLIST ; 
 int /*<<< orphan*/  IDC_MONITORNAME ; 
 int /*<<< orphan*/  LB_ADDSTRING ; 
 int /*<<< orphan*/  LB_RESETCONTENT ; 
 int /*<<< orphan*/  LB_SETCURSEL ; 
 int /*<<< orphan*/  LB_SETITEMDATA ; 
 int /*<<< orphan*/  LMEM_FIXED ; 
 TYPE_3__* LocalAlloc (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  LocalFree (int /*<<< orphan*/ ) ; 
 void* QueryDeskCplString (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  RegisterClipboardFormat (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  SW_HIDE ; 
 int /*<<< orphan*/  SW_SHOW ; 
 scalar_t__ SendDlgItemMessage (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  SetDlgItemText (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  ShowWindow (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  UpdateMonitorSelection (TYPE_2__*) ; 
 int /*<<< orphan*/  UpdateRefreshFrequencyList (TYPE_2__*) ; 
 int /*<<< orphan*/ * stub1 (int /*<<< orphan*/ ) ; 

__attribute__((used)) static VOID
InitMonitorDialog(PDESKMONITOR This)
{
    PDESKMONINFO pmi, pminext, *pmilink;
    DISPLAY_DEVICE dd;
    BOOL bRet;
    INT i;
    DWORD dwIndex;

    /* Free all allocated monitors */
    pmi = This->Monitors;
    This->Monitors = NULL;
    while (pmi != NULL)
    {
        pminext = pmi->Next;
        LocalFree((HLOCAL)pmi);
        pmi = pminext;
    }

    This->SelMonitor = NULL;
    This->dwMonitorCount = 0;

    if (This->lpDisplayDevice != NULL)
        LocalFree((HLOCAL)This->lpDisplayDevice);

    This->lpDisplayDevice = QueryDeskCplString(This->pdtobj,
                                               RegisterClipboardFormat(DESK_EXT_DISPLAYDEVICE));

    if (This->DeskExtInterface != NULL)
    {
        if (This->lpDisplayDevice != NULL)
        {
            /* Enumerate all monitors */
            dwIndex = 0;
            pmilink = &This->Monitors;

            do
            {
                dd.cb = sizeof(dd);
                bRet = EnumDisplayDevices(This->lpDisplayDevice,
                                          dwIndex++,
                                          &dd,
                                          0);
                if (bRet)
                {
                    pmi = LocalAlloc(LMEM_FIXED,
                                     sizeof(*pmi));
                    if (pmi != NULL)
                    {
                        CopyMemory(&pmi->dd,
                                   &dd,
                                   sizeof(dd));
                        pmi->Next = NULL;
                        *pmilink = pmi;
                        pmilink = &pmi->Next;

                        This->dwMonitorCount++;
                    }
                }
            } while (bRet);
        }

        This->lpDevModeOnInit = This->DeskExtInterface->GetCurrentMode(This->DeskExtInterface->Context);
    }
    else
        This->lpDevModeOnInit = NULL;

    This->lpSelDevMode = This->lpDevModeOnInit;

    /* Setup the UI depending on how many monitors are attached */
    if (This->dwMonitorCount == 0)
    {
        LPTSTR lpMonitorName;

        /* This is a fallback, let's hope that desk.cpl can provide us with a monitor name */
        lpMonitorName = QueryDeskCplString(This->pdtobj,
                                           RegisterClipboardFormat(DESK_EXT_MONITORNAME));

        SetDlgItemText(This->hwndDlg,
                       IDC_MONITORNAME,
                       lpMonitorName);

        if (lpMonitorName != NULL)
            LocalFree((HLOCAL)lpMonitorName);
    }
    else if (This->dwMonitorCount == 1)
    {
        This->SelMonitor = This->Monitors;
        SetDlgItemText(This->hwndDlg,
                       IDC_MONITORNAME,
                       This->Monitors->dd.DeviceString);
    }
    else
    {
        SendDlgItemMessage(This->hwndDlg,
                           IDC_MONITORLIST,
                           LB_RESETCONTENT,
                           0,
                           0);

        pmi = This->Monitors;
        while (pmi != NULL)
        {
            i = (INT)SendDlgItemMessage(This->hwndDlg,
                                        IDC_MONITORLIST,
                                        LB_ADDSTRING,
                                        0,
                                        (LPARAM)pmi->dd.DeviceString);
            if (i >= 0)
            {
                SendDlgItemMessage(This->hwndDlg,
                                   IDC_MONITORLIST,
                                   LB_SETITEMDATA,
                                   (WPARAM)i,
                                   (LPARAM)pmi);

                if (This->SelMonitor == NULL)
                {
                    SendDlgItemMessage(This->hwndDlg,
                                       IDC_MONITORLIST,
                                       LB_SETCURSEL,
                                       (WPARAM)i,
                                       0);

                    This->SelMonitor = pmi;
                }
            }

            pmi = pmi->Next;
        }
    }

    /* Show/Hide controls */
    ShowWindow(GetDlgItem(This->hwndDlg,
                          IDC_MONITORNAME),
               (This->dwMonitorCount <= 1 ? SW_SHOW : SW_HIDE));
    ShowWindow(GetDlgItem(This->hwndDlg,
                          IDC_MONITORLIST),
               (This->dwMonitorCount > 1 ? SW_SHOW : SW_HIDE));

    UpdateRefreshFrequencyList(This);
    UpdateMonitorSelection(This);
}
#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_11__   TYPE_3__ ;
typedef  struct TYPE_10__   TYPE_2__ ;
typedef  struct TYPE_9__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  szRefreshRate ;
typedef  int /*<<< orphan*/  szFormat ;
typedef  int /*<<< orphan*/  szColors ;
typedef  int /*<<< orphan*/  szBuffer ;
typedef  int /*<<< orphan*/  WPARAM ;
typedef  int /*<<< orphan*/  VOID ;
struct TYPE_11__ {TYPE_1__* DeskExtInterface; } ;
struct TYPE_10__ {int /*<<< orphan*/  dmPelsHeight; int /*<<< orphan*/  dmPelsWidth; } ;
struct TYPE_9__ {int /*<<< orphan*/  Context; TYPE_2__* (* EnumAllModes ) (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ;TYPE_2__* (* GetCurrentMode ) (int /*<<< orphan*/ ) ;} ;
typedef  int /*<<< orphan*/  TCHAR ;
typedef  TYPE_2__* PDEVMODEW ;
typedef  TYPE_3__* PDESKDISPLAYADAPTER ;
typedef  int /*<<< orphan*/  LPARAM ;
typedef  scalar_t__ INT ;
typedef  int /*<<< orphan*/  HWND ;
typedef  scalar_t__ DWORD ;

/* Variables and functions */
 int /*<<< orphan*/  GetColorDescription (TYPE_2__*,int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  GetRefreshRateDescription (TYPE_2__*,int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  IDC_ALLVALIDMODES ; 
 int /*<<< orphan*/  IDS_MODEFMT ; 
 int /*<<< orphan*/  LB_ADDSTRING ; 
 int /*<<< orphan*/  LB_SETCURSEL ; 
 int /*<<< orphan*/  LB_SETITEMDATA ; 
 int /*<<< orphan*/  LoadString (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int) ; 
 scalar_t__ SendDlgItemMessage (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  TEXT (char) ; 
 int /*<<< orphan*/  _sntprintf (int /*<<< orphan*/ *,int,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  hInstance ; 
 TYPE_2__* stub1 (int /*<<< orphan*/ ) ; 
 TYPE_2__* stub2 (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static VOID
InitListAllModesDialog(PDESKDISPLAYADAPTER This,
                       HWND hwndListAllModesDlg)
{
    TCHAR szFormat[64], szBuffer[64], szColors[64], szRefreshRate[64];
    PDEVMODEW lpDevMode, lpCurrentDevMode;
    DWORD dwIndex = 0;
    INT i;

    if (This->DeskExtInterface != NULL)
    {
        if (!LoadString(hInstance,
                        IDS_MODEFMT,
                        szFormat,
                        sizeof(szFormat) / sizeof(szFormat[0])))
        {
            szFormat[0] = TEXT('\0');
        }

        lpCurrentDevMode = This->DeskExtInterface->GetCurrentMode(This->DeskExtInterface->Context);

        do
        {
            lpDevMode = This->DeskExtInterface->EnumAllModes(This->DeskExtInterface->Context,
                                                             dwIndex++);
            if (lpDevMode != NULL)
            {
                GetColorDescription(lpDevMode,
                                    szColors,
                                    sizeof(szColors) / sizeof(szColors[0]));

                GetRefreshRateDescription(lpDevMode,
                                          szRefreshRate,
                                          sizeof(szRefreshRate) / sizeof(szRefreshRate[0]));

                _sntprintf(szBuffer,
                           sizeof(szBuffer) / sizeof(szBuffer[0]),
                           szFormat,
                           lpDevMode->dmPelsWidth,
                           lpDevMode->dmPelsHeight,
                           szColors,
                           szRefreshRate);

                i = (INT)SendDlgItemMessage(hwndListAllModesDlg,
                                            IDC_ALLVALIDMODES,
                                            LB_ADDSTRING,
                                            0,
                                            (LPARAM)szBuffer);
                if (i >= 0)
                {
                    SendDlgItemMessage(hwndListAllModesDlg,
                                       IDC_ALLVALIDMODES,
                                       LB_SETITEMDATA,
                                       (WPARAM)i,
                                       (LPARAM)lpDevMode);

                    if (lpDevMode == lpCurrentDevMode)
                    {
                        SendDlgItemMessage(hwndListAllModesDlg,
                                           IDC_ALLVALIDMODES,
                                           LB_SETCURSEL,
                                           (WPARAM)i,
                                           0);
                    }
                }
            }

        } while (lpDevMode != NULL);
    }
}
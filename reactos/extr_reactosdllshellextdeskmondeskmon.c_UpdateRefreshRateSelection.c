#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  WPARAM ;
typedef  int /*<<< orphan*/  VOID ;
struct TYPE_6__ {scalar_t__ lpSelDevMode; int /*<<< orphan*/  hwndDlg; TYPE_1__* DeskExtInterface; } ;
struct TYPE_5__ {int /*<<< orphan*/  Context; int /*<<< orphan*/  (* SetCurrentMode ) (int /*<<< orphan*/ ,scalar_t__) ;} ;
typedef  scalar_t__ PDEVMODEW ;
typedef  TYPE_2__* PDESKMONITOR ;
typedef  scalar_t__ INT ;

/* Variables and functions */
 int /*<<< orphan*/  CB_GETCURSEL ; 
 int /*<<< orphan*/  CB_GETITEMDATA ; 
 int /*<<< orphan*/  GetParent (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  IDC_REFRESHRATE ; 
 int /*<<< orphan*/  PropSheet_Changed (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ SendDlgItemMessage (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  UpdateRefreshFrequencyList (TYPE_2__*) ; 
 int /*<<< orphan*/  stub1 (int /*<<< orphan*/ ,scalar_t__) ; 

__attribute__((used)) static VOID
UpdateRefreshRateSelection(PDESKMONITOR This)
{
    PDEVMODEW lpCurrentDevMode;
    INT i;

    if (This->DeskExtInterface != NULL)
    {
        i = (INT)SendDlgItemMessage(This->hwndDlg,
                                    IDC_REFRESHRATE,
                                    CB_GETCURSEL,
                                    0,
                                    0);
        if (i >= 0)
        {
            lpCurrentDevMode = This->lpSelDevMode;
            This->lpSelDevMode = (PDEVMODEW)SendDlgItemMessage(This->hwndDlg,
                                                               IDC_REFRESHRATE,
                                                               CB_GETITEMDATA,
                                                               (WPARAM)i,
                                                               0);

            if (This->lpSelDevMode != NULL && This->lpSelDevMode != lpCurrentDevMode)
            {
                This->DeskExtInterface->SetCurrentMode(This->DeskExtInterface->Context,
                                                       This->lpSelDevMode);

                UpdateRefreshFrequencyList(This);

                (void)PropSheet_Changed(GetParent(This->hwndDlg),
                                        This->hwndDlg);
            }
        }
    }
}
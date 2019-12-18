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
struct TYPE_4__ {int state; } ;
typedef  TYPE_1__* PWND ;
typedef  scalar_t__ HWND ;

/* Variables and functions */
 int DS_CONTROL ; 
 int /*<<< orphan*/  GWL_STYLE ; 
 scalar_t__ GetDesktopWindow () ; 
 scalar_t__ GetParent (scalar_t__) ; 
 int GetWindowLongA (scalar_t__,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  IsWindow (scalar_t__) ; 
 int /*<<< orphan*/  TestWindowProcess (TYPE_1__*) ; 
 TYPE_1__* ValidateHwnd (scalar_t__) ; 
 int WNDS_DIALOGWINDOW ; 

__attribute__((used)) static HWND DIALOG_FindMsgDestination( HWND hwndDlg )
{
    while (GetWindowLongA(hwndDlg, GWL_STYLE) & DS_CONTROL)
    {
        PWND pWnd;
        HWND hParent = GetParent(hwndDlg);
        if (!hParent) break;
// ReactOS
        if (!IsWindow(hParent)) break;

        pWnd = ValidateHwnd(hParent);
        // FIXME: Use pWnd->fnid == FNID_DESKTOP
        if (!pWnd || !TestWindowProcess(pWnd) || hParent == GetDesktopWindow()) break;

        if (!(pWnd->state & WNDS_DIALOGWINDOW))
        {
            break;
        }

        hwndDlg = hParent;
    }

    return hwndDlg;
}
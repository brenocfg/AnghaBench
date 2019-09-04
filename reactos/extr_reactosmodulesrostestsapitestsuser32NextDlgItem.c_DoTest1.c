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
typedef  scalar_t__ HWND ;

/* Variables and functions */
 int /*<<< orphan*/  FALSE ; 
 scalar_t__ GetDlgCtrlID (scalar_t__) ; 
 scalar_t__ GetDlgItem (scalar_t__,scalar_t__) ; 
 int /*<<< orphan*/  GetNameFromHWND (scalar_t__) ; 
 scalar_t__ GetNextDlgTabItem (scalar_t__,scalar_t__,int /*<<< orphan*/ ) ; 
 scalar_t__ IDCANCEL ; 
 scalar_t__ IDOK ; 
 int /*<<< orphan*/  SW_HIDE ; 
 int /*<<< orphan*/  SW_SHOWNOACTIVATE ; 
 scalar_t__ ShowWindow (scalar_t__,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  TRUE ; 
 int /*<<< orphan*/  ok (int,char*,...) ; 
 scalar_t__ psh1 ; 
 scalar_t__ rad1 ; 
 scalar_t__ rad2 ; 
 scalar_t__ rad3 ; 
 scalar_t__ rad5 ; 
 scalar_t__ rad6 ; 
 scalar_t__ rad7 ; 

__attribute__((used)) static void
DoTest1(HWND hwnd)
{
    HWND hCtrl;
    HWND hRad1, hRad2, hRad3, hPsh1, hRad5, hRad6, hRad7, hOK, hCancel;

    // check control IDs
    hCtrl = GetDlgItem(hwnd, rad1);
    ok(GetDlgCtrlID(hCtrl) == rad1, "\n");
    hCtrl = GetDlgItem(hwnd, rad2);
    ok(GetDlgCtrlID(hCtrl) == rad2, "\n");
    hCtrl = GetDlgItem(hwnd, rad3);
    ok(GetDlgCtrlID(hCtrl) == rad3, "\n");
    hCtrl = GetDlgItem(hwnd, psh1);
    ok(GetDlgCtrlID(hCtrl) == psh1, "\n");
    hCtrl = GetDlgItem(hwnd, rad5);
    ok(GetDlgCtrlID(hCtrl) == rad5, "\n");
    hCtrl = GetDlgItem(hwnd, rad6);
    ok(GetDlgCtrlID(hCtrl) == rad6, "\n");
    hCtrl = GetDlgItem(hwnd, rad7);
    ok(GetDlgCtrlID(hCtrl) == rad7, "\n");
    hCtrl = GetDlgItem(hwnd, IDOK);
    ok(GetDlgCtrlID(hCtrl) == IDOK, "\n");
    hCtrl = GetDlgItem(hwnd, IDCANCEL);
    ok(GetDlgCtrlID(hCtrl) == IDCANCEL, "\n");

    // get dialog items
    hRad1 = GetDlgItem(hwnd, rad1);
    hRad2 = GetDlgItem(hwnd, rad2);
    hRad3 = GetDlgItem(hwnd, rad3);
    hPsh1 = GetDlgItem(hwnd, psh1);
    hRad5 = GetDlgItem(hwnd, rad5);
    hRad6 = GetDlgItem(hwnd, rad6);
    hRad7 = GetDlgItem(hwnd, rad7);
    hOK = GetDlgItem(hwnd, IDOK);
    hCancel = GetDlgItem(hwnd, IDCANCEL);

    // next
    hCtrl = GetNextDlgTabItem(hwnd, hRad1, FALSE);
    ok(hCtrl == hRad2, "hCtrl was %s\n", GetNameFromHWND(hCtrl));
    hCtrl = GetNextDlgTabItem(hwnd, hRad2, FALSE);
    ok(hCtrl == hRad3, "hCtrl was %s\n", GetNameFromHWND(hCtrl));
    hCtrl = GetNextDlgTabItem(hwnd, hRad3, FALSE);
    ok(hCtrl == hPsh1, "hCtrl was %s\n", GetNameFromHWND(hCtrl));
    hCtrl = GetNextDlgTabItem(hwnd, hPsh1, FALSE);
    ok(hCtrl == hRad5, "hCtrl was %s\n", GetNameFromHWND(hCtrl));
    hCtrl = GetNextDlgTabItem(hwnd, hRad5, FALSE);
    ok(hCtrl == hRad6, "hCtrl was %s\n", GetNameFromHWND(hCtrl));
    hCtrl = GetNextDlgTabItem(hwnd, hRad6, FALSE);
    ok(hCtrl == hRad7, "hCtrl was %s\n", GetNameFromHWND(hCtrl));
    hCtrl = GetNextDlgTabItem(hwnd, hRad7, FALSE);
    ok(hCtrl == hOK, "hCtrl was %s\n", GetNameFromHWND(hCtrl));
    hCtrl = GetNextDlgTabItem(hwnd, hOK, FALSE);
    ok(hCtrl == hCancel, "hCtrl was %s\n", GetNameFromHWND(hCtrl));
    hCtrl = GetNextDlgTabItem(hwnd, hCancel, FALSE);
    ok(hCtrl == hRad1, "hCtrl was %s\n", GetNameFromHWND(hCtrl));

    // prev
    hCtrl = GetNextDlgTabItem(hwnd, hRad1, TRUE);
    ok(hCtrl == hCancel, "hCtrl was %s\n", GetNameFromHWND(hCtrl));
    hCtrl = GetNextDlgTabItem(hwnd, hRad2, TRUE);
    ok(hCtrl == hRad1, "hCtrl was %s\n", GetNameFromHWND(hCtrl));
    hCtrl = GetNextDlgTabItem(hwnd, hRad3, TRUE);
    ok(hCtrl == hRad2, "hCtrl was %s\n", GetNameFromHWND(hCtrl));
    hCtrl = GetNextDlgTabItem(hwnd, hPsh1, TRUE);
    ok(hCtrl == hRad3, "hCtrl was %s\n", GetNameFromHWND(hCtrl));
    hCtrl = GetNextDlgTabItem(hwnd, hRad5, TRUE);
    ok(hCtrl == hPsh1, "hCtrl was %s\n", GetNameFromHWND(hCtrl));
    hCtrl = GetNextDlgTabItem(hwnd, hRad6, TRUE);
    ok(hCtrl == hRad5, "hCtrl was %s\n", GetNameFromHWND(hCtrl));
    hCtrl = GetNextDlgTabItem(hwnd, hRad7, TRUE);
    ok(hCtrl == hRad6, "hCtrl was %s\n", GetNameFromHWND(hCtrl));
    hCtrl = GetNextDlgTabItem(hwnd, hOK, TRUE);
    ok(hCtrl == hRad7, "hCtrl was %s\n", GetNameFromHWND(hCtrl));
    hCtrl = GetNextDlgTabItem(hwnd, hCancel, TRUE);
    ok(hCtrl == hOK, "hCtrl was %s\n", GetNameFromHWND(hCtrl));

    // hide
    ok(ShowWindow(hRad3, SW_HIDE) != 0, "\n");
    ok(ShowWindow(hRad6, SW_HIDE) != 0, "\n");

    // next with hidden
    hCtrl = GetNextDlgTabItem(hwnd, hRad1, FALSE);
    ok(hCtrl == hRad2, "hCtrl was %s\n", GetNameFromHWND(hCtrl));
    hCtrl = GetNextDlgTabItem(hwnd, hRad2, FALSE);
    ok(hCtrl == hPsh1, "hCtrl was %s\n", GetNameFromHWND(hCtrl));
    hCtrl = GetNextDlgTabItem(hwnd, hPsh1, FALSE);
    ok(hCtrl == hRad5, "hCtrl was %s\n", GetNameFromHWND(hCtrl));
    hCtrl = GetNextDlgTabItem(hwnd, hRad5, FALSE);
    ok(hCtrl == hRad7, "hCtrl was %s\n", GetNameFromHWND(hCtrl));
    hCtrl = GetNextDlgTabItem(hwnd, hRad7, FALSE);
    ok(hCtrl == hOK, "hCtrl was %s\n", GetNameFromHWND(hCtrl));
    hCtrl = GetNextDlgTabItem(hwnd, hOK, FALSE);
    ok(hCtrl == hCancel, "hCtrl was %s\n", GetNameFromHWND(hCtrl));
    hCtrl = GetNextDlgTabItem(hwnd, hCancel, FALSE);
    ok(hCtrl == hRad1, "hCtrl was %s\n", GetNameFromHWND(hCtrl));

    // prev with hidden
    hCtrl = GetNextDlgTabItem(hwnd, hRad1, TRUE);
    ok(hCtrl == hCancel, "hCtrl was %s\n", GetNameFromHWND(hCtrl));
    hCtrl = GetNextDlgTabItem(hwnd, hRad2, TRUE);
    ok(hCtrl == hRad1, "hCtrl was %s\n", GetNameFromHWND(hCtrl));
    hCtrl = GetNextDlgTabItem(hwnd, hPsh1, TRUE);
    ok(hCtrl == hRad2, "hCtrl was %s\n", GetNameFromHWND(hCtrl));
    hCtrl = GetNextDlgTabItem(hwnd, hRad5, TRUE);
    ok(hCtrl == hPsh1, "hCtrl was %s\n", GetNameFromHWND(hCtrl));
    hCtrl = GetNextDlgTabItem(hwnd, hRad7, TRUE);
    ok(hCtrl == hRad5, "hCtrl was %s\n", GetNameFromHWND(hCtrl));
    hCtrl = GetNextDlgTabItem(hwnd, hOK, TRUE);
    ok(hCtrl == hRad7, "hCtrl was %s\n", GetNameFromHWND(hCtrl));
    hCtrl = GetNextDlgTabItem(hwnd, hCancel, TRUE);
    ok(hCtrl == hOK, "hCtrl was %s\n", GetNameFromHWND(hCtrl));

    // show
    ShowWindow(hRad3, SW_SHOWNOACTIVATE);
    ShowWindow(hRad6, SW_SHOWNOACTIVATE);

    // next again
    hCtrl = GetNextDlgTabItem(hwnd, hRad1, FALSE);
    ok(hCtrl == hRad2, "hCtrl was %s\n", GetNameFromHWND(hCtrl));
    hCtrl = GetNextDlgTabItem(hwnd, hRad2, FALSE);
    ok(hCtrl == hRad3, "hCtrl was %s\n", GetNameFromHWND(hCtrl));
    hCtrl = GetNextDlgTabItem(hwnd, hRad3, FALSE);
    ok(hCtrl == hPsh1, "hCtrl was %s\n", GetNameFromHWND(hCtrl));
    hCtrl = GetNextDlgTabItem(hwnd, hPsh1, FALSE);
    ok(hCtrl == hRad5, "hCtrl was %s\n", GetNameFromHWND(hCtrl));
    hCtrl = GetNextDlgTabItem(hwnd, hRad5, FALSE);
    ok(hCtrl == hRad6, "hCtrl was %s\n", GetNameFromHWND(hCtrl));
    hCtrl = GetNextDlgTabItem(hwnd, hRad6, FALSE);
    ok(hCtrl == hRad7, "hCtrl was %s\n", GetNameFromHWND(hCtrl));
    hCtrl = GetNextDlgTabItem(hwnd, hRad7, FALSE);
    ok(hCtrl == hOK, "hCtrl was %s\n", GetNameFromHWND(hCtrl));
    hCtrl = GetNextDlgTabItem(hwnd, hOK, FALSE);
    ok(hCtrl == hCancel, "hCtrl was %s\n", GetNameFromHWND(hCtrl));
    hCtrl = GetNextDlgTabItem(hwnd, hCancel, FALSE);
    ok(hCtrl == hRad1, "hCtrl was %s\n", GetNameFromHWND(hCtrl));

    // prev again
    hCtrl = GetNextDlgTabItem(hwnd, hRad1, TRUE);
    ok(hCtrl == hCancel, "hCtrl was %s\n", GetNameFromHWND(hCtrl));
    hCtrl = GetNextDlgTabItem(hwnd, hRad2, TRUE);
    ok(hCtrl == hRad1, "hCtrl was %s\n", GetNameFromHWND(hCtrl));
    hCtrl = GetNextDlgTabItem(hwnd, hRad3, TRUE);
    ok(hCtrl == hRad2, "hCtrl was %s\n", GetNameFromHWND(hCtrl));
    hCtrl = GetNextDlgTabItem(hwnd, hPsh1, TRUE);
    ok(hCtrl == hRad3, "hCtrl was %s\n", GetNameFromHWND(hCtrl));
    hCtrl = GetNextDlgTabItem(hwnd, hRad5, TRUE);
    ok(hCtrl == hPsh1, "hCtrl was %s\n", GetNameFromHWND(hCtrl));
    hCtrl = GetNextDlgTabItem(hwnd, hRad6, TRUE);
    ok(hCtrl == hRad5, "hCtrl was %s\n", GetNameFromHWND(hCtrl));
    hCtrl = GetNextDlgTabItem(hwnd, hRad7, TRUE);
    ok(hCtrl == hRad6, "hCtrl was %s\n", GetNameFromHWND(hCtrl));
    hCtrl = GetNextDlgTabItem(hwnd, hOK, TRUE);
    ok(hCtrl == hRad7, "hCtrl was %s\n", GetNameFromHWND(hCtrl));
    hCtrl = GetNextDlgTabItem(hwnd, hCancel, TRUE);
    ok(hCtrl == hOK, "hCtrl was %s\n", GetNameFromHWND(hCtrl));
}
#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct TYPE_3__ {int /*<<< orphan*/  y; int /*<<< orphan*/  x; } ;
typedef  TYPE_1__ POINT ;
typedef  int /*<<< orphan*/  HWND ;

/* Variables and functions */
 scalar_t__ BST_CHECKED ; 
 scalar_t__ BST_UNCHECKED ; 
 int /*<<< orphan*/  CheckDlgButton (int /*<<< orphan*/ ,int /*<<< orphan*/ ,scalar_t__) ; 
 TYPE_1__ GetCtrlCenter (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  GetDlgItem (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ IsDlgButtonChecked (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  MAKELPARAM (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  MK_LBUTTON ; 
 int /*<<< orphan*/  SendMessage (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  WM_LBUTTONDOWN ; 
 int /*<<< orphan*/  WM_LBUTTONUP ; 
 int /*<<< orphan*/  ok (int,char*) ; 
 int /*<<< orphan*/  rad1 ; 
 int /*<<< orphan*/  rad2 ; 
 int /*<<< orphan*/  rad3 ; 
 int /*<<< orphan*/  rad5 ; 
 int /*<<< orphan*/  rad6 ; 
 int /*<<< orphan*/  rad7 ; 

__attribute__((used)) static void
DoTest3(HWND hwnd)
{
    HWND hCtrl;
    POINT pt;

    CheckDlgButton(hwnd, rad1, BST_CHECKED);
    CheckDlgButton(hwnd, rad5, BST_CHECKED);

    ok(IsDlgButtonChecked(hwnd, rad1) == BST_CHECKED, "\n");
    ok(IsDlgButtonChecked(hwnd, rad2) == BST_UNCHECKED, "\n");
    ok(IsDlgButtonChecked(hwnd, rad3) == BST_UNCHECKED, "\n");
    ok(IsDlgButtonChecked(hwnd, rad5) == BST_CHECKED, "\n");
    ok(IsDlgButtonChecked(hwnd, rad6) == BST_UNCHECKED, "\n");
    ok(IsDlgButtonChecked(hwnd, rad7) == BST_UNCHECKED, "\n");

    hCtrl = GetDlgItem(hwnd, rad1);
    pt = GetCtrlCenter(hCtrl);
    SendMessage(hCtrl, WM_LBUTTONDOWN, MK_LBUTTON, MAKELPARAM(pt.x, pt.y));
    SendMessage(hCtrl, WM_LBUTTONUP, MK_LBUTTON, MAKELPARAM(pt.x, pt.y));

    ok(IsDlgButtonChecked(hwnd, rad1) == BST_CHECKED, "\n");
    ok(IsDlgButtonChecked(hwnd, rad2) == BST_UNCHECKED, "\n");
    ok(IsDlgButtonChecked(hwnd, rad3) == BST_UNCHECKED, "\n");
    ok(IsDlgButtonChecked(hwnd, rad5) == BST_UNCHECKED, "\n");
    ok(IsDlgButtonChecked(hwnd, rad6) == BST_UNCHECKED, "\n");
    ok(IsDlgButtonChecked(hwnd, rad7) == BST_UNCHECKED, "\n");

    hCtrl = GetDlgItem(hwnd, rad5);
    pt = GetCtrlCenter(hCtrl);
    SendMessage(hCtrl, WM_LBUTTONDOWN, MK_LBUTTON, MAKELPARAM(pt.x, pt.y));
    SendMessage(hCtrl, WM_LBUTTONUP, MK_LBUTTON, MAKELPARAM(pt.x, pt.y));

    ok(IsDlgButtonChecked(hwnd, rad1) == BST_UNCHECKED, "\n");
    ok(IsDlgButtonChecked(hwnd, rad2) == BST_UNCHECKED, "\n");
    ok(IsDlgButtonChecked(hwnd, rad3) == BST_UNCHECKED, "\n");
    ok(IsDlgButtonChecked(hwnd, rad5) == BST_CHECKED, "\n");
    ok(IsDlgButtonChecked(hwnd, rad6) == BST_UNCHECKED, "\n");
    ok(IsDlgButtonChecked(hwnd, rad7) == BST_UNCHECKED, "\n");
}
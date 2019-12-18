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
typedef  int /*<<< orphan*/  UINT ;
typedef  int /*<<< orphan*/  HWND ;

/* Variables and functions */
 int /*<<< orphan*/  FALSE ; 
 int /*<<< orphan*/  GetDlgItem (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  GetParent (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  IDC_APPLY_BUTTON ; 
 int /*<<< orphan*/  IsWindowEnabled (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  KillTimer (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  PSBTN_OK ; 
 int /*<<< orphan*/  PropSheet_Changed (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  PropSheet_PressButton (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  PropSheet_UnChanged (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  TRUE ; 
 int /*<<< orphan*/  ok_int (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  s_bNotified ; 

__attribute__((used)) static void OnTimer(HWND hwnd, UINT id)
{
    HWND hwndParent, hwndApply;

    KillTimer(hwnd, id);

    ok_int(s_bNotified, TRUE);

    hwndParent = GetParent(hwnd);
    hwndApply = GetDlgItem(hwndParent, IDC_APPLY_BUTTON);
    ok_int(IsWindowEnabled(hwndApply), FALSE);

    PropSheet_Changed(hwndParent, hwnd);
    ok_int(IsWindowEnabled(hwndApply), TRUE);

    PropSheet_UnChanged(hwndParent, hwnd);
    ok_int(IsWindowEnabled(hwndApply), FALSE);

    PropSheet_PressButton(hwndParent, PSBTN_OK);
}
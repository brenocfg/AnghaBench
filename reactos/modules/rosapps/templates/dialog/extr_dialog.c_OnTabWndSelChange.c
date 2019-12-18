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

/* Variables and functions */
 int /*<<< orphan*/  BringWindowToTop (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  SW_HIDE ; 
 int /*<<< orphan*/  SW_SHOW ; 
 int /*<<< orphan*/  SetFocus (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ShowWindow (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int TabCtrl_GetCurSel (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  hPage1 ; 
 int /*<<< orphan*/  hPage2 ; 
 int /*<<< orphan*/  hPage3 ; 
 int /*<<< orphan*/  hTabWnd ; 

void OnTabWndSelChange(void)
{
    switch (TabCtrl_GetCurSel(hTabWnd)) {
    case 0:
        ShowWindow(hPage1, SW_SHOW);
        ShowWindow(hPage2, SW_HIDE);
        ShowWindow(hPage3, SW_HIDE);
        BringWindowToTop(hPage1);
        SetFocus(hTabWnd);
        break;
    case 1:
        ShowWindow(hPage1, SW_HIDE);
        ShowWindow(hPage2, SW_SHOW);
        ShowWindow(hPage3, SW_HIDE);
        BringWindowToTop(hPage2);
        SetFocus(hTabWnd);
        break;
    case 2:
        ShowWindow(hPage1, SW_HIDE);
        ShowWindow(hPage2, SW_HIDE);
        ShowWindow(hPage3, SW_SHOW);
        BringWindowToTop(hPage3);
        SetFocus(hTabWnd);
        break;
    }
}
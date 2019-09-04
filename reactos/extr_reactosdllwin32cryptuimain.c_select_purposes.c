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
typedef  int PurposeSelection ;
typedef  int /*<<< orphan*/  HWND ;

/* Variables and functions */
 int /*<<< orphan*/  EnableWindow (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  FALSE ; 
 int /*<<< orphan*/  GetDlgItem (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  IDC_ADD_PURPOSE ; 
 int /*<<< orphan*/  IDC_CERTIFICATE_USAGES ; 
#define  PurposeDisableAll 130 
#define  PurposeEnableAll 129 
#define  PurposeEnableSelected 128 
 int /*<<< orphan*/  TRUE ; 
 int /*<<< orphan*/  redraw_states (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void select_purposes(HWND hwnd, PurposeSelection selection)
{
    HWND lv = GetDlgItem(hwnd, IDC_CERTIFICATE_USAGES);

    switch (selection)
    {
    case PurposeEnableAll:
    case PurposeDisableAll:
        EnableWindow(lv, FALSE);
        redraw_states(lv, FALSE);
        EnableWindow(GetDlgItem(hwnd, IDC_ADD_PURPOSE), FALSE);
        break;
    case PurposeEnableSelected:
        EnableWindow(lv, TRUE);
        redraw_states(lv, TRUE);
        EnableWindow(GetDlgItem(hwnd, IDC_ADD_PURPOSE), TRUE);
    }
}
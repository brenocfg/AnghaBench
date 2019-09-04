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
typedef  int UINT ;
typedef  int /*<<< orphan*/  HWND ;
typedef  int /*<<< orphan*/  BOOL ;

/* Variables and functions */
 int BST_UNCHECKED ; 
 int /*<<< orphan*/  CheckDlgButton (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  EnableWindow (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  GetDlgItem (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  IDC_EXTENDED_LABEL ; 
 int IsChecked (int /*<<< orphan*/ ) ; 
 scalar_t__ IsWindowEnabled (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  hMainDialog ; 

__attribute__((used)) static void EnableExtendedLabel(BOOL enable)
{
	HWND hCtrl = GetDlgItem(hMainDialog, IDC_EXTENDED_LABEL);
	static UINT checked, state = 0;

	if (!enable && IsWindowEnabled(hCtrl) && (state != 1)) {
		checked = IsChecked(IDC_EXTENDED_LABEL);
		CheckDlgButton(hMainDialog, IDC_EXTENDED_LABEL, BST_UNCHECKED);
		state = 1;
	} else if (enable && !IsWindowEnabled(hCtrl) && (state != 2)) {
		if (state != 0)
			CheckDlgButton(hMainDialog, IDC_EXTENDED_LABEL, checked);
		state = 2;
	}
	EnableWindow(hCtrl, enable);
}
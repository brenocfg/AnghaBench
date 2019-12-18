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
typedef  scalar_t__ BOOL ;

/* Variables and functions */
 int BST_UNCHECKED ; 
 scalar_t__ BT_IMAGE ; 
 int /*<<< orphan*/  CheckDlgButton (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  EnableWindow (int /*<<< orphan*/ ,scalar_t__) ; 
 scalar_t__ FALSE ; 
 scalar_t__ FS_EXT2 ; 
 int /*<<< orphan*/  GetDlgItem (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  IDC_EXTENDED_LABEL ; 
 scalar_t__ IS_DD_ONLY (int /*<<< orphan*/ ) ; 
 int IsChecked (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  IsWindowEnabled (int /*<<< orphan*/ ) ; 
 scalar_t__ boot_type ; 
 scalar_t__ fs_type ; 
 int /*<<< orphan*/  hMainDialog ; 
 int /*<<< orphan*/  img_report ; 

__attribute__((used)) static void EnableExtendedLabel(BOOL enable, BOOL remove_checkboxes)
{
	static UINT checked, state = 0;
	HWND hCtrl = GetDlgItem(hMainDialog, IDC_EXTENDED_LABEL);

	if ((fs_type >= FS_EXT2) || ((boot_type == BT_IMAGE) && IS_DD_ONLY(img_report)))
		enable = FALSE;

	if (remove_checkboxes) {
		if (!enable && (state != 1)) {
			checked = IsChecked(IDC_EXTENDED_LABEL);
			CheckDlgButton(hMainDialog, IDC_EXTENDED_LABEL, BST_UNCHECKED);
			state = 1;
		} else if (enable && !IsWindowEnabled(hCtrl) && (state != 2)) {
			if (state != 0)
				CheckDlgButton(hMainDialog, IDC_EXTENDED_LABEL, checked);
			state = 2;
		}
	}
	EnableWindow(hCtrl, enable);
}
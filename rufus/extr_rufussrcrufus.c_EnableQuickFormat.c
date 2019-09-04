#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct TYPE_2__ {scalar_t__ DiskSize; } ;
typedef  int /*<<< orphan*/  HWND ;
typedef  scalar_t__ BOOL ;

/* Variables and functions */
 int /*<<< orphan*/  BST_CHECKED ; 
 int /*<<< orphan*/  CheckDlgButton (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  EnableWindow (int /*<<< orphan*/ ,scalar_t__) ; 
 scalar_t__ FALSE ; 
 scalar_t__ FS_FAT32 ; 
 scalar_t__ FS_REFS ; 
 int /*<<< orphan*/  GetDlgItem (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  IDC_QUICK_FORMAT ; 
 int /*<<< orphan*/  IsChecked (int /*<<< orphan*/ ) ; 
 scalar_t__ IsWindowEnabled (int /*<<< orphan*/ ) ; 
 scalar_t__ LARGE_FAT32_SIZE ; 
 TYPE_1__ SelectedDrive ; 
 scalar_t__ force_large_fat32 ; 
 scalar_t__ fs_type ; 
 int /*<<< orphan*/  hMainDialog ; 
 int /*<<< orphan*/  uQFChecked ; 

__attribute__((used)) static void EnableQuickFormat(BOOL enable)
{
	HWND hCtrl = GetDlgItem(hMainDialog, IDC_QUICK_FORMAT);

	// Keep track of the current state if we are going to disable it
	if (IsWindowEnabled(hCtrl) && !enable) {
		uQFChecked = IsChecked(IDC_QUICK_FORMAT);
	}

	// Disable/restore the quick format control depending on large FAT32 or ReFS
	if (((fs_type == FS_FAT32) && ((SelectedDrive.DiskSize > LARGE_FAT32_SIZE) || (force_large_fat32))) || (fs_type == FS_REFS)) {
		enable = FALSE;
		CheckDlgButton(hMainDialog, IDC_QUICK_FORMAT, BST_CHECKED);
	}

	// Restore state if we are re-enabling the control
	if (!IsWindowEnabled(hCtrl) && enable) {
		CheckDlgButton(hMainDialog, IDC_QUICK_FORMAT, uQFChecked);
	}

	// Now enable or disable the control
	EnableWindow(hCtrl, enable);
}
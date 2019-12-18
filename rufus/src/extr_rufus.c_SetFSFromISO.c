#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_9__   TYPE_1__ ;

/* Type definitions */
typedef  int uint32_t ;
struct TYPE_9__ {scalar_t__ has_4GB_file; } ;
typedef  int BOOL ;

/* Variables and functions */
 scalar_t__ BT_IMAGE ; 
 int CBN_SELCHANGE_INTERNAL ; 
 int ComboBox_GetCount (int /*<<< orphan*/ ) ; 
 int ComboBox_GetCurSel (int /*<<< orphan*/ ) ; 
 scalar_t__ ComboBox_GetItemData (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  ComboBox_SetCurSel (int /*<<< orphan*/ ,int) ; 
 int FS_FAT16 ; 
 int FS_FAT32 ; 
 int FS_NTFS ; 
 int FS_UNKNOWN ; 
 int /*<<< orphan*/  GetDlgItem (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ HAS_BOOTMGR (TYPE_1__) ; 
 scalar_t__ HAS_KOLIBRIOS (TYPE_1__) ; 
 scalar_t__ HAS_REACTOS (TYPE_1__) ; 
 scalar_t__ HAS_SYSLINUX (TYPE_1__) ; 
 scalar_t__ HAS_WINPE (TYPE_1__) ; 
 scalar_t__ HAS_WINTOGO (TYPE_1__) ; 
 int IDC_FILE_SYSTEM ; 
 int /*<<< orphan*/  IDC_IMAGE_OPTION ; 
 int /*<<< orphan*/  IGNORE_RETVAL (int /*<<< orphan*/ ) ; 
 int IMOP_WINTOGO ; 
 scalar_t__ IS_EFI_BOOTABLE (TYPE_1__) ; 
 int /*<<< orphan*/  SendMessage (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,int) ; 
 scalar_t__ TT_UEFI ; 
 int /*<<< orphan*/  WM_COMMAND ; 
 scalar_t__ boot_type ; 
 int /*<<< orphan*/  hFileSystem ; 
 int /*<<< orphan*/  hMainDialog ; 
 int image_options ; 
 int /*<<< orphan*/ * image_path ; 
 TYPE_1__ img_report ; 
 int preselected_fs ; 
 int selected_fs ; 
 scalar_t__ target_type ; 

__attribute__((used)) static void SetFSFromISO(void)
{
	int i, fs_tmp, preferred_fs = FS_UNKNOWN;
	uint32_t fs_mask = FS_FAT32 | FS_NTFS;
	BOOL windows_to_go = (image_options & IMOP_WINTOGO) && (boot_type == BT_IMAGE) && HAS_WINTOGO(img_report) &&
		(ComboBox_GetCurSel(GetDlgItem(hMainDialog, IDC_IMAGE_OPTION)) == 1);

	if (image_path == NULL)
		return;

	// Create a mask of all the FS's available
	for (i=0; i<ComboBox_GetCount(hFileSystem); i++) {
		fs_tmp = (int)ComboBox_GetItemData(hFileSystem, i);
		fs_mask |= 1<<fs_tmp;
	}

	if ((preferred_fs == FS_UNKNOWN) && (preselected_fs != FS_UNKNOWN)) {
		// If the FS requested from the command line is valid use it
		if (fs_mask & (1 << preselected_fs)) {
			preferred_fs = preselected_fs;
		}
	}

	if (preferred_fs == FS_UNKNOWN) {
		// Syslinux and EFI have precedence over bootmgr (unless the user selected BIOS as target type)
		if ((HAS_SYSLINUX(img_report)) || (HAS_REACTOS(img_report)) || HAS_KOLIBRIOS(img_report) ||
			(IS_EFI_BOOTABLE(img_report) && (target_type == TT_UEFI) && (!windows_to_go))) {
			if (fs_mask & (1 << FS_FAT32)) {
				preferred_fs = FS_FAT32;
			} else if ((fs_mask & (1 << FS_FAT16)) && !HAS_KOLIBRIOS(img_report)) {
				preferred_fs = FS_FAT16;
			}
		} else if ((windows_to_go) || HAS_BOOTMGR(img_report) || HAS_WINPE(img_report)) {
			if (fs_mask & (1 << FS_NTFS)) {
				preferred_fs = FS_NTFS;
			}
		}
	}

	// The presence of a 4GB file forces the use of NTFS as default FS if available
	if (img_report.has_4GB_file && (fs_mask & (1 << FS_NTFS))) {
		preferred_fs = FS_NTFS;
	}

	// Try to select the FS
	for (i = 0; i < ComboBox_GetCount(hFileSystem); i++) {
		fs_tmp = (int)ComboBox_GetItemData(hFileSystem, i);
		if (fs_tmp == preferred_fs) {
			IGNORE_RETVAL(ComboBox_SetCurSel(hFileSystem, i));
			break;
		}
	}
	if (selected_fs == FS_UNKNOWN)
		selected_fs = preferred_fs;

	SendMessage(hMainDialog, WM_COMMAND, (CBN_SELCHANGE_INTERNAL<<16) | IDC_FILE_SYSTEM,
		ComboBox_GetCurSel(hFileSystem));
}
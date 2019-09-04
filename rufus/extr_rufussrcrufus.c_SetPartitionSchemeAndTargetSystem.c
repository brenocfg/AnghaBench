#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_2__ ;
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
struct TYPE_8__ {int DiskSize; int PartitionStyle; } ;
struct TYPE_7__ {scalar_t__ is_bootable_img; scalar_t__ has_efi; scalar_t__ is_iso; } ;
typedef  int BOOL ;

/* Variables and functions */
#define  BT_FREEDOS 137 
#define  BT_GRUB2 136 
#define  BT_GRUB4DOS 135 
#define  BT_IMAGE 134 
#define  BT_MSDOS 133 
#define  BT_NON_BOOTABLE 132 
#define  BT_REACTOS 131 
#define  BT_SYSLINUX_V4 130 
#define  BT_SYSLINUX_V6 129 
#define  BT_UEFI_NTFS 128 
 int /*<<< orphan*/  ComboBox_AddStringU (int /*<<< orphan*/ ,char*) ; 
 int ComboBox_GetCurSel (int /*<<< orphan*/ ) ; 
 scalar_t__ ComboBox_GetItemData (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  ComboBox_ResetContent (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ComboBox_SetCurSel (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ComboBox_SetItemData (int /*<<< orphan*/ ,int /*<<< orphan*/ ,size_t) ; 
 int FALSE ; 
 int /*<<< orphan*/  GetDlgItem (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ HAS_WINDOWS (TYPE_1__) ; 
 scalar_t__ HAS_WINTOGO (TYPE_1__) ; 
 int /*<<< orphan*/  IDC_IMAGE_OPTION ; 
 int /*<<< orphan*/  IGNORE_RETVAL (int /*<<< orphan*/ ) ; 
 scalar_t__ IS_BIOS_BOOTABLE (TYPE_1__) ; 
 scalar_t__ IS_EFI_BOOTABLE (TYPE_1__) ; 
 int /*<<< orphan*/  MSG_031 ; 
 int /*<<< orphan*/  MSG_032 ; 
 int /*<<< orphan*/  MSG_033 ; 
 size_t PARTITION_STYLE_GPT ; 
 size_t PARTITION_STYLE_MBR ; 
 size_t PARTITION_STYLE_SFD ; 
 TYPE_2__ SelectedDrive ; 
 int /*<<< orphan*/  SendMessage (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  SetComboEntry (int /*<<< orphan*/ ,int) ; 
 int TB ; 
 int TRUE ; 
 size_t TT_BIOS ; 
 size_t TT_UEFI ; 
 int /*<<< orphan*/  UM_UPDATE_CSM_TOOLTIP ; 
 scalar_t__ allow_dual_uefi_bios ; 
 int boot_type ; 
 int /*<<< orphan*/  hBootType ; 
 int /*<<< orphan*/  hDeviceList ; 
 int /*<<< orphan*/  hMainDialog ; 
 int /*<<< orphan*/  hPartitionScheme ; 
 int /*<<< orphan*/  hTargetSystem ; 
 int has_uefi_csm ; 
 int /*<<< orphan*/ * image_path ; 
 TYPE_1__ img_report ; 
 char* lmprintf (int /*<<< orphan*/ ) ; 
 size_t partition_type ; 
 size_t selected_pt ; 
 char* sfd_name ; 
 int target_type ; 

__attribute__((used)) static void SetPartitionSchemeAndTargetSystem(BOOL only_target)
{
	//                                   MBR,  GPT,  SFD
	BOOL allowed_partition_scheme[3] = { TRUE, TRUE, FALSE };
	//                                   BIOS, UEFI, DUAL
	BOOL allowed_target_system[3]    = { TRUE, TRUE, FALSE };
	BOOL is_windows_to_go_selected;

	if (!only_target)
		IGNORE_RETVAL(ComboBox_ResetContent(hPartitionScheme));
	IGNORE_RETVAL(ComboBox_ResetContent(hTargetSystem));

	boot_type = (int)ComboBox_GetItemData(hBootType, ComboBox_GetCurSel(hBootType));
	is_windows_to_go_selected = (boot_type == BT_IMAGE) && (image_path != NULL) && HAS_WINTOGO(img_report) &&
		(ComboBox_GetCurSel(GetDlgItem(hMainDialog, IDC_IMAGE_OPTION)) == 1);
	// If no device is selected, don't populate anything
	if (ComboBox_GetCurSel(hDeviceList) < 0)
		return;
	switch (boot_type) {
	case BT_NON_BOOTABLE:
		allowed_partition_scheme[PARTITION_STYLE_SFD] = TRUE;
		allowed_target_system[0] = FALSE;
		allowed_target_system[1] = FALSE;
		allowed_target_system[2] = TRUE;
		break;
	case BT_IMAGE:
		if (image_path == NULL)
			break;
		// Check if image is EFI bootable
		if (!IS_EFI_BOOTABLE(img_report)) {
			allowed_partition_scheme[PARTITION_STYLE_GPT] = FALSE;
			allowed_target_system[1] = FALSE;
			break;
		}
		// Image is EFI bootable => set dual BIOS + UEFI and so on...
		if (IS_BIOS_BOOTABLE(img_report)) {
			if (!HAS_WINDOWS(img_report) || allow_dual_uefi_bios || is_windows_to_go_selected) {
				allowed_target_system[0] = FALSE;
				allowed_target_system[1] = TRUE;
				allowed_target_system[2] = TRUE;
			}
		} else {
			allowed_target_system[0] = FALSE;
		}
		break;
	case BT_MSDOS:
	case BT_FREEDOS:
	case BT_SYSLINUX_V4:
	case BT_SYSLINUX_V6:
	case BT_REACTOS:
	case BT_GRUB4DOS:
	case BT_GRUB2:
		allowed_partition_scheme[PARTITION_STYLE_GPT] = FALSE;
		allowed_target_system[1] = FALSE;
		break;
	case BT_UEFI_NTFS:
		allowed_target_system[0] = FALSE;
		break;
	}

	if (!only_target) {
		// Override partition type selection to GPT for drives larger than 2TB
		if (SelectedDrive.DiskSize > 2 * TB)
			selected_pt = PARTITION_STYLE_GPT;
		// Try to reselect the current drive's partition scheme
		int preferred_pt = SelectedDrive.PartitionStyle;
		if (allowed_partition_scheme[PARTITION_STYLE_MBR]) 
			IGNORE_RETVAL(ComboBox_SetItemData(hPartitionScheme,
				ComboBox_AddStringU(hPartitionScheme, "MBR"), PARTITION_STYLE_MBR));
		if (allowed_partition_scheme[PARTITION_STYLE_GPT])
			IGNORE_RETVAL(ComboBox_SetItemData(hPartitionScheme,
				ComboBox_AddStringU(hPartitionScheme, "GPT"), PARTITION_STYLE_GPT));
		if (allowed_partition_scheme[PARTITION_STYLE_SFD])
			IGNORE_RETVAL(ComboBox_SetItemData(hPartitionScheme,
				ComboBox_AddStringU(hPartitionScheme, sfd_name), PARTITION_STYLE_SFD));
		// Override the partition scheme according to the current 
		if (boot_type == BT_NON_BOOTABLE)
			preferred_pt = (selected_pt >= 0) ? selected_pt : PARTITION_STYLE_MBR;
		else if (boot_type == BT_UEFI_NTFS)
			preferred_pt = (selected_pt >= 0) ? selected_pt : PARTITION_STYLE_GPT;
		else if ((boot_type == BT_IMAGE) && (image_path != NULL) && (img_report.is_iso)) {
			if (HAS_WINDOWS(img_report) && img_report.has_efi)
				preferred_pt = allow_dual_uefi_bios? PARTITION_STYLE_MBR :
					((selected_pt >= 0) ? selected_pt : PARTITION_STYLE_GPT);
			if (img_report.is_bootable_img)
				preferred_pt = (selected_pt >= 0) ? selected_pt : PARTITION_STYLE_MBR;
		}
		SetComboEntry(hPartitionScheme, preferred_pt);
		partition_type = (int)ComboBox_GetItemData(hPartitionScheme, ComboBox_GetCurSel(hPartitionScheme));
	}

	has_uefi_csm = FALSE;
	if (allowed_target_system[0] && (partition_type != PARTITION_STYLE_GPT)) {
		IGNORE_RETVAL(ComboBox_SetItemData(hTargetSystem,
			ComboBox_AddStringU(hTargetSystem, lmprintf(MSG_031)), TT_BIOS));
		has_uefi_csm = TRUE;
	}
	if (allowed_target_system[1] && !((partition_type == PARTITION_STYLE_MBR) && (boot_type == BT_IMAGE) && IS_BIOS_BOOTABLE(img_report) && IS_EFI_BOOTABLE(img_report)) )
		IGNORE_RETVAL(ComboBox_SetItemData(hTargetSystem,
			ComboBox_AddStringU(hTargetSystem, lmprintf(MSG_032)), TT_UEFI));
	if (allowed_target_system[2] && ((partition_type != PARTITION_STYLE_GPT) || (boot_type == BT_NON_BOOTABLE)))
		IGNORE_RETVAL(ComboBox_SetItemData(hTargetSystem,
			ComboBox_AddStringU(hTargetSystem, lmprintf(MSG_033)), TT_BIOS));
	IGNORE_RETVAL(ComboBox_SetCurSel(hTargetSystem, 0));
	target_type = (int)ComboBox_GetItemData(hTargetSystem, ComboBox_GetCurSel(hTargetSystem));
	// Can't update a tooltip from a thread, so we send a message instead
	SendMessage(hMainDialog, UM_UPDATE_CSM_TOOLTIP, 0, 0);
}
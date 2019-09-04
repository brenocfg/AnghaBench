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
typedef  int /*<<< orphan*/  WPARAM ;
struct TYPE_2__ {int /*<<< orphan*/  is_iso; } ;
typedef  int /*<<< orphan*/  LPARAM ;
typedef  int BOOL ;

/* Variables and functions */
 scalar_t__ BT_IMAGE ; 
 scalar_t__ ComboBox_GetCurSel (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  EnableBootOptions (int,int) ; 
 int /*<<< orphan*/  EnableWindow (int /*<<< orphan*/ ,int) ; 
 int FALSE ; 
 int /*<<< orphan*/  GetDlgItem (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  IDCANCEL ; 
 scalar_t__ IDC_ABOUT ; 
 int /*<<< orphan*/  IDC_IMAGE_OPTION ; 
 scalar_t__ IDC_LANG ; 
 int /*<<< orphan*/  IDC_LIST_USB_HDD ; 
 scalar_t__ IDC_SETTINGS ; 
 int /*<<< orphan*/  IDS_CSM_HELP_TXT ; 
 int /*<<< orphan*/  SendMessage (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  SetDlgItemTextU (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  TB_ENABLEBUTTON ; 
 scalar_t__ boot_type ; 
 int /*<<< orphan*/  hAdvancedDeviceToolbar ; 
 int /*<<< orphan*/  hAdvancedFormatToolbar ; 
 int /*<<< orphan*/  hBootType ; 
 int /*<<< orphan*/  hClusterSize ; 
 int /*<<< orphan*/  hDeviceList ; 
 int /*<<< orphan*/  hFileSystem ; 
 int /*<<< orphan*/  hHashToolbar ; 
 int /*<<< orphan*/  hMainDialog ; 
 int /*<<< orphan*/  hMultiToolbar ; 
 int /*<<< orphan*/  hPartitionScheme ; 
 int /*<<< orphan*/  hSaveToolbar ; 
 int /*<<< orphan*/  hSelectImage ; 
 int /*<<< orphan*/  hStart ; 
 int /*<<< orphan*/  hTargetSystem ; 
 int /*<<< orphan*/ * image_path ; 
 TYPE_1__ img_report ; 
 int /*<<< orphan*/  uppercase_cancel ; 
 int /*<<< orphan*/  uppercase_close ; 

__attribute__((used)) static void EnableControls(BOOL bEnable)
{
	// The following only get disabled on format/checksum and otherwise remain enabled,
	// even if no device or image are selected
	EnableWindow(hDeviceList, bEnable);
	EnableWindow(hBootType, bEnable);
	EnableWindow(hSelectImage, bEnable);
	EnableWindow(GetDlgItem(hMainDialog, IDC_LIST_USB_HDD), bEnable);
	EnableWindow(hAdvancedDeviceToolbar, bEnable);
	EnableWindow(hAdvancedFormatToolbar, bEnable);
	SendMessage(hMultiToolbar, TB_ENABLEBUTTON, (WPARAM)IDC_LANG, (LPARAM)bEnable);
	SendMessage(hMultiToolbar, TB_ENABLEBUTTON, (WPARAM)IDC_ABOUT, (LPARAM)bEnable);
	SendMessage(hMultiToolbar, TB_ENABLEBUTTON, (WPARAM)IDC_SETTINGS, (LPARAM)bEnable);

	// Checksum button is enabled if an image has been selected
	EnableWindow(hHashToolbar, bEnable && (boot_type == BT_IMAGE) && (image_path != NULL));

	// Toggle CLOSE/CANCEL
	SetDlgItemTextU(hMainDialog, IDCANCEL, bEnable ? uppercase_close : uppercase_cancel);

	// Only enable the following controls if a device is active
	bEnable = (ComboBox_GetCurSel(hDeviceList) < 0) ? FALSE : bEnable;
	EnableWindow(GetDlgItem(hMainDialog, IDC_IMAGE_OPTION), bEnable);
	EnableWindow(hSaveToolbar, bEnable);

	// Enable or disable the Start button and the other boot options
	bEnable = ((boot_type == BT_IMAGE) && (image_path == NULL)) ? FALSE : bEnable;
	EnableWindow(hStart, bEnable);
	EnableBootOptions(bEnable, FALSE);

	// Finally, only enable the half-size dropdowns if we aren't dealing with a pure DD image
	bEnable = ((boot_type == BT_IMAGE) && (image_path != NULL) && (!img_report.is_iso)) ? FALSE : bEnable;
	EnableWindow(hPartitionScheme, bEnable);
	EnableWindow(hTargetSystem, bEnable);
	EnableWindow(GetDlgItem(hMainDialog, IDS_CSM_HELP_TXT), bEnable);
	EnableWindow(hFileSystem, bEnable);
	EnableWindow(hClusterSize, bEnable);
}
#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
typedef  int uint64_t ;
typedef  int /*<<< orphan*/  WPARAM ;
struct TYPE_4__ {int DiskSize; } ;
struct TYPE_3__ {int projected_size; } ;
typedef  int /*<<< orphan*/  LPARAM ;
typedef  int LONGLONG ;
typedef  int /*<<< orphan*/  HWND ;

/* Variables and functions */
 int /*<<< orphan*/  ComboBox_AddStringU (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ ComboBox_GetCurSel (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ComboBox_ResetContent (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ComboBox_SetCurSel (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  ComboBox_SetItemData (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  GetDlgItem (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  IDC_PERSISTENCE_SLIDER ; 
 int /*<<< orphan*/  IDC_PERSISTENCE_UNITS ; 
 int /*<<< orphan*/  IGNORE_RETVAL (int /*<<< orphan*/ ) ; 
 int MB ; 
 scalar_t__ MSG_022 ; 
 TYPE_2__ SelectedDrive ; 
 int /*<<< orphan*/  SendMessage (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  SetPersistencePos (int) ; 
 int /*<<< orphan*/  TBM_SETPOS ; 
 int /*<<< orphan*/  TBM_SETRANGEMAX ; 
 int /*<<< orphan*/  TBM_SETRANGEMIN ; 
 scalar_t__ TRUE ; 
 int /*<<< orphan*/  hDeviceList ; 
 int /*<<< orphan*/  hMainDialog ; 
 TYPE_1__ img_report ; 
 int /*<<< orphan*/  lmprintf (scalar_t__) ; 
 int min (int,int) ; 
 int persistence_size ; 
 int persistence_unit_selection ; 

void SetPersistenceSize(void)
{
	int i, proposed_unit_selection = 0;
	LONGLONG base_unit = MB;
	HWND hCtrl;
	uint64_t max = 0, pos = 0;

	if (ComboBox_GetCurSel(hDeviceList) >= 0) {
		max = SelectedDrive.DiskSize - img_report.projected_size;
		persistence_size = min(persistence_size, max);
		pos = persistence_size;

		// Reset the the Persistence Units dropdown
		hCtrl = GetDlgItem(hMainDialog, IDC_PERSISTENCE_UNITS);
		IGNORE_RETVAL(ComboBox_ResetContent(hCtrl));
		for (i = 0; i < 3; i++) {
			IGNORE_RETVAL(ComboBox_SetItemData(hCtrl, ComboBox_AddStringU(hCtrl, lmprintf(MSG_022 + i)), i));
			// If we have more than 7 discrete positions, set this unit as our base
			if (SelectedDrive.DiskSize > 7 * base_unit)
				proposed_unit_selection = i;
			base_unit *= 1024;
			// Don't allow a base unit unless the drive is at least twice the size of that unit
			if (SelectedDrive.DiskSize < 2 * base_unit)
				break;
		}
		if (persistence_unit_selection < 0)
			persistence_unit_selection = proposed_unit_selection;

		IGNORE_RETVAL(ComboBox_SetCurSel(hCtrl, persistence_unit_selection));
		pos /= MB;
		max /= MB;
		for (i = 0; i < persistence_unit_selection; i++) {
			pos /= 1024;
			max /= 1024;
		}
	}

	hCtrl = GetDlgItem(hMainDialog, IDC_PERSISTENCE_SLIDER);
	// Wow! Unless you set *all* these redraw WPARAMs to true, the one from
	// TBM_SETPOS gets completely ignored if the value is zero!
	SendMessage(hCtrl, TBM_SETRANGEMIN, (WPARAM)TRUE, (LPARAM)0);
	SendMessage(hCtrl, TBM_SETRANGEMAX, (WPARAM)TRUE, (LPARAM)max);
	SendMessage(hCtrl, TBM_SETPOS, (WPARAM)TRUE, (LPARAM)pos);

	SetPersistencePos(pos);
}
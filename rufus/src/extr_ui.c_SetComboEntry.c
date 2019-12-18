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
typedef  int /*<<< orphan*/  HWND ;

/* Variables and functions */
 int ComboBox_GetCount (int /*<<< orphan*/ ) ; 
 int ComboBox_GetItemData (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  ComboBox_SetCurSel (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  IGNORE_RETVAL (int /*<<< orphan*/ ) ; 

void SetComboEntry(HWND hDlg, int data)
{
	int i, nb_entries = ComboBox_GetCount(hDlg);

	if (nb_entries <= 0)
		return;
	for (i = 0; i < nb_entries; i++) {
		if (ComboBox_GetItemData(hDlg, i) == data) {
			IGNORE_RETVAL(ComboBox_SetCurSel(hDlg, i));
			return;
		}
	}
	if (i == nb_entries)
		IGNORE_RETVAL(ComboBox_SetCurSel(hDlg, 0));
}
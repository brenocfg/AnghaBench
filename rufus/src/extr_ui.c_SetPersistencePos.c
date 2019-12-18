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
typedef  scalar_t__ uint64_t ;
typedef  int /*<<< orphan*/  LONG ;

/* Variables and functions */
 scalar_t__ BT_IMAGE ; 
 int /*<<< orphan*/  FALSE ; 
 int /*<<< orphan*/  GetDlgItem (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  IDC_PERSISTENCE_SIZE ; 
 int /*<<< orphan*/  MSG_124 ; 
 int /*<<< orphan*/  SetWindowTextU (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  TRUE ; 
 int /*<<< orphan*/  TogglePersistenceControls (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  app_changed_size ; 
 scalar_t__ boot_type ; 
 int /*<<< orphan*/  hMainDialog ; 
 int /*<<< orphan*/  lmprintf (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  static_sprintf (char*,char*,int /*<<< orphan*/ ) ; 

void SetPersistencePos(uint64_t pos)
{
	char tmp[64];

	if ((boot_type == BT_IMAGE) && (pos != 0)) {
		TogglePersistenceControls(TRUE);
		static_sprintf(tmp, "%ld", (LONG)pos);
	} else {
		TogglePersistenceControls(FALSE);
		static_sprintf(tmp, "0 (%s)", lmprintf(MSG_124));
	}
	app_changed_size = TRUE;
	SetWindowTextU(GetDlgItem(hMainDialog, IDC_PERSISTENCE_SIZE), tmp);
}
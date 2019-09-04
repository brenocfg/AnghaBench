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
typedef  int ULONG ;
struct TYPE_4__ {TYPE_1__* ClusterSize; } ;
struct TYPE_3__ {int Allowed; int Default; } ;
typedef  int /*<<< orphan*/  BOOL ;

/* Variables and functions */
 char** ClusterSizeLabel ; 
 int /*<<< orphan*/  ComboBox_AddStringU (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  ComboBox_ResetContent (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ComboBox_SetCurSel (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  ComboBox_SetItemData (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  FALSE ; 
 int FS_MAX ; 
 int /*<<< orphan*/  IGNORE_RETVAL (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  MSG_030 ; 
 TYPE_2__ SelectedDrive ; 
 int /*<<< orphan*/  TRUE ; 
 int /*<<< orphan*/  hClusterSize ; 
 char* lmprintf (int /*<<< orphan*/ ,char*) ; 

__attribute__((used)) static BOOL SetClusterSizes(int FSType)
{
	char* szClustSize;
	int i, k, default_index = 0;
	ULONG j;

	IGNORE_RETVAL(ComboBox_ResetContent(hClusterSize));

	if ((FSType < 0) || (FSType >= FS_MAX)) {
		return FALSE;
	}

	if ((SelectedDrive.ClusterSize[FSType].Allowed == 0)
		|| (SelectedDrive.ClusterSize[FSType].Default == 0)) {
		return FALSE;
	}

	for (i = 0, j = 0x100, k = 0; j<0x10000000; i++, j <<= 1) {
		if (j & SelectedDrive.ClusterSize[FSType].Allowed) {
			if (j == SelectedDrive.ClusterSize[FSType].Default) {
				szClustSize = lmprintf(MSG_030, ClusterSizeLabel[i]);
				default_index = k;
			} else {
				szClustSize = ClusterSizeLabel[i];
			}
			IGNORE_RETVAL(ComboBox_SetItemData(hClusterSize, ComboBox_AddStringU(hClusterSize, szClustSize), j));
			k++;
		}
	}

	IGNORE_RETVAL(ComboBox_SetCurSel(hClusterSize, default_index));
	return TRUE;
}
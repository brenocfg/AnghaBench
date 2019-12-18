#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_3__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_5__ {scalar_t__ cx; } ;
struct TYPE_4__ {scalar_t__ left; scalar_t__ right; } ;
typedef  TYPE_1__ RECT ;
typedef  int /*<<< orphan*/  POINT ;
typedef  int /*<<< orphan*/  HWND ;

/* Variables and functions */
 int /*<<< orphan*/  GetDlgItem (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 TYPE_3__ GetTextSize (int /*<<< orphan*/ ,char*) ; 
 scalar_t__ GetTextWidth (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  GetWindowRect (int /*<<< orphan*/ ,TYPE_1__*) ; 
 int /*<<< orphan*/  IDC_BAD_BLOCKS ; 
 int /*<<< orphan*/  IDC_CLUSTER_SIZE ; 
 int /*<<< orphan*/  IDC_PARTITION_TYPE ; 
 int /*<<< orphan*/  IDC_RUFUS_MBR ; 
 int /*<<< orphan*/  IDC_TARGET_SYSTEM ; 
 unsigned int MAX_CLUSTER_SIZES ; 
 unsigned int MSG_026 ; 
 int /*<<< orphan*/  MSG_030 ; 
 unsigned int MSG_031 ; 
 unsigned int MSG_033 ; 
 int /*<<< orphan*/  MSG_034 ; 
 int /*<<< orphan*/  MSG_035 ; 
 int /*<<< orphan*/  MSG_087 ; 
 int /*<<< orphan*/  MapWindowPoints (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int) ; 
 scalar_t__ ddw ; 
 int /*<<< orphan*/ * flash_type ; 
 scalar_t__ hw ; 
 char* lmprintf (unsigned int,...) ; 
 scalar_t__ max (scalar_t__,scalar_t__) ; 
 int /*<<< orphan*/  safe_sprintf (char*,int,char*,unsigned int,char*) ; 
 scalar_t__ sfd_name ; 
 scalar_t__ sw ; 

void GetHalfDropwdownWidth(HWND hDlg)
{
	RECT rc;
	unsigned int i, j, msg_id;
	char tmp[256];

	// Initialize half width to the UI's default size
	GetWindowRect(GetDlgItem(hDlg, IDC_PARTITION_TYPE), &rc);
	MapWindowPoints(NULL, hDlg, (POINT*)&rc, 2);
	hw = rc.right - rc.left - ddw;

	// "Super Floppy Disk" is the longuest entry in the Partition Scheme dropdown
	hw = max(hw, GetTextSize(GetDlgItem(hDlg, IDC_PARTITION_TYPE), (char*)sfd_name).cx);

	// This is basically the same as SetClusterSizeLabels() except we're adding (Default) to each entry
	for (i = 512, j = 1, msg_id = MSG_026; j<MAX_CLUSTER_SIZES; i <<= 1, j++) {
		if (i > 8192) {
			i /= 1024;
			msg_id++;
		}
		safe_sprintf(tmp, 64, "%d %s", i, lmprintf(msg_id));
		hw = max(hw, GetTextSize(GetDlgItem(hDlg, IDC_CLUSTER_SIZE), lmprintf(MSG_030, tmp)).cx);
	}
	// We don't go over file systems, because none of them will be longer than "Super Floppy Disk"
	// We do however go over the BIOS vs UEFI entries, as some of these are translated
	for (msg_id = MSG_031; msg_id <= MSG_033; msg_id++)
		hw = max(hw, GetTextSize(GetDlgItem(hDlg, IDC_TARGET_SYSTEM), lmprintf(msg_id)).cx);

	// Just in case, we also do the number of passes
	for (i = 1; i <= 5; i++) {
		char* msg = (i == 1) ? lmprintf(MSG_034, 1) : lmprintf(MSG_035, (i == 2) ? 2 : 4, (i == 2) ? "" : lmprintf(MSG_087, flash_type[i - 3]));
		hw = max(hw, GetTextSize(GetDlgItem(hDlg, IDC_TARGET_SYSTEM), msg).cx);
	}

	// Finally, we must ensure that we'll have enough space for the 2 checkbox controls
	// that end up with a half dropdown
	hw = max(hw, GetTextWidth(hDlg, IDC_RUFUS_MBR) - sw);
	hw = max(hw, GetTextWidth(hDlg, IDC_BAD_BLOCKS) - sw);

	// Add the width of a blank dropdown
	hw += ddw;
}
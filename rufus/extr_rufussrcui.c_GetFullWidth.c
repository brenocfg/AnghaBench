#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_3__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct TYPE_6__ {int cx; } ;
struct TYPE_5__ {int right; int left; } ;
typedef  TYPE_1__ RECT ;
typedef  int /*<<< orphan*/  POINT ;
typedef  int /*<<< orphan*/  HWND ;

/* Variables and functions */
 int ARRAYSIZE (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  GetClientRect (int /*<<< orphan*/ ,TYPE_1__*) ; 
 int /*<<< orphan*/  GetDlgItem (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 TYPE_3__ GetTextSize (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int GetTextWidth (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  GetWindowRect (int /*<<< orphan*/ ,TYPE_1__*) ; 
 int /*<<< orphan*/  IDC_BOOT_SELECTION ; 
 int /*<<< orphan*/  IDC_IMAGE_OPTION ; 
 int /*<<< orphan*/  IDS_DEVICE_TXT ; 
 int /*<<< orphan*/  MSG_117 ; 
 int /*<<< orphan*/  MSG_118 ; 
 int /*<<< orphan*/  MSG_279 ; 
 int /*<<< orphan*/  MSG_280 ; 
 int /*<<< orphan*/  MSG_281 ; 
 int /*<<< orphan*/  MapWindowPoints (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int) ; 
 int bsw ; 
 int bw ; 
 int dbw ; 
 int ddw ; 
 int /*<<< orphan*/ * full_width_checkboxes ; 
 int fw ; 
 int /*<<< orphan*/  hBootType ; 
 int hw ; 
 int /*<<< orphan*/  lmprintf (int /*<<< orphan*/ ,...) ; 
 int max (int,int) ; 
 int sbw ; 
 int ssw ; 
 int sw ; 

void GetFullWidth(HWND hDlg)
{
	RECT rc;
	int i;

	// Get the dialog border width
	GetWindowRect(hDlg, &rc);
	dbw = rc.right - rc.left;
	GetClientRect(hDlg, &rc);
	dbw -= rc.right - rc.left;

	// Compute the minimum size needed for the Boot Selection dropdown
	GetWindowRect(GetDlgItem(hDlg, IDC_BOOT_SELECTION), &rc);
	MapWindowPoints(NULL, hDlg, (POINT*)&rc, 2);

	bsw = max(rc.right - rc.left, GetTextSize(hBootType, lmprintf(MSG_279)).cx + ddw);
	bsw = max(bsw, GetTextSize(hBootType, lmprintf(MSG_281, lmprintf(MSG_280))).cx + ddw);

	// Initialize full width to the UI's default size
	GetWindowRect(GetDlgItem(hDlg, IDS_DEVICE_TXT), &rc);
	MapWindowPoints(NULL, hDlg, (POINT*)&rc, 2);
	fw = rc.right - rc.left - ddw;

	// Go through the Image Options for Windows To Go
	fw = max(fw, GetTextSize(GetDlgItem(hDlg, IDC_IMAGE_OPTION), lmprintf(MSG_117)).cx);
	fw = max(fw, GetTextSize(GetDlgItem(hDlg, IDC_IMAGE_OPTION), lmprintf(MSG_118)).cx);

	// Now deal with full length checkbox lines
	for (i = 0; i<ARRAYSIZE(full_width_checkboxes); i++)
		fw = max(fw, GetTextWidth(hDlg, full_width_checkboxes[i]));

	// All of the above is for text only, so we need to add dd space
	fw += ddw;

	// Our min also needs to be longer than 2 half length dropdowns + spacer
	fw = max(fw, 2 * hw + sw);

	// Now that we have our minimum full width, adjust the button width if needed
	// Adjust according to min full width
	bw = max(bw, (fw - 2 * ssw - sw) / 4);
	// Adjust according to min boot selection width
	bw = max(bw, (bsw + sbw - sw) / 3);

	// Adjust according to min half width
	bw = max(bw, (hw / 2) - ssw);

	// Now that our button width is set, we can adjust the rest
	hw = max(hw, 2 * bw + ssw);
	fw = max(fw, 2 * hw + sw);

	bsw = max(bsw, fw - bw - 2 * ssw - sbw);

	// TODO: Also pick a few choice messages from info/status
}
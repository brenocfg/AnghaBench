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
struct TYPE_5__ {int cx; } ;
struct TYPE_4__ {int right; int left; int top; scalar_t__ bottom; } ;
typedef  TYPE_1__ RECT ;
typedef  int /*<<< orphan*/  POINT ;
typedef  int /*<<< orphan*/ * HWND ;

/* Variables and functions */
 int ARRAYSIZE (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  GW_HWNDPREV ; 
 int /*<<< orphan*/ * GetDlgItem (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * GetNextWindow (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 TYPE_3__ GetTextSize (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int GetTextWidth (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  GetWindowRect (int /*<<< orphan*/ *,TYPE_1__*) ; 
 int /*<<< orphan*/  IDCANCEL ; 
 int /*<<< orphan*/  IDC_CHECK_NOW ; 
 int /*<<< orphan*/  IDC_UPDATE_FREQUENCY ; 
 int /*<<< orphan*/  IDS_INCLUDE_BETAS_TXT ; 
 int /*<<< orphan*/  IDS_UPDATE_FREQUENCY_TXT ; 
 int /*<<< orphan*/  MSG_008 ; 
 int /*<<< orphan*/  MSG_009 ; 
 int /*<<< orphan*/  MSG_013 ; 
 int /*<<< orphan*/  MSG_014 ; 
 int /*<<< orphan*/  MSG_015 ; 
 int /*<<< orphan*/  MSG_016 ; 
 int /*<<< orphan*/  MSG_030 ; 
 int /*<<< orphan*/  MapWindowPoints (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  Reposition (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int,int) ; 
 int SWP_NOMOVE ; 
 int SWP_NOZORDER ; 
 int /*<<< orphan*/  SetWindowPos (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int,int,int,scalar_t__,int) ; 
 int cbw ; 
 scalar_t__ ddbh ; 
 int ddw ; 
 int /*<<< orphan*/  lmprintf (int /*<<< orphan*/ ,...) ; 
 int max (int,int) ; 
 int /*<<< orphan*/ * update_settings_reposition_ids ; 

__attribute__((used)) static void PositionControls(HWND hDlg)
{
	RECT rc;
	HWND hCtrl, hPrevCtrl;
	int i, ow, dw;	// original width, delta

	// Get the original size of the control
	GetWindowRect(GetDlgItem(hDlg, IDS_UPDATE_FREQUENCY_TXT), &rc);
	MapWindowPoints(NULL, hDlg, (POINT*)&rc, 2);
	ow = rc.right - rc.left;
	dw = GetTextWidth(hDlg, IDS_UPDATE_FREQUENCY_TXT) - ow;
	dw = max(dw, GetTextWidth(hDlg, IDS_INCLUDE_BETAS_TXT) - ow);
	if (dw > 0) {
		GetWindowRect(hDlg, &rc);
		SetWindowPos(hDlg, NULL, -1, -1, rc.right - rc.left + dw, rc.bottom - rc.top, SWP_NOMOVE | SWP_NOZORDER);
		for (i = 0; i < ARRAYSIZE(update_settings_reposition_ids); i++)
			Reposition(hDlg, update_settings_reposition_ids[i], (i < 4) ? 0 : dw, (i >= 4) ? 0 : dw);
	}

	hCtrl = GetDlgItem(hDlg, IDC_UPDATE_FREQUENCY);
	GetWindowRect(hCtrl, &rc);
	MapWindowPoints(NULL, hDlg, (POINT*)&rc, 2);
	ow = rc.right - rc.left;

	dw = GetTextSize(hCtrl, lmprintf(MSG_013)).cx;
	dw = max(dw, GetTextSize(hCtrl, lmprintf(MSG_030, lmprintf(MSG_014))).cx);
	dw = max(dw, GetTextSize(hCtrl, lmprintf(MSG_015)).cx);
	dw = max(dw, GetTextSize(hCtrl, lmprintf(MSG_016)).cx);
	dw = max(dw, GetTextSize(hCtrl, lmprintf(MSG_008)).cx);
	dw = max(dw, GetTextSize(hCtrl, lmprintf(MSG_009)).cx);
	dw -= ow - ddw;
	if (dw > 0) {
		GetWindowRect(hDlg, &rc);
		SetWindowPos(hDlg, NULL, -1, -1, rc.right - rc.left + dw, rc.bottom - rc.top, SWP_NOMOVE | SWP_NOZORDER);
		for (i = 0; i < ARRAYSIZE(update_settings_reposition_ids); i++) {
			if ((i >= 2) && (i <= 3))
				continue;
			Reposition(hDlg, update_settings_reposition_ids[i], (i < 6) ? 0 : dw, (i >= 6) ? 0 : dw);
		}
	}

	GetWindowRect(GetDlgItem(hDlg, IDC_CHECK_NOW), &rc);
	MapWindowPoints(NULL, hDlg, (POINT*)&rc, 2);
	ow = rc.right - rc.left;
	dw = GetTextWidth(hDlg, IDC_CHECK_NOW) - ow + cbw;
	dw = max(dw, GetTextWidth(hDlg, IDCANCEL) - ow + cbw);
	if (dw > 0) {
		GetWindowRect(hDlg, &rc);
		SetWindowPos(hDlg, NULL, -1, -1, rc.right - rc.left + dw, rc.bottom - rc.top, SWP_NOMOVE | SWP_NOZORDER);
		for (i = 0; i < ARRAYSIZE(update_settings_reposition_ids); i++) {
			if ((i >= 1) && (i <= 5))
				continue;
			Reposition(hDlg, update_settings_reposition_ids[i], 0, dw);
		}
	}
	hCtrl = GetDlgItem(hDlg, IDC_CHECK_NOW);
	GetWindowRect(hCtrl, &rc);
	MapWindowPoints(NULL, hDlg, (POINT*)&rc, 2);
	hPrevCtrl = GetNextWindow(hCtrl, GW_HWNDPREV);
	SetWindowPos(hCtrl, hPrevCtrl, rc.left, rc.top, rc.right - rc.left, ddbh, 0);
	hCtrl = GetDlgItem(hDlg, IDCANCEL);
	GetWindowRect(hCtrl, &rc);
	MapWindowPoints(NULL, hDlg, (POINT*)&rc, 2);
	hPrevCtrl = GetNextWindow(hCtrl, GW_HWNDPREV);
	SetWindowPos(hCtrl, hPrevCtrl, rc.left, rc.top, rc.right - rc.left, ddbh, 0);
}
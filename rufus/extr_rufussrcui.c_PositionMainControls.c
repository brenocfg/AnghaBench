#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  WPARAM ;
struct TYPE_6__ {int bottom; int top; int left; int right; } ;
struct TYPE_5__ {int cy; int cx; } ;
typedef  TYPE_1__ SIZE ;
typedef  TYPE_2__ RECT ;
typedef  int /*<<< orphan*/  POINT ;
typedef  int /*<<< orphan*/  LPARAM ;
typedef  int /*<<< orphan*/ * HWND ;
typedef  int DWORD ;

/* Variables and functions */
 int ARRAYSIZE (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  EnableWindow (int /*<<< orphan*/ *,scalar_t__) ; 
 scalar_t__ FALSE ; 
 int /*<<< orphan*/  GW_HWNDPREV ; 
 int /*<<< orphan*/ * GetDlgItem (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * GetNextWindow (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 TYPE_1__ GetTextSize (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  GetWindowRect (int /*<<< orphan*/ *,TYPE_2__*) ; 
 int /*<<< orphan*/ * HWND_TOP ; 
 int /*<<< orphan*/  IDC_ABOUT ; 
 int /*<<< orphan*/  IDC_BAD_BLOCKS ; 
 int /*<<< orphan*/  IDC_BOOT_SELECTION ; 
 int /*<<< orphan*/  IDC_DEVICE ; 
 int /*<<< orphan*/  IDC_HASH ; 
 int /*<<< orphan*/  IDC_IMAGE_OPTION ; 
 int /*<<< orphan*/  IDC_LABEL ; 
 int /*<<< orphan*/  IDC_LIST_USB_HDD ; 
 int /*<<< orphan*/  IDC_PERSISTENCE_SIZE ; 
 int /*<<< orphan*/  IDC_PERSISTENCE_SLIDER ; 
 int /*<<< orphan*/  IDC_PERSISTENCE_UNITS ; 
 int /*<<< orphan*/  IDC_QUICK_FORMAT ; 
 int /*<<< orphan*/  IDC_RUFUS_MBR ; 
 int /*<<< orphan*/  IDC_SAVE ; 
 int /*<<< orphan*/  IDS_BOOT_SELECTION_TXT ; 
 int /*<<< orphan*/  IDS_CSM_HELP_TXT ; 
 int /*<<< orphan*/  IDS_DEVICE_TXT ; 
 int /*<<< orphan*/  IDS_DRIVE_PROPERTIES_TXT ; 
 int /*<<< orphan*/  IDS_FORMAT_OPTIONS_TXT ; 
 int /*<<< orphan*/  IDS_STATUS_TXT ; 
 int /*<<< orphan*/  MAKELPARAM (int,int) ; 
 int /*<<< orphan*/  MapWindowPoints (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int) ; 
 int SWP_NOMOVE ; 
 int SWP_NOZORDER ; 
 int /*<<< orphan*/  SW_HIDE ; 
 scalar_t__ SendMessage (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  SetWindowPos (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int,int,int,int,int) ; 
 int /*<<< orphan*/  ShowWindow (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  TB_GETIDEALSIZE ; 
 int /*<<< orphan*/  TB_GETPADDING ; 
 int /*<<< orphan*/  TB_SETBUTTONSIZE ; 
 int /*<<< orphan*/  TB_SETPADDING ; 
 int advanced_device_section_height ; 
 int advanced_format_section_height ; 
 scalar_t__ advanced_mode_device ; 
 int /*<<< orphan*/  bh ; 
 int bsw ; 
 int bw ; 
 int dbw ; 
 int ddbh ; 
 int ddh ; 
 int /*<<< orphan*/ * full_width_controls ; 
 int fw ; 
 int /*<<< orphan*/ * hAdvancedFormatToolbar ; 
 int /*<<< orphan*/ * hBootType ; 
 int /*<<< orphan*/ * hDeviceList ; 
 int /*<<< orphan*/ * hHashToolbar ; 
 int /*<<< orphan*/ * hMainDialog ; 
 int /*<<< orphan*/ * hMultiToolbar ; 
 int /*<<< orphan*/ * hNBPasses ; 
 int /*<<< orphan*/ * hProgress ; 
 int /*<<< orphan*/ * hSaveToolbar ; 
 int /*<<< orphan*/ * hTargetSystem ; 
 int /*<<< orphan*/ * half_width_ids ; 
 int hw ; 
 int /*<<< orphan*/ * main_button_ids ; 
 int /*<<< orphan*/  max (int /*<<< orphan*/ ,int) ; 
 int mw ; 
 int rh ; 
 int sbw ; 
 int* section_vpos ; 
 int ssw ; 
 int sw ; 
 int tw ; 

void PositionMainControls(HWND hDlg)
{
	RECT rc;
	HWND hCtrl, hPrevCtrl;
	SIZE sz;
	DWORD padding;
	int i, x, button_fudge = 2;

	// Start by resizing the whole dialog
	GetWindowRect(hDlg, &rc);
	// Don't forget to add the dialog border width, since we resize the whole dialog
	SetWindowPos(hDlg, NULL, -1, -1, fw + 2 * mw + dbw, rc.bottom - rc.top, SWP_NOMOVE | SWP_NOZORDER);

	// Resize the height of the label, persistence size and progress bar to the height of standard dropdowns
	hCtrl = GetDlgItem(hDlg, IDC_DEVICE);
	GetWindowRect(hCtrl, &rc);
	MapWindowPoints(NULL, hDlg, (POINT*)&rc, 2);
	ddh = rc.bottom - rc.top;
	ddbh = ddh + button_fudge;
	bh = max(bh, ddbh);
	hCtrl = GetDlgItem(hDlg, IDC_LABEL);
	GetWindowRect(hCtrl, &rc);
	MapWindowPoints(NULL, hDlg, (POINT*)&rc, 2);
	SetWindowPos(hCtrl, hAdvancedFormatToolbar, rc.left, rc.top, rc.right - rc.left, ddh, SWP_NOZORDER);
	hCtrl = GetDlgItem(hDlg, IDC_PERSISTENCE_SIZE);
	GetWindowRect(hCtrl, &rc);
	MapWindowPoints(NULL, hDlg, (POINT*)&rc, 2);
	SetWindowPos(hCtrl, GetDlgItem(hDlg, IDC_PERSISTENCE_SLIDER), rc.left, rc.top, rc.right - rc.left, ddh, SWP_NOZORDER);
	GetWindowRect(hProgress, &rc);
	MapWindowPoints(NULL, hDlg, (POINT*)&rc, 2);
	SetWindowPos(hProgress, hNBPasses, rc.left, rc.top, rc.right - rc.left, ddh, SWP_NOZORDER);

	// Get the height of a typical row
	hCtrl = GetDlgItem(hDlg, IDS_BOOT_SELECTION_TXT);
	GetWindowRect(hCtrl, &rc);
	MapWindowPoints(NULL, hDlg, (POINT*)&rc, 2);
	rh = rc.top;
	hCtrl = GetDlgItem(hDlg, IDS_DEVICE_TXT);
	GetWindowRect(hCtrl, &rc);
	MapWindowPoints(NULL, hDlg, (POINT*)&rc, 2);
	rh -= rc.top;

	// Get the height of the advanced options
	hCtrl = GetDlgItem(hDlg, IDC_LIST_USB_HDD);
	GetWindowRect(hCtrl, &rc);
	MapWindowPoints(NULL, hDlg, (POINT*)&rc, 2);
	advanced_device_section_height = rc.top;
	hCtrl = GetDlgItem(hDlg, IDC_RUFUS_MBR);
	GetWindowRect(hCtrl, &rc);
	MapWindowPoints(NULL, hDlg, (POINT*)&rc, 2);
	advanced_device_section_height = rc.bottom - advanced_device_section_height;

	hCtrl = GetDlgItem(hDlg, IDC_QUICK_FORMAT);
	GetWindowRect(hCtrl, &rc);
	MapWindowPoints(NULL, hDlg, (POINT*)&rc, 2);
	advanced_format_section_height = rc.top;
	hCtrl = GetDlgItem(hDlg, IDC_BAD_BLOCKS);
	GetWindowRect(hCtrl, &rc);
	MapWindowPoints(NULL, hDlg, (POINT*)&rc, 2);
	advanced_format_section_height = rc.bottom - advanced_format_section_height;

	// Get the vertical position of the sections text
	hCtrl = GetDlgItem(hDlg, IDS_DRIVE_PROPERTIES_TXT);
	GetWindowRect(hCtrl, &rc);
	MapWindowPoints(NULL, hDlg, (POINT*)&rc, 2);
	sz = GetTextSize(hCtrl, NULL);
	section_vpos[0] = rc.top + 2 * sz.cy / 3;
	hCtrl = GetDlgItem(hDlg, IDS_FORMAT_OPTIONS_TXT);
	GetWindowRect(hCtrl, &rc);
	MapWindowPoints(NULL, hDlg, (POINT*)&rc, 2);
	sz = GetTextSize(hCtrl, NULL);
	section_vpos[1] = rc.top + 2 * sz.cy / 3;
	hCtrl = GetDlgItem(hDlg, IDS_STATUS_TXT);
	GetWindowRect(hCtrl, &rc);
	MapWindowPoints(NULL, hDlg, (POINT*)&rc, 2);
	sz = GetTextSize(hCtrl, NULL);
	section_vpos[2] = rc.top + 2 * sz.cy / 3;

	// Seriously, who designed this bullshit API call where you pass a SIZE
	// struct but can only retrieve one of cx or cy at a time?!?
	SendMessage(hMultiToolbar, TB_GETIDEALSIZE, (WPARAM)FALSE, (LPARAM)&sz);
	GetWindowRect(GetDlgItem(hDlg, IDC_ABOUT), &rc);
	MapWindowPoints(NULL, hDlg, (POINT*)&rc, 2);
	SetWindowPos(hMultiToolbar, hProgress, rc.left, rc.top, sz.cx, ddbh, 0);

	// Reposition the main buttons
	for (i = 0; i < ARRAYSIZE(main_button_ids); i++) {
		hCtrl = GetDlgItem(hDlg, main_button_ids[i]);
		GetWindowRect(hCtrl, &rc);
		MapWindowPoints(NULL, hDlg, (POINT*)&rc, 2);
		x = mw + fw - bw;
		if (i % 2 == 1)
			x -= bw + ssw;
		hPrevCtrl = GetNextWindow(hCtrl, GW_HWNDPREV);
		SetWindowPos(hCtrl, hPrevCtrl, x, rc.top, bw, ddbh, 0);
	}

	// Reposition the Save button
	hCtrl = GetDlgItem(hDlg, IDC_SAVE);
	GetWindowRect(hCtrl, &rc);
	MapWindowPoints(NULL, hDlg, (POINT*)&rc, 2);
	SendMessage(hSaveToolbar, TB_GETIDEALSIZE, (WPARAM)FALSE, (LPARAM)&sz);
	SendMessage(hSaveToolbar, TB_SETBUTTONSIZE, 0, MAKELPARAM(sz.cx, ddbh));
	// Microsoft, how I loathe thee!!!
	padding = (DWORD)SendMessage(hSaveToolbar, TB_GETPADDING, 0, 0);
	sz.cx = padding & 0xFFFF;
	sz.cy = padding >> 16;
	SendMessage(hSaveToolbar, TB_SETPADDING, 0, MAKELPARAM(sz.cx + 3, sz.cy + 2));
	SetWindowPos(hSaveToolbar, hDeviceList, mw + fw - sbw, rc.top, sbw, ddbh, 0);

	// Reposition the Hash button
	hCtrl = GetDlgItem(hDlg, IDC_HASH);
	GetWindowRect(hCtrl, &rc);
	MapWindowPoints(NULL, hDlg, (POINT*)&rc, 2);
	SendMessage(hHashToolbar, TB_GETIDEALSIZE, (WPARAM)FALSE, (LPARAM)&sz);
	SendMessage(hHashToolbar, TB_SETBUTTONSIZE, 0, MAKELPARAM(sz.cx, ddbh));
	padding = (DWORD)SendMessage(hHashToolbar, TB_GETPADDING, 0, 0);
	sz.cx = padding & 0xFFFF;
	sz.cy = padding >> 16;
	SendMessage(hHashToolbar, TB_SETPADDING, 0, MAKELPARAM(sz.cx + 3, sz.cy + 2));
	SetWindowPos(hHashToolbar, hBootType, mw + bsw + ssw, rc.top, sbw, ddbh, 0);

	// Reposition the Persistence slider and resize it to the boot selection width
	hCtrl = GetDlgItem(hDlg, IDC_PERSISTENCE_SLIDER);
	GetWindowRect(hCtrl, &rc);
	MapWindowPoints(NULL, hDlg, (POINT*)&rc, 2);
	SetWindowPos(hCtrl, GetDlgItem(hDlg, IDC_IMAGE_OPTION), mw, rc.top, bsw, rc.bottom - rc.top, 0);

	// Reposition the Persistence Units dropdown (no need to resize)
	hCtrl = GetDlgItem(hDlg, IDC_PERSISTENCE_UNITS);
	GetWindowRect(hCtrl, &rc);
	MapWindowPoints(NULL, hDlg, (POINT*)&rc, 2);
	sz.cx = fw - (rc.right - rc.left);
	SetWindowPos(hCtrl, GetDlgItem(hDlg, IDC_PERSISTENCE_SIZE), mw + sz.cx, rc.top, rc.right - rc.left, rc.bottom - rc.top, 0);
	ShowWindow(hCtrl, SW_HIDE);

	// Reposition and resize the Persistence Size edit
	hCtrl = GetDlgItem(hDlg, IDC_PERSISTENCE_SIZE);
	GetWindowRect(hCtrl, &rc);
	MapWindowPoints(NULL, hDlg, (POINT*)&rc, 2);
	SetWindowPos(hCtrl, GetDlgItem(hDlg, IDC_PERSISTENCE_SLIDER), mw + bsw + ssw, rc.top, fw - bsw - ssw, rc.bottom - rc.top, 0);
	EnableWindow(hCtrl, FALSE);

	// Reposition the CSM help tip
	hCtrl = GetDlgItem(hDlg, IDS_CSM_HELP_TXT);
	GetWindowRect(hCtrl, &rc);
	MapWindowPoints(NULL, hDlg, (POINT*)&rc, 2);
	SetWindowPos(hCtrl, hTargetSystem, mw + fw + tw, rc.top, sbw, rc.bottom - rc.top, 0);

	if (advanced_mode_device) {
		// Still need to adjust the width of the device selection dropdown
		GetWindowRect(hDeviceList, &rc);
		MapWindowPoints(NULL, hMainDialog, (POINT*)&rc, 2);
		SetWindowPos(hDeviceList, HWND_TOP, rc.left, rc.top, fw - ssw - sbw, rc.bottom - rc.top, 0);
	}

	// Resize the full width controls
	for (i = 0; i < ARRAYSIZE(full_width_controls); i++) {
		hCtrl = GetDlgItem(hDlg, full_width_controls[i]);
		GetWindowRect(hCtrl, &rc);
		MapWindowPoints(NULL, hDlg, (POINT*)&rc, 2);
		hPrevCtrl = GetNextWindow(hCtrl, GW_HWNDPREV);
		SetWindowPos(hCtrl, hPrevCtrl, rc.left, rc.top, fw, rc.bottom - rc.top, 0);
	}

	// Resize the half drowpdowns
	for (i = 0; i < ARRAYSIZE(half_width_ids); i++) {
		hCtrl = GetDlgItem(hDlg, half_width_ids[i]);
		GetWindowRect(hCtrl, &rc);
		MapWindowPoints(NULL, hDlg, (POINT*)&rc, 2);
		// First 5 controls are on the left handside
		// First 2 controls may overflow into separator
		hPrevCtrl = GetNextWindow(hCtrl, GW_HWNDPREV);
		SetWindowPos(hCtrl, hPrevCtrl, (i < 5) ? rc.left : mw + hw + sw, rc.top,
			(i <2) ? hw + sw : hw, rc.bottom - rc.top, 0);
	}

	// Resize the boot selection dropdown
	hCtrl = GetDlgItem(hDlg, IDC_BOOT_SELECTION);
	GetWindowRect(hCtrl, &rc);
	MapWindowPoints(NULL, hDlg, (POINT*)&rc, 2);
	hPrevCtrl = GetNextWindow(hCtrl, GW_HWNDPREV);
	SetWindowPos(hCtrl, hPrevCtrl, rc.left, rc.top, bsw, rc.bottom - rc.top, 0);
}
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
typedef  int /*<<< orphan*/  wtmp ;
typedef  int wchar_t ;
typedef  int /*<<< orphan*/  WPARAM ;
struct TYPE_6__ {int /*<<< orphan*/  top; int /*<<< orphan*/  left; } ;
struct TYPE_5__ {int /*<<< orphan*/  cy; int /*<<< orphan*/  cx; } ;
typedef  TYPE_1__ SIZE ;
typedef  TYPE_2__ RECT ;
typedef  int /*<<< orphan*/  POINT ;
typedef  int /*<<< orphan*/  HWND ;
typedef  scalar_t__ HFONT ;

/* Variables and functions */
 int ARRAYSIZE (int*) ; 
 scalar_t__ CreateFontA (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  DEFAULT_CHARSET ; 
 int /*<<< orphan*/  FALSE ; 
 int /*<<< orphan*/  FW_SEMIBOLD ; 
 int /*<<< orphan*/  GetDC (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  GetDeviceCaps (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  GetDlgItem (int /*<<< orphan*/ ,int) ; 
 TYPE_1__ GetTextSize (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  GetWindowRect (int /*<<< orphan*/ ,TYPE_2__*) ; 
 int /*<<< orphan*/  GetWindowTextW (int /*<<< orphan*/ ,int*,int) ; 
 int /*<<< orphan*/  LOGPIXELSY ; 
 int /*<<< orphan*/  MapWindowPoints (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  MulDiv (int,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  PROOF_QUALITY ; 
 int /*<<< orphan*/  SWP_NOZORDER ; 
 int /*<<< orphan*/  SendDlgItemMessageA (int /*<<< orphan*/ ,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  SetWindowPos (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  SetWindowTextW (int /*<<< orphan*/ ,int*) ; 
 int /*<<< orphan*/  TRUE ; 
 int /*<<< orphan*/  WM_SETFONT ; 
 int /*<<< orphan*/  hMainDialog ; 
 int /*<<< orphan*/  memset (int*,int /*<<< orphan*/ ,int) ; 
 int* section_control_ids ; 
 size_t wcslen (int*) ; 

void SetSectionHeaders(HWND hDlg)
{
	RECT rc;
	HWND hCtrl;
	SIZE sz;
	HFONT hf;
	wchar_t wtmp[128];
	size_t wlen;
	int i;

	// Set the section header fonts and resize the static controls accordingly
	hf = CreateFontA(-MulDiv(14, GetDeviceCaps(GetDC(hMainDialog), LOGPIXELSY), 72), 0, 0, 0,
		FW_SEMIBOLD, FALSE, FALSE, FALSE, DEFAULT_CHARSET, 0, 0, PROOF_QUALITY, 0, "Segoe UI");

	for (i = 0; i < ARRAYSIZE(section_control_ids); i++) {
		SendDlgItemMessageA(hDlg, section_control_ids[i], WM_SETFONT, (WPARAM)hf, TRUE);
		hCtrl = GetDlgItem(hDlg, section_control_ids[i]);
		memset(wtmp, 0, sizeof(wtmp));
		GetWindowTextW(hCtrl, wtmp, ARRAYSIZE(wtmp));
		wlen = wcslen(wtmp);
		wtmp[wlen++] = L' ';
		wtmp[wlen++] = L' ';
		SetWindowTextW(hCtrl, wtmp);
		GetWindowRect(hCtrl, &rc);
		MapWindowPoints(NULL, hDlg, (POINT*)&rc, 2);
		sz = GetTextSize(hCtrl, NULL);
		SetWindowPos(hCtrl, NULL, rc.left, rc.top, sz.cx, sz.cy, SWP_NOZORDER);
	}
}
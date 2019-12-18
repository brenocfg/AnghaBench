#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_3__ ;
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  button_info ;
typedef  int /*<<< orphan*/  WPARAM ;
struct TYPE_7__ {scalar_t__ top; scalar_t__ bottom; int /*<<< orphan*/  left; } ;
struct TYPE_6__ {int cx; } ;
struct TYPE_5__ {int cbSize; int /*<<< orphan*/ * pszText; int /*<<< orphan*/  dwMask; } ;
typedef  TYPE_1__ TBBUTTONINFO ;
typedef  TYPE_2__ SIZE ;
typedef  TYPE_3__ RECT ;
typedef  int /*<<< orphan*/  POINT ;
typedef  int /*<<< orphan*/  LPARAM ;
typedef  scalar_t__ BOOL ;

/* Variables and functions */
 int ARRAYSIZE (int /*<<< orphan*/ *) ; 
 scalar_t__ FALSE ; 
 int /*<<< orphan*/  GetDlgItem (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  GetWindowRect (int /*<<< orphan*/ ,TYPE_3__*) ; 
 scalar_t__ IDC_ADVANCED_FORMAT_OPTIONS ; 
 int /*<<< orphan*/  InvalidateRect (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  MSG_120 ; 
 int /*<<< orphan*/  MSG_121 ; 
 int /*<<< orphan*/  MSG_122 ; 
 int /*<<< orphan*/  MapWindowPoints (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  MoveCtrlY (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  ResizeDialogs (int) ; 
 int /*<<< orphan*/  SW_HIDE ; 
 int /*<<< orphan*/  SW_SHOW ; 
 int /*<<< orphan*/  SendMessage (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  SetWindowPos (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,scalar_t__,int,scalar_t__,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ShowWindow (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  TBIF_TEXT ; 
 int /*<<< orphan*/  TB_GETIDEALSIZE ; 
 int /*<<< orphan*/  TB_SETBUTTONINFO ; 
 int /*<<< orphan*/  TB_SETIMAGELIST ; 
 int /*<<< orphan*/  TRUE ; 
 int /*<<< orphan*/ * advanced_format_move_ids ; 
 int advanced_format_section_height ; 
 int /*<<< orphan*/ * advanced_format_toggle_ids ; 
 int fw ; 
 int /*<<< orphan*/  hAdvancedFormatToolbar ; 
 int /*<<< orphan*/  hClusterSize ; 
 scalar_t__ hDownImageList ; 
 int /*<<< orphan*/  hMainDialog ; 
 scalar_t__ hUpImageList ; 
 int /*<<< orphan*/  lmprintf (int /*<<< orphan*/ ,...) ; 
 int* section_vpos ; 
 int /*<<< orphan*/  utf8_to_wchar_no_alloc (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/ ** wtbtext ; 

void ToggleAdvancedFormatOptions(BOOL enable)
{
	RECT rc;
	SIZE sz;
	TBBUTTONINFO button_info;
	int i, shift = advanced_format_section_height;

	if (!enable)
		shift = -shift;
	section_vpos[2] += shift;

	// Toggle the Hide/Show toolbar text
	utf8_to_wchar_no_alloc(lmprintf((enable) ? MSG_122 : MSG_121, lmprintf(MSG_120)), wtbtext[1], ARRAYSIZE(wtbtext[0]));
	button_info.cbSize = sizeof(button_info);
	button_info.dwMask = TBIF_TEXT;
	button_info.pszText = wtbtext[1];
	SendMessage(hAdvancedFormatToolbar, TB_SETBUTTONINFO, (WPARAM)IDC_ADVANCED_FORMAT_OPTIONS, (LPARAM)&button_info);
	SendMessage(hAdvancedFormatToolbar, TB_SETIMAGELIST, (WPARAM)0, (LPARAM)((enable) ? hUpImageList : hDownImageList));
	GetWindowRect(hAdvancedFormatToolbar, &rc);
	MapWindowPoints(NULL, hMainDialog, (POINT*)&rc, 2);
	SendMessage(hAdvancedFormatToolbar, TB_GETIDEALSIZE, (WPARAM)FALSE, (LPARAM)&sz);
	if (sz.cx < 16)
		sz.cx = fw;
	SetWindowPos(hAdvancedFormatToolbar, hClusterSize, rc.left, rc.top, sz.cx, rc.bottom - rc.top, 0);

	// Move the controls up or down
	for (i = 0; i<ARRAYSIZE(advanced_format_move_ids); i++)
		MoveCtrlY(hMainDialog, advanced_format_move_ids[i], shift);

	// Hide or show the various advanced options
	for (i = 0; i<ARRAYSIZE(advanced_format_toggle_ids); i++)
		ShowWindow(GetDlgItem(hMainDialog, advanced_format_toggle_ids[i]), enable ? SW_SHOW : SW_HIDE);

	// Resize the main dialog and log window
	ResizeDialogs(shift);

	// Never hurts to force Windows' hand
	InvalidateRect(hMainDialog, NULL, TRUE);
}
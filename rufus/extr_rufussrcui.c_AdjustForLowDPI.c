#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct TYPE_3__ {scalar_t__ top; scalar_t__ bottom; scalar_t__ left; scalar_t__ right; } ;
typedef  TYPE_1__ RECT ;
typedef  int /*<<< orphan*/  POINT ;
typedef  int /*<<< orphan*/  HWND ;

/* Variables and functions */
 int ARRAYSIZE (scalar_t__**) ; 
 int /*<<< orphan*/  GW_HWNDPREV ; 
 int /*<<< orphan*/  GetDlgItem (int /*<<< orphan*/ ,scalar_t__) ; 
 int /*<<< orphan*/  GetNextWindow (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  GetWindowRect (int /*<<< orphan*/ ,TYPE_1__*) ; 
 scalar_t__ IDC_QUICK_FORMAT ; 
 int /*<<< orphan*/  InvalidateRect (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  MapWindowPoints (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  ResizeDialogs (int) ; 
 int /*<<< orphan*/  SetWindowPos (int /*<<< orphan*/ ,int /*<<< orphan*/ ,scalar_t__,scalar_t__,scalar_t__,scalar_t__,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  TRUE ; 
 scalar_t__** adjust_dpi_ids ; 
 int advanced_device_section_height ; 
 int advanced_format_section_height ; 
 float fScale ; 
 int* section_vpos ; 

void AdjustForLowDPI(HWND hDlg)
{
	static int ddy = 4;
	int i, j;
	RECT rc;
	HWND hCtrl, hPrevCtrl;
	int dy = 0;

	if (fScale >= 1.3f)
		return;

	for (i = 0; i < ARRAYSIZE(adjust_dpi_ids); i++) {
		dy += ddy;
		// "...and the other thing I really like about Microsoft's UI handling is how "
		//."you never have to introduce weird hardcoded constants all over the place, "
		// "just to make your UI look good...", said NO ONE ever.
		if (adjust_dpi_ids[i][0] == IDC_QUICK_FORMAT)
			dy += 1;
		for (j = 0; j < 5; j++) {
			if (adjust_dpi_ids[i][j] == 0)
				break;
			hCtrl = GetDlgItem(hDlg, adjust_dpi_ids[i][j]);
			GetWindowRect(hCtrl, &rc);
			MapWindowPoints(NULL, hDlg, (POINT*)&rc, 2);
			hPrevCtrl = GetNextWindow(hCtrl, GW_HWNDPREV);
			SetWindowPos(hCtrl, hPrevCtrl, rc.left, rc.top + dy,
				rc.right - rc.left, rc.bottom - rc.top, 0);
		}
	}

	section_vpos[1] += 9 * ddy;
	section_vpos[2] += 16 * ddy + 1;
	advanced_device_section_height += 3 * ddy;
	advanced_format_section_height += 3 * ddy + 1;

	ResizeDialogs(dy + 2 * ddy);
	InvalidateRect(hDlg, NULL, TRUE);
}
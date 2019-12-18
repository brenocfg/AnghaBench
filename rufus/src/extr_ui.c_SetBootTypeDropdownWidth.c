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
struct TYPE_6__ {scalar_t__ left; scalar_t__ right; } ;
struct TYPE_5__ {scalar_t__ cx; } ;
typedef  TYPE_1__ SIZE ;
typedef  TYPE_2__ RECT ;
typedef  int /*<<< orphan*/  POINT ;
typedef  int /*<<< orphan*/  LPARAM ;
typedef  scalar_t__ HFONT ;
typedef  int /*<<< orphan*/  HDC ;

/* Variables and functions */
 int /*<<< orphan*/  CB_SETDROPPEDWIDTH ; 
 int /*<<< orphan*/  GetDC (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  GetTextExtentPointU (int /*<<< orphan*/ ,int /*<<< orphan*/ ,TYPE_1__*) ; 
 int /*<<< orphan*/  GetWindowRect (int /*<<< orphan*/ ,TYPE_2__*) ; 
 int /*<<< orphan*/  MapWindowPoints (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  SelectObject (int /*<<< orphan*/ ,scalar_t__) ; 
 int /*<<< orphan*/  SendMessage (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ SendMessageA (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  WM_GETFONT ; 
 int /*<<< orphan*/  hBootType ; 
 int /*<<< orphan*/  hMainDialog ; 
 int /*<<< orphan*/ * image_path ; 
 scalar_t__ max (scalar_t__,scalar_t__) ; 
 int /*<<< orphan*/  safe_release_dc (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  short_image_path ; 

void SetBootTypeDropdownWidth(void)
{
	HDC hDC;
	HFONT hFont;
	SIZE sz;
	RECT rc;

	if (image_path == NULL)
		return;
	// Set the maximum width of the dropdown according to the image selected
	GetWindowRect(hBootType, &rc);
	MapWindowPoints(NULL, hMainDialog, (POINT*)&rc, 2);
	hDC = GetDC(hBootType);
	hFont = (HFONT)SendMessageA(hBootType, WM_GETFONT, 0, 0);
	SelectObject(hDC, hFont);
	GetTextExtentPointU(hDC, short_image_path, &sz);
	safe_release_dc(hBootType, hDC);
	SendMessage(hBootType, CB_SETDROPPEDWIDTH, (WPARAM)max(sz.cx + 10, rc.right - rc.left), (LPARAM)0);
}
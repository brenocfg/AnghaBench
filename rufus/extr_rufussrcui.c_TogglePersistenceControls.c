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
typedef  int /*<<< orphan*/  LONG_PTR ;
typedef  scalar_t__ LONG ;
typedef  int /*<<< orphan*/  HWND ;
typedef  scalar_t__ BOOL ;

/* Variables and functions */
 int /*<<< orphan*/  EnableWindow (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  FALSE ; 
 int /*<<< orphan*/  GWL_EXSTYLE ; 
 int /*<<< orphan*/  GetDlgItem (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  GetWindowLongPtr (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  GetWindowRect (int /*<<< orphan*/ ,TYPE_1__*) ; 
 int /*<<< orphan*/  IDC_PERSISTENCE_SIZE ; 
 int /*<<< orphan*/  IDC_PERSISTENCE_SLIDER ; 
 int /*<<< orphan*/  IDC_PERSISTENCE_UNITS ; 
 int /*<<< orphan*/  MapWindowPoints (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  SW_HIDE ; 
 int /*<<< orphan*/  SW_SHOW ; 
 int /*<<< orphan*/  SetWindowLongPtr (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  SetWindowPos (int /*<<< orphan*/ ,int /*<<< orphan*/ ,scalar_t__,scalar_t__,scalar_t__,scalar_t__,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ShowWindow (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  TRUE ; 
 int /*<<< orphan*/  WS_EX_RIGHT ; 
 scalar_t__ bsw ; 
 scalar_t__ fw ; 
 int /*<<< orphan*/  hMainDialog ; 
 scalar_t__ mw ; 
 scalar_t__ ssw ; 

void TogglePersistenceControls(BOOL display)
{
	RECT rc;
	HWND hSize, hUnits;
	LONG_PTR style;
	LONG width = fw - bsw - ssw;
	hSize = GetDlgItem(hMainDialog, IDC_PERSISTENCE_SIZE);
	hUnits = GetDlgItem(hMainDialog, IDC_PERSISTENCE_UNITS);

	style = GetWindowLongPtr(hSize, GWL_EXSTYLE);
	if (display)
		style |= WS_EX_RIGHT;
	else
		style &= ~WS_EX_RIGHT;
	SetWindowLongPtr(hSize, GWL_EXSTYLE, style);

	if (display) {
		GetWindowRect(hUnits, &rc);
		MapWindowPoints(NULL, hMainDialog, (POINT*)&rc, 2);
		width -= (rc.right - rc.left) + ssw;
	}

	GetWindowRect(hSize, &rc);
	MapWindowPoints(NULL, hMainDialog, (POINT*)&rc, 2);
	SetWindowPos(hSize, GetDlgItem(hMainDialog, IDC_PERSISTENCE_SLIDER), mw + bsw + ssw, rc.top, width, rc.bottom - rc.top, 0);

	EnableWindow(hSize, display ? TRUE : FALSE);
	EnableWindow(hUnits, display ? TRUE : FALSE);
	ShowWindow(hUnits, display ? SW_SHOW : SW_HIDE);
}
#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_5__ {scalar_t__ y; scalar_t__ x; } ;
struct TYPE_4__ {scalar_t__ top; scalar_t__ bottom; scalar_t__ left; scalar_t__ right; } ;
typedef  TYPE_1__ RECT ;
typedef  TYPE_2__ POINT ;

/* Variables and functions */
 int /*<<< orphan*/  Edit_GetLineCount (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  Edit_Scroll (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  GetWindowRect (int /*<<< orphan*/ ,TYPE_1__*) ; 
 int /*<<< orphan*/  IDCANCEL ; 
 int /*<<< orphan*/  IDC_LOG_CLEAR ; 
 int /*<<< orphan*/  IDC_LOG_SAVE ; 
 int /*<<< orphan*/  MoveCtrlY (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  MoveWindow (int /*<<< orphan*/ ,scalar_t__,scalar_t__,scalar_t__,scalar_t__,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  SWP_NOZORDER ; 
 int /*<<< orphan*/  SetWindowPos (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,scalar_t__,scalar_t__,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  TRUE ; 
 int /*<<< orphan*/  hLog ; 
 int /*<<< orphan*/  hLogDialog ; 
 int /*<<< orphan*/  hMainDialog ; 

__attribute__((used)) static void ResizeDialogs(int shift)
{
	RECT rc;
	POINT point;

	// Resize the main dialog
	GetWindowRect(hMainDialog, &rc);
	point.x = (rc.right - rc.left);
	point.y = (rc.bottom - rc.top);
	MoveWindow(hMainDialog, rc.left, rc.top, point.x, point.y + shift, TRUE);

	// Resize the log
	GetWindowRect(hLogDialog, &rc);
	point.x = (rc.right - rc.left);
	point.y = (rc.bottom - rc.top);
	MoveWindow(hLogDialog, rc.left, rc.top, point.x, point.y + shift, TRUE);
	MoveCtrlY(hLogDialog, IDC_LOG_CLEAR, shift);
	MoveCtrlY(hLogDialog, IDC_LOG_SAVE, shift);
	MoveCtrlY(hLogDialog, IDCANCEL, shift);
	GetWindowRect(hLog, &rc);
	point.x = (rc.right - rc.left);
	point.y = (rc.bottom - rc.top) + shift;
	SetWindowPos(hLog, NULL, 0, 0, point.x, point.y, SWP_NOZORDER);
	// Don't forget to scroll the edit to the bottom after resize
	Edit_Scroll(hLog, 0, Edit_GetLineCount(hLog));
}
#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_12__   TYPE_6__ ;
typedef  struct TYPE_11__   TYPE_3__ ;
typedef  struct TYPE_10__   TYPE_2__ ;
typedef  struct TYPE_9__   TYPE_1__ ;

/* Type definitions */
struct TYPE_9__ {int bottom; int top; scalar_t__ left; scalar_t__ right; } ;
struct TYPE_10__ {TYPE_1__ rcNormalPosition; } ;
typedef  TYPE_2__ WINDOWPLACEMENT ;
struct TYPE_12__ {int /*<<< orphan*/  hstatusbar; int /*<<< orphan*/  hdrivebar; int /*<<< orphan*/  htoolbar; } ;
struct TYPE_11__ {int left; int top; int bottom; scalar_t__ right; } ;
typedef  TYPE_3__ RECT ;
typedef  TYPE_3__* PRECT ;
typedef  int /*<<< orphan*/  HWND ;

/* Variables and functions */
 int /*<<< orphan*/  GetClientRect (int /*<<< orphan*/ ,TYPE_3__*) ; 
 int GetSystemMetrics (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  GetWindowPlacement (int /*<<< orphan*/ ,TYPE_2__*) ; 
 TYPE_6__ Globals ; 
 int /*<<< orphan*/  IsIconic (int /*<<< orphan*/ ) ; 
 scalar_t__ IsWindowVisible (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  SM_CXEDGE ; 
 int /*<<< orphan*/  SM_CXSIZEFRAME ; 
 int /*<<< orphan*/  SM_CYCAPTION ; 
 int /*<<< orphan*/  SM_CYEDGE ; 
 int /*<<< orphan*/  SM_CYMENUSIZE ; 
 int /*<<< orphan*/  SM_CYSIZEFRAME ; 

__attribute__((used)) static void frame_get_clientspace(HWND hwnd, PRECT prect)
{
	RECT rt;

	if (!IsIconic(hwnd))
		GetClientRect(hwnd, prect);
	else {
		WINDOWPLACEMENT wp;

		GetWindowPlacement(hwnd, &wp);

		prect->left = prect->top = 0;
		prect->right = wp.rcNormalPosition.right-wp.rcNormalPosition.left-
						2*(GetSystemMetrics(SM_CXSIZEFRAME)+GetSystemMetrics(SM_CXEDGE));
		prect->bottom = wp.rcNormalPosition.bottom-wp.rcNormalPosition.top-
						2*(GetSystemMetrics(SM_CYSIZEFRAME)+GetSystemMetrics(SM_CYEDGE))-
						GetSystemMetrics(SM_CYCAPTION)-GetSystemMetrics(SM_CYMENUSIZE);
	}

	if (IsWindowVisible(Globals.htoolbar)) {
		GetClientRect(Globals.htoolbar, &rt);
		prect->top += rt.bottom+2;
	}

	if (IsWindowVisible(Globals.hdrivebar)) {
		GetClientRect(Globals.hdrivebar, &rt);
		prect->top += rt.bottom+2;
	}

	if (IsWindowVisible(Globals.hstatusbar)) {
		GetClientRect(Globals.hstatusbar, &rt);
		prect->bottom -= rt.bottom;
	}
}
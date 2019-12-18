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
typedef  int /*<<< orphan*/  WPARAM ;
struct TYPE_4__ {int flags; scalar_t__ cy; scalar_t__ cx; int /*<<< orphan*/  hwnd; } ;
typedef  TYPE_1__ WINDOWPOS ;
struct TYPE_5__ {scalar_t__ top; scalar_t__ bottom; scalar_t__ left; scalar_t__ right; } ;
typedef  TYPE_2__ RECT ;
typedef  int /*<<< orphan*/  LPARAM ;
typedef  int /*<<< orphan*/  HWND ;

/* Variables and functions */
 int /*<<< orphan*/  GetWindowRect (int /*<<< orphan*/ ,TYPE_2__*) ; 
 int SWP_NOACTIVATE ; 
 int SWP_NOMOVE ; 
 int SWP_NOOWNERZORDER ; 
 int SWP_NOZORDER ; 
 int /*<<< orphan*/  SendMessage (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  WM_WINDOWPOSCHANGED ; 

void OnSetFont(HWND hWnd, WPARAM wParam, LPARAM lParam)
{
	RECT rc;
	WINDOWPOS wp;

	GetWindowRect(hWnd, &rc);
	wp.hwnd = hWnd;
	wp.cx = rc.right - rc.left;
	wp.cy = rc.bottom - rc.top;
	wp.flags = SWP_NOACTIVATE | SWP_NOMOVE | SWP_NOOWNERZORDER | SWP_NOZORDER;
	SendMessage(hWnd, WM_WINDOWPOSCHANGED, 0, (LPARAM)&wp);
}
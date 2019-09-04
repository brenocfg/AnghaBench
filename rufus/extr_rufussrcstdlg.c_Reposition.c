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
 int /*<<< orphan*/  GetDlgItem (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  GetWindowRect (int /*<<< orphan*/ ,TYPE_1__*) ; 
 int /*<<< orphan*/  HWND_TOP ; 
 int /*<<< orphan*/  MapWindowPoints (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  SetWindowPos (int /*<<< orphan*/ ,int /*<<< orphan*/ ,scalar_t__,scalar_t__,scalar_t__,scalar_t__,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void Reposition(HWND hDlg, int id, int dx, int dw)
{
	HWND hCtrl;
	RECT rc;

	hCtrl = GetDlgItem(hDlg, id);
	GetWindowRect(hCtrl, &rc);
	MapWindowPoints(NULL, hDlg, (POINT*)&rc, 2);
	SetWindowPos(hCtrl, HWND_TOP, rc.left + dx, rc.top, rc.right - rc.left + dw, rc.bottom - rc.top, 0);
}
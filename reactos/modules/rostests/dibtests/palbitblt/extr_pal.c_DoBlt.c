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
struct TYPE_3__ {int /*<<< orphan*/  bottom; int /*<<< orphan*/  right; } ;
typedef  TYPE_1__ RECT ;
typedef  int /*<<< orphan*/ * HWND ;
typedef  int /*<<< orphan*/  HDC ;
typedef  int /*<<< orphan*/  HBITMAP ;

/* Variables and functions */
 int /*<<< orphan*/  BitBlt (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  CreateCompatibleDC (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  DeleteDC (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  DeleteObject (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * GetActiveWindow () ; 
 int /*<<< orphan*/  GetClientRect (int /*<<< orphan*/ *,TYPE_1__*) ; 
 int /*<<< orphan*/  GetDC (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  ReleaseDC (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  SRCCOPY ; 
 int /*<<< orphan*/  SelectObject (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

void DoBlt(HBITMAP hBM)
{
	HDC hDC,Context;
	HWND ActiveWindow;
	RECT dest;
	HBITMAP dflBmp;

	if((ActiveWindow = GetActiveWindow()) == NULL)
		return;

	hDC = GetDC(ActiveWindow);
	GetClientRect(ActiveWindow,&dest);

	Context = CreateCompatibleDC(0);
	dflBmp = SelectObject(Context, hBM);
	BitBlt(hDC, 0, 0, dest.right, dest.bottom, Context, 0, 0, SRCCOPY);
	SelectObject(Context, dflBmp);
	DeleteDC(Context);
	DeleteObject(dflBmp);
	ReleaseDC(ActiveWindow, hDC);
}
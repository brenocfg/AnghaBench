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
struct TYPE_3__ {int left; int right; int bottom; scalar_t__ top; } ;
typedef  TYPE_1__ RECT ;
typedef  int /*<<< orphan*/ * PRECT ;
typedef  int /*<<< orphan*/  HWND ;
typedef  int /*<<< orphan*/ * HRGN ;
typedef  int /*<<< orphan*/  HDC ;

/* Variables and functions */
 int /*<<< orphan*/ * CreateRectRgn (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  CreateWindowW (char*,char*,int,int,int,int,int,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  DeleteObject (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  DestroyWindow (int /*<<< orphan*/ ) ; 
 scalar_t__ FALSE ; 
 int /*<<< orphan*/  GetDC (int /*<<< orphan*/ ) ; 
 int GetUpdateRgn (int /*<<< orphan*/ ,int /*<<< orphan*/ *,scalar_t__) ; 
 int NULLREGION ; 
 int /*<<< orphan*/  ReleaseDC (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ ScrollDC (int /*<<< orphan*/ ,int,int,int /*<<< orphan*/ *,TYPE_1__*,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 scalar_t__ TRUE ; 
 int /*<<< orphan*/  UpdateWindow (int /*<<< orphan*/ ) ; 
 int WS_OVERLAPPEDWINDOW ; 
 int WS_VISIBLE ; 
 int /*<<< orphan*/  ok (int,char*,...) ; 

void Test_ScrollDC()
{
	HWND hWnd, hWnd2;
	HDC hDC;
	HRGN hrgn;
	RECT rcClip;
	int iResult;

	/* Create a window */
	hWnd = CreateWindowW(L"BUTTON", L"TestWindow", WS_OVERLAPPEDWINDOW | WS_VISIBLE,
	                    100, 100, 100, 100,
	                    NULL, NULL, 0, 0);
	UpdateWindow(hWnd);
	hDC = GetDC(hWnd);

	/* Test that no update region is there */
	hrgn = CreateRectRgn(0,0,0,0);
	iResult = GetUpdateRgn(hWnd, hrgn, FALSE);
	ok (iResult == NULLREGION, "Expected NULLREGION, got %d\n", iResult);

    /* Test normal scrolling */
	ok(ScrollDC(hDC, 0, 0, NULL, NULL, hrgn, NULL) == TRUE, "ScrollDC failed\n");

    /* Scroll with invalid update region */
	DeleteObject(hrgn);
	ok(ScrollDC(hDC, 50, 0, NULL, NULL, (HRGN)0x12345678, NULL) == FALSE, "ScrollDC successed\n");
	ok(ScrollDC(hDC, 50, 0, NULL, NULL, hrgn, NULL) == FALSE, "ScrollDC successed\n");
	hrgn = CreateRectRgn(0,0,0,0);
	iResult = GetUpdateRgn(hWnd, hrgn, FALSE);
	ok(iResult == NULLREGION, "Expected NULLREGION, got %d\n", iResult);

    /* Scroll with invalid update rect pointer */
	ok(ScrollDC(hDC, 50, 0, NULL, NULL, NULL, (PRECT)1) == FALSE, "ScrollDC failed\n");
	iResult = GetUpdateRgn(hWnd, hrgn, FALSE);
	ok(iResult == NULLREGION, "Expected NULLREGION, got %d\n", iResult);

    /* Scroll with a clip rect */
    rcClip.left = 50; rcClip.top = 0; rcClip.right = 100; rcClip.bottom = 100;
	ok(ScrollDC(hDC, 50, 0, NULL, &rcClip, hrgn, NULL) == TRUE, "ScrollDC failed\n");
	iResult = GetUpdateRgn(hWnd, hrgn, FALSE);
	ok(iResult == NULLREGION, "Expected NULLREGION, got %d\n", iResult);

    /* Scroll with a clip rect */
    rcClip.left = 50; rcClip.top = 0; rcClip.right = 100; rcClip.bottom = 100;
	ok(ScrollDC(hDC, 50, 50, NULL, &rcClip, hrgn, NULL) == TRUE, "ScrollDC failed\n");
	iResult = GetUpdateRgn(hWnd, hrgn, FALSE);
	ok(iResult == NULLREGION, "Expected NULLREGION, got %d\n", iResult);

	/* Overlap with another window */
	hWnd2 = CreateWindowW(L"BUTTON", L"TestWindow", WS_OVERLAPPEDWINDOW | WS_VISIBLE,
	                    30, 160, 100, 100,
	                    NULL, NULL, 0, 0);
	UpdateWindow(hWnd2);

    /* Cleanup */
	ReleaseDC(hWnd, hDC);
    DestroyWindow(hWnd);
    DestroyWindow(hWnd2);

}
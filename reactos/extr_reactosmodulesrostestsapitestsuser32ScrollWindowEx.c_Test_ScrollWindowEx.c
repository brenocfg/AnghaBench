#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */

/* Type definitions */
typedef  int /*<<< orphan*/ * LPRECT ;
typedef  int /*<<< orphan*/  HWND ;
typedef  int /*<<< orphan*/ * HRGN ;

/* Variables and functions */
 int /*<<< orphan*/  CW_USEDEFAULT ; 
 int /*<<< orphan*/ * CreateRectRgn (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  CreateWindowW (char*,char*,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,int,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  DeleteObject (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  DestroyWindow (int /*<<< orphan*/ ) ; 
 int ERROR ; 
 int /*<<< orphan*/  FALSE ; 
 int GetUpdateRgn (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int NULLREGION ; 
 int SIMPLEREGION ; 
 int /*<<< orphan*/  SW_INVALIDATE ; 
 int ScrollWindowEx (int /*<<< orphan*/ ,int,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  UpdateWindow (int /*<<< orphan*/ ) ; 
 int WS_OVERLAPPEDWINDOW ; 
 int WS_VISIBLE ; 
 int /*<<< orphan*/  ok (int,char*,int) ; 

void Test_ScrollWindowEx()
{
	HWND hWnd;
	HRGN hrgn;
	int Result;

	/* Create a window */
	hWnd = CreateWindowW(L"BUTTON", L"TestWindow", WS_OVERLAPPEDWINDOW | WS_VISIBLE,
	                    CW_USEDEFAULT, CW_USEDEFAULT, 100, 100,
	                    NULL, NULL, 0, 0);
	UpdateWindow(hWnd);

	/* Assert that no update region is there */
	hrgn = CreateRectRgn(0,0,0,0);
	Result = GetUpdateRgn(hWnd, hrgn, FALSE);
	ok(Result == NULLREGION, "Result = %d\n", Result);

	Result = ScrollWindowEx(hWnd, 20, 0, NULL, NULL, NULL, NULL, 0);
	ok(Result == SIMPLEREGION, "Result = %d\n", Result);
	Result = GetUpdateRgn(hWnd, hrgn, FALSE);
	ok(Result == NULLREGION, "Result = %d\n", Result);

	Result = ScrollWindowEx(hWnd, 20, 0, NULL, NULL, NULL, NULL, SW_INVALIDATE);
	ok(Result == SIMPLEREGION, "Result = %d\n", Result);
	Result = GetUpdateRgn(hWnd, hrgn, FALSE);
	ok(Result == SIMPLEREGION, "Result = %d\n", Result);
	UpdateWindow(hWnd);

	// test invalid update region
	DeleteObject(hrgn);
	Result = ScrollWindowEx(hWnd, 20, 0, NULL, NULL, hrgn, NULL, SW_INVALIDATE);
	ok(Result == ERROR, "Result = %d\n", Result);
	hrgn = CreateRectRgn(0,0,0,0);
	UpdateWindow(hWnd);

	// Test invalid updaterect pointer
	Result = ScrollWindowEx(hWnd, 20, 0, NULL, NULL, NULL, (LPRECT)1, SW_INVALIDATE);
	ok(Result == ERROR, "Result = %d\n", Result);
	Result = GetUpdateRgn(hWnd, hrgn, FALSE);
	ok(Result == SIMPLEREGION, "Result = %d\n", Result);

// test for alignment of rects

	DeleteObject(hrgn);
    DestroyWindow(hWnd);
}
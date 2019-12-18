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
typedef  int /*<<< orphan*/  RECT ;
typedef  int /*<<< orphan*/ * HWND ;
typedef  int /*<<< orphan*/ * HRGN ;
typedef  int /*<<< orphan*/  HDC ;

/* Variables and functions */
 int COMPLEXREGION ; 
 int /*<<< orphan*/  CW_USEDEFAULT ; 
 int CombineRgn (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * CreateRectRgn (int,int,int,int) ; 
 int /*<<< orphan*/ * CreateWindowW (char*,char*,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,int,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  DeleteObject (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  DestroyWindow (int /*<<< orphan*/ *) ; 
 int ERROR ; 
 int ERROR_INVALID_HANDLE ; 
 int /*<<< orphan*/  ERROR_SUCCESS ; 
 int GetClipBox (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  GetDC (int /*<<< orphan*/ *) ; 
 int GetLastError () ; 
 int /*<<< orphan*/  MM_ANISOTROPIC ; 
 int NULLREGION ; 
 int /*<<< orphan*/  RGN_OR ; 
 int /*<<< orphan*/  ReleaseDC (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int SIMPLEREGION ; 
 int /*<<< orphan*/  SelectClipRgn (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  SetLastError (int /*<<< orphan*/ ) ; 
 int SetMapMode (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  SetMetaRgn (int /*<<< orphan*/ ) ; 
 int SetViewportExtEx (int /*<<< orphan*/ ,int,int,int /*<<< orphan*/ *) ; 
 int SetWindowExtEx (int /*<<< orphan*/ ,int,int,int /*<<< orphan*/ *) ; 
 int WS_OVERLAPPEDWINDOW ; 
 int WS_VISIBLE ; 
 int /*<<< orphan*/  ok (int,char*,...) ; 
 int /*<<< orphan*/  ok_int (int,int) ; 
 int /*<<< orphan*/  ok_rect (int /*<<< orphan*/ *,int,int,int,int) ; 

void Test_GetClipBox()
{
    HWND hWnd;
    HDC hdc;
    RECT rect;
    HRGN hrgn, hrgn2;
    int ret;

    /* Create a window */
    hWnd = CreateWindowW(L"BUTTON", L"TestWindow", WS_OVERLAPPEDWINDOW | WS_VISIBLE,
                        CW_USEDEFAULT, CW_USEDEFAULT, 100, 100,
                        NULL, NULL, 0, 0);
    ok(hWnd != NULL, "CreateWindowW failed\n");
    if (hWnd == NULL)
    {
        return;
    }

    hdc = GetDC(hWnd);

    /* Test invalid DC */
    SetLastError(ERROR_SUCCESS);
    ret = GetClipBox((HDC)0x12345, &rect);
    ok(ret == ERROR, "Expected ERROR, got %d\n", ret);
    ok((GetLastError() == 0) || (GetLastError() == ERROR_INVALID_HANDLE), "Expected 0, got %ld\n", GetLastError());

    //ret = GetClipBox(hdc, &rect);
    //ok_int(ret, SIMPLEREGION);
    //ok_rect(&rect, 0, 0, 132, 68);

    /* Create a clip region */
    hrgn = CreateRectRgn(5, 7, 50, 50);
    SelectClipRgn(hdc, hrgn);
    DeleteObject(hrgn);
    ret = GetClipBox(hdc, &rect);
    ok_int(ret, SIMPLEREGION);
    ok_rect(&rect, 5, 7, 50, 50);

    /* Set clip region as meta region */
    SetMetaRgn(hdc);

    /* Create a new clip region */
    hrgn = CreateRectRgn(10, 10, 100, 100);
    SelectClipRgn(hdc, hrgn);
    DeleteObject(hrgn);
    ret = GetClipBox(hdc, &rect);
    ok_int(ret, SIMPLEREGION);
    ok_rect(&rect, 10, 10, 50, 50);

    /* Create an empty clip region */
    hrgn = CreateRectRgn(10, 10, 10, 30);
    SelectClipRgn(hdc, hrgn);
    DeleteObject(hrgn);
    ret = GetClipBox(hdc, &rect);
    ok_int(ret, NULLREGION);
    ok_rect(&rect, 0, 0, 0, 0);

    /* Create a complex region */
    hrgn = CreateRectRgn(10, 10, 30, 30);
    hrgn2 = CreateRectRgn(20, 20, 60, 60);
    ok_int(CombineRgn(hrgn, hrgn, hrgn2, RGN_OR), COMPLEXREGION);
    SelectClipRgn(hdc, hrgn);
    DeleteObject(hrgn2);
    ret = GetClipBox(hdc, &rect);
    ok_int(ret, COMPLEXREGION);
    ok_rect(&rect, 10, 10, 50, 50);

    /* Set scaling but keep the mapping mode (viewport should not be changed) */
    ok_int(SetViewportExtEx(hdc, 1000, 1000, NULL), 1);
    ret = GetClipBox(hdc, &rect);
    ok_int(ret, COMPLEXREGION);
    ok_rect(&rect, 10, 10, 50, 50);

    /* Set unisotropic mode, ClipBox should be unchanged */
    ok_int(SetMapMode(hdc, MM_ANISOTROPIC), 1);
    ret = GetClipBox(hdc, &rect);
    ok_int(ret, COMPLEXREGION);
    ok_rect(&rect, 10, 10, 50, 50);

    /* Now set viewport again */
    ok_int(SetViewportExtEx(hdc, 200, 400, NULL), 1);
    ret = GetClipBox(hdc, &rect);
    ok_int(ret, COMPLEXREGION); // obviously some special secret feature...
    ok_rect(&rect, 0, 0, 0, 0);

    /* Reset clip region */
    SelectClipRgn(hdc, NULL);
    SetMetaRgn(hdc);
    ret = GetClipBox(hdc, &rect);
    ok_int(ret, SIMPLEREGION);
    ok_rect(&rect, 0, 0, 0, 0);

    hrgn = CreateRectRgn(10, 10, 190, 190);
    SelectClipRgn(hdc, hrgn);
    ret = GetClipBox(hdc, &rect);
    ok_int(ret, SIMPLEREGION);
    ok_rect(&rect, 0, 0, 0, 0);

    /* Now also set the window extension */
    ok_int(SetWindowExtEx(hdc, 400, 600, NULL), 1);
    ret = GetClipBox(hdc, &rect);
    ok_int(ret, SIMPLEREGION);
    ok_rect(&rect, 20, 15, 100, 75);

    hrgn = CreateRectRgn(30, 30, 300, 300);
    SelectClipRgn(hdc, hrgn);
    SetMetaRgn(hdc);
    ret = GetClipBox(hdc, &rect);
    ok_int(ret, SIMPLEREGION);
    ok_rect(&rect, 60, 45, 100, 75);

    ReleaseDC(hWnd, hdc);
    DestroyWindow(hWnd);
}
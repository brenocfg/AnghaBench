#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_4__ {int cx; int cy; } ;
typedef  TYPE_1__ SIZE ;
typedef  scalar_t__ INT ;
typedef  int /*<<< orphan*/  HDC ;
typedef  scalar_t__ BOOL ;

/* Variables and functions */
 int /*<<< orphan*/  CreateICA (char*,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  DeleteDC (int /*<<< orphan*/ ) ; 
 scalar_t__ FALSE ; 
 scalar_t__ GetDeviceCaps (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  GetViewportExtEx (int /*<<< orphan*/ ,TYPE_1__*) ; 
 int /*<<< orphan*/  GetWindowExtEx (int /*<<< orphan*/ ,TYPE_1__*) ; 
 int /*<<< orphan*/  HORZRES ; 
 int /*<<< orphan*/  HORZSIZE ; 
 int /*<<< orphan*/  LOGPIXELSX ; 
 int /*<<< orphan*/  MM_LOMETRIC ; 
 int /*<<< orphan*/  MM_TEXT ; 
 int /*<<< orphan*/  SetMapMode (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ TRUE ; 
 int /*<<< orphan*/  expect_LPtoDP (int /*<<< orphan*/ ,int,int) ; 
 int /*<<< orphan*/  expect_viewport_ext (int /*<<< orphan*/ ,int,int) ; 
 int /*<<< orphan*/  expect_window_ext (int /*<<< orphan*/ ,int,int) ; 
 int /*<<< orphan*/  ok (int,char*,...) ; 
 scalar_t__ pSetVirtualResolution (int /*<<< orphan*/ ,int,int,int,int) ; 
 int /*<<< orphan*/  win_skip (char*) ; 

__attribute__((used)) static void test_setvirtualresolution(void)
{
    HDC hdc = CreateICA("DISPLAY", NULL, NULL, NULL);
    BOOL r;
    INT horz_res = GetDeviceCaps(hdc, HORZRES);
    INT horz_size = GetDeviceCaps(hdc, HORZSIZE);
    INT log_pixels_x = GetDeviceCaps(hdc, LOGPIXELSX);
    SIZE orig_lometric_vp, orig_lometric_wnd;

    if(!pSetVirtualResolution)
    {
        win_skip("Don't have SetVirtualResolution\n");
        return;
    }

    /* Get the true resolution limits */
    SetMapMode(hdc, MM_LOMETRIC);
    GetViewportExtEx(hdc, &orig_lometric_vp);
    GetWindowExtEx(hdc, &orig_lometric_wnd);
    SetMapMode(hdc, MM_TEXT);

    r = pSetVirtualResolution(hdc, 4000, 1000, 400, 200); /* 10 pix/mm x 5 pix/mm */
    ok(r == TRUE, "got %d\n", r);
    expect_LPtoDP(hdc, 1000, 1000);
    expect_viewport_ext(hdc, 1, 1);
    expect_window_ext(hdc, 1, 1);

    SetMapMode(hdc, MM_LOMETRIC);
    expect_LPtoDP(hdc, 1000, -500);
    expect_viewport_ext(hdc, 4000, -1000);
    expect_window_ext(hdc, 4000, 2000);

    /* Doesn't change the device caps */
    ok(horz_res == GetDeviceCaps(hdc, HORZRES), "horz_res changed\n");
    ok(horz_size == GetDeviceCaps(hdc, HORZSIZE), "horz_size changed\n");
    ok(log_pixels_x == GetDeviceCaps(hdc, LOGPIXELSX), "log_pixels_x changed\n");

    r = pSetVirtualResolution(hdc, 8000, 1000, 400, 200); /* 20 pix/mm x 5 pix/mm */
    ok(r == TRUE, "got %d\n", r);
    expect_LPtoDP(hdc, 1000, -500); /* No change, need to re-set the mapping mode */
    SetMapMode(hdc, MM_TEXT);
    SetMapMode(hdc, MM_LOMETRIC);
    expect_LPtoDP(hdc, 2000, -500);
    expect_viewport_ext(hdc, 8000, -1000);
    expect_window_ext(hdc, 4000, 2000);

    r = pSetVirtualResolution(hdc, 8000, 1000, 200, 200); /* 40 pix/mm x 5 pix/mm */
    ok(r == TRUE, "got %d\n", r);
    SetMapMode(hdc, MM_TEXT);
    SetMapMode(hdc, MM_LOMETRIC);
    expect_LPtoDP(hdc, 4000, -500);
    expect_viewport_ext(hdc, 8000, -1000);
    expect_window_ext(hdc, 2000, 2000);

    r = pSetVirtualResolution(hdc, 8000, 1000, 200, 200); /* 40 pix/mm x 5 pix/mm */
    ok(r == TRUE, "got %d\n", r);
    SetMapMode(hdc, MM_TEXT);
    SetMapMode(hdc, MM_LOMETRIC);
    expect_LPtoDP(hdc, 4000, -500);
    expect_viewport_ext(hdc, 8000, -1000);
    expect_window_ext(hdc, 2000, 2000);

    r = pSetVirtualResolution(hdc, 8000, 2000, 200, 200); /* 40 pix/mm x 10 pix/mm */
    ok(r == TRUE, "got %d\n", r);
    SetMapMode(hdc, MM_TEXT);
    SetMapMode(hdc, MM_LOMETRIC);
    expect_LPtoDP(hdc, 4000, -1000);
    expect_viewport_ext(hdc, 8000, -2000);
    expect_window_ext(hdc, 2000, 2000);

    r = pSetVirtualResolution(hdc, 0, 0, 10, 0); /* Error */
    ok(r == FALSE, "got %d\n", r);
    SetMapMode(hdc, MM_TEXT);
    SetMapMode(hdc, MM_LOMETRIC);
    expect_LPtoDP(hdc, 4000, -1000);
    expect_viewport_ext(hdc, 8000, -2000);
    expect_window_ext(hdc, 2000, 2000);

    r = pSetVirtualResolution(hdc, 0, 0, 0, 0); /* Reset to true resolution */
    ok(r == TRUE, "got %d\n", r);
    SetMapMode(hdc, MM_TEXT);
    SetMapMode(hdc, MM_LOMETRIC);
    expect_viewport_ext(hdc, orig_lometric_vp.cx, orig_lometric_vp.cy);
    expect_window_ext(hdc, orig_lometric_wnd.cx, orig_lometric_wnd.cy);

    DeleteDC(hdc);
}
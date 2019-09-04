#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_9__   TYPE_3__ ;
typedef  struct TYPE_8__   TYPE_2__ ;
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
struct TYPE_9__ {int X; int Y; int Width; int Height; } ;
struct TYPE_8__ {int X; int Y; int Width; int Height; } ;
struct TYPE_7__ {int left; int top; int right; int bottom; } ;
typedef  TYPE_1__ RECT ;
typedef  int /*<<< orphan*/  PAINTSTRUCT ;
typedef  int /*<<< orphan*/  HDC ;
typedef  int /*<<< orphan*/  GpStatus ;
typedef  TYPE_2__ GpRectF ;
typedef  TYPE_3__ GpRect ;
typedef  int /*<<< orphan*/  GpGraphics ;

/* Variables and functions */
 int /*<<< orphan*/  BeginPaint (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  CombineModeReplace ; 
 int /*<<< orphan*/  EndPaint (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  GdipCreateFromHDC (int /*<<< orphan*/ ,int /*<<< orphan*/ **) ; 
 int /*<<< orphan*/  GdipDeleteGraphics (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  GdipGetVisibleClipBounds (int /*<<< orphan*/ *,TYPE_2__*) ; 
 int /*<<< orphan*/  GdipGetVisibleClipBoundsI (int /*<<< orphan*/ *,TYPE_3__*) ; 
 int /*<<< orphan*/  GdipResetClip (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  GdipScaleWorldTransform (int /*<<< orphan*/ *,double,double,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  GdipSetClipRect (int /*<<< orphan*/ *,int,int,int,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  GetClientRect (int /*<<< orphan*/ ,TYPE_1__*) ; 
 int /*<<< orphan*/  MatrixOrderPrepend ; 
 int /*<<< orphan*/  Ok ; 
 int /*<<< orphan*/  expect (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  hwnd ; 
 int /*<<< orphan*/  ok (int,char*,...) ; 

__attribute__((used)) static void test_GdipGetVisibleClipBounds_window(void)
{
    GpStatus status;
    GpGraphics *graphics = NULL;
    GpRectF rectf, window, exp, clipr;
    GpRect recti;
    HDC hdc;
    PAINTSTRUCT ps;
    RECT wnd_rect;

    /* get client area size */
    ok(GetClientRect(hwnd, &wnd_rect), "GetClientRect should have succeeded\n");
    window.X = wnd_rect.left;
    window.Y = wnd_rect.top;
    window.Width = wnd_rect.right - wnd_rect.left;
    window.Height = wnd_rect.bottom - wnd_rect.top;

    hdc = BeginPaint(hwnd, &ps);

    status = GdipCreateFromHDC(hdc, &graphics);
    expect(Ok, status);
    ok(graphics != NULL, "Expected graphics to be initialized\n");

    status = GdipGetVisibleClipBounds(graphics, &rectf);
    expect(Ok, status);
    ok(rectf.X == window.X &&
        rectf.Y == window.Y &&
        rectf.Width == window.Width &&
        rectf.Height == window.Height,
        "Expected clip bounds (%0.f, %0.f, %0.f, %0.f) to be the size of "
        "the window (%0.f, %0.f, %0.f, %0.f)\n",
        rectf.X, rectf.Y, rectf.Width, rectf.Height,
        window.X, window.Y, window.Width, window.Height);

    /* clipping rect entirely within window */
    exp.X = clipr.X = 20;
    exp.Y = clipr.Y = 8;
    exp.Width = clipr.Width = 30;
    exp.Height = clipr.Height = 20;

    status = GdipSetClipRect(graphics, clipr.X, clipr.Y, clipr.Width, clipr.Height, CombineModeReplace);
    expect(Ok, status);

    status = GdipGetVisibleClipBounds(graphics, &rectf);
    expect(Ok, status);
    ok(rectf.X == exp.X &&
        rectf.Y == exp.Y &&
        rectf.Width == exp.Width &&
        rectf.Height == exp.Height,
        "Expected clip bounds (%0.f, %0.f, %0.f, %0.f) to be the size of "
        "the clipping rect (%0.f, %0.f, %0.f, %0.f)\n",
        rectf.X, rectf.Y, rectf.Width, rectf.Height,
        exp.X, exp.Y, exp.Width, exp.Height);

    /* clipping rect partially outside of window */
    clipr.X = window.Width - 10;
    clipr.Y = window.Height - 15;
    clipr.Width = 20;
    clipr.Height = 30;

    status = GdipSetClipRect(graphics, clipr.X, clipr.Y, clipr.Width, clipr.Height, CombineModeReplace);
    expect(Ok, status);

    exp.X = window.Width - 10;
    exp.Y = window.Height - 15;
    exp.Width = 10;
    exp.Height = 15;

    status = GdipGetVisibleClipBounds(graphics, &rectf);
    expect(Ok, status);
    ok(rectf.X == exp.X &&
        rectf.Y == exp.Y &&
        rectf.Width == exp.Width &&
        rectf.Height == exp.Height,
        "Expected clip bounds (%0.f, %0.f, %0.f, %0.f) to be the size of "
        "the visible clipping rect (%0.f, %0.f, %0.f, %0.f)\n",
        rectf.X, rectf.Y, rectf.Width, rectf.Height,
        exp.X, exp.Y, exp.Width, exp.Height);

    status = GdipGetVisibleClipBoundsI(graphics, &recti);
    expect(Ok, status);
    ok(recti.X == exp.X &&
        recti.Y == exp.Y &&
        recti.Width == exp.Width &&
        recti.Height == exp.Height,
        "Expected clip bounds (%d, %d, %d, %d) to be the size of "
        "the visible clipping rect (%0.f, %0.f, %0.f, %0.f)\n",
        recti.X, recti.Y, recti.Width, recti.Height,
        exp.X, exp.Y, exp.Width, exp.Height);

    /* window bounds with transform applied */
    status = GdipResetClip(graphics);
    expect(Ok, status);

    status = GdipScaleWorldTransform(graphics, 0.5, 0.5, MatrixOrderPrepend);
    expect(Ok, status);

    exp.X = window.X * 2.0;
    exp.Y = window.Y * 2.0;
    exp.Width = window.Width * 2.0;
    exp.Height = window.Height * 2.0;

    status = GdipGetVisibleClipBounds(graphics, &rectf);
    expect(Ok, status);
    ok(rectf.X == exp.X &&
        rectf.Y == exp.Y &&
        rectf.Width == exp.Width &&
        rectf.Height == exp.Height,
        "Expected clip bounds (%0.f, %0.f, %0.f, %0.f) to be "
        "twice the window size (%0.f, %0.f, %0.f, %0.f)\n",
        rectf.X, rectf.Y, rectf.Width, rectf.Height,
        exp.X, exp.Y, exp.Width, exp.Height);

    GdipDeleteGraphics(graphics);
    EndPaint(hwnd, &ps);
}
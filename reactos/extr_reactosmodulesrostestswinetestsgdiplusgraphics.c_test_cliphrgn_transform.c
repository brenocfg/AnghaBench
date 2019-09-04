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
struct TYPE_3__ {int /*<<< orphan*/  Height; int /*<<< orphan*/  Width; int /*<<< orphan*/  Y; int /*<<< orphan*/  X; } ;
typedef  TYPE_1__ RectF ;
typedef  int /*<<< orphan*/  HRGN ;
typedef  int /*<<< orphan*/  HDC ;
typedef  int /*<<< orphan*/  GpStatus ;
typedef  int /*<<< orphan*/  GpGraphics ;
typedef  int /*<<< orphan*/  BOOL ;

/* Variables and functions */
 int /*<<< orphan*/  CombineModeReplace ; 
 int /*<<< orphan*/  CreateRectRgn (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,int) ; 
 int /*<<< orphan*/  DeleteObject (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  FALSE ; 
 int /*<<< orphan*/  GdipCreateFromHDC (int /*<<< orphan*/ ,int /*<<< orphan*/ **) ; 
 int /*<<< orphan*/  GdipDeleteGraphics (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  GdipGetVisibleClipBounds (int /*<<< orphan*/ *,TYPE_1__*) ; 
 int /*<<< orphan*/  GdipIsVisiblePoint (int /*<<< orphan*/ *,int,int,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  GdipSetClipHrgn (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  GetDC (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  Ok ; 
 int /*<<< orphan*/  ReleaseDC (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  SetViewportOrgEx (int /*<<< orphan*/ ,int,int,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  TRUE ; 
 int /*<<< orphan*/  expect (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  expectf (double,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  hwnd ; 

__attribute__((used)) static void test_cliphrgn_transform(void)
{
    HDC hdc;
    GpStatus status;
    GpGraphics *graphics;
    HRGN rgn;
    RectF rectf;
    BOOL res;

    hdc = GetDC(hwnd);

    SetViewportOrgEx(hdc, 10, 10, NULL);

    status = GdipCreateFromHDC(hdc, &graphics);
    expect(Ok, status);

    rgn = CreateRectRgn(0, 0, 100, 100);

    status = GdipSetClipHrgn(graphics, rgn, CombineModeReplace);
    expect(Ok, status);

    status = GdipGetVisibleClipBounds(graphics, &rectf);
    expect(Ok, status);
    expectf(-10.0, rectf.X);
    expectf(-10.0, rectf.Y);
    expectf(100.0, rectf.Width);
    expectf(100.0, rectf.Height);

    status = GdipIsVisiblePoint(graphics, 95, 95, &res);
    expect(Ok, status);
    expect(FALSE, res);

    status = GdipIsVisiblePoint(graphics, -5, -5, &res);
    expect(Ok, status);
    expect(TRUE, res);

    DeleteObject(rgn);

    GdipDeleteGraphics(graphics);

    SetViewportOrgEx(hdc, 0, 0, NULL);

    ReleaseDC(hwnd, hdc);
}
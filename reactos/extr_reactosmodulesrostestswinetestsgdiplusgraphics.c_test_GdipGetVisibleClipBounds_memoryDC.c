#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct TYPE_6__ {scalar_t__ X; scalar_t__ Y; int Width; int Height; } ;
struct TYPE_5__ {int right; int left; int bottom; int top; } ;
typedef  TYPE_1__ RECT ;
typedef  int /*<<< orphan*/  POINT ;
typedef  int /*<<< orphan*/  HGDIOBJ ;
typedef  int /*<<< orphan*/  HDC ;
typedef  int /*<<< orphan*/  HBITMAP ;
typedef  int /*<<< orphan*/  GpStatus ;
typedef  TYPE_2__ GpRect ;
typedef  int /*<<< orphan*/  GpGraphics ;

/* Variables and functions */
 int /*<<< orphan*/  CombineModeReplace ; 
 int /*<<< orphan*/  CreateCompatibleBitmap (int /*<<< orphan*/ ,int,int) ; 
 int /*<<< orphan*/  CreateCompatibleDC (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  DeleteDC (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  DeleteObject (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  GdipCreateFromHDC (int /*<<< orphan*/ ,int /*<<< orphan*/ **) ; 
 int /*<<< orphan*/  GdipDeleteGraphics (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  GdipGetVisibleClipBoundsI (int /*<<< orphan*/ *,TYPE_2__*) ; 
 int /*<<< orphan*/  GdipSetClipRectI (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,int,int /*<<< orphan*/ ) ; 
 int GetClientRect (int /*<<< orphan*/ ,TYPE_1__*) ; 
 int /*<<< orphan*/  GetDC (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  Ok ; 
 int /*<<< orphan*/  ReleaseDC (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  SelectObject (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  SetWindowOrgEx (int /*<<< orphan*/ ,int,int,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  expect (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  hwnd ; 
 int /*<<< orphan*/  ok (int,char*) ; 

__attribute__((used)) static void test_GdipGetVisibleClipBounds_memoryDC(void)
{
    HDC hdc,dc;
    HBITMAP bmp;
    HGDIOBJ old;
    RECT rect;
    POINT pt;
    int width = 0;
    int height = 0;
    GpGraphics* graphics = NULL;
    GpRect boundRect;
    GpStatus status;

    ok(GetClientRect(hwnd, &rect), "GetClientRect should have succeeded\n");
    width = rect.right - rect.left;
    height = rect.bottom - rect.top;

    dc = GetDC(hwnd);
    hdc = CreateCompatibleDC ( dc );
    bmp = CreateCompatibleBitmap ( dc, width, height );
    old = SelectObject (hdc, bmp);

    /*change the window origin is the key test point*/
    SetWindowOrgEx (hdc, rect.left+10, rect.top+10, &pt);

    status = GdipCreateFromHDC(hdc, &graphics);
    expect(Ok, status);

    status = GdipGetVisibleClipBoundsI(graphics, &boundRect);
    expect(Ok, status);

    ok(boundRect.X==rect.left+10 &&
       boundRect.Y==rect.top+10 &&
       boundRect.Width==width &&
       boundRect.Height==height, "Expected GdipGetVisibleClipBoundsI ok\n");

    status = GdipSetClipRectI(graphics, 0, 0, width, height, CombineModeReplace);
    expect(Ok, status);

    status = GdipGetVisibleClipBoundsI(graphics, &boundRect);
    expect(Ok, status);

    ok(boundRect.X==rect.left+10 &&
       boundRect.Y==rect.top+10 &&
       boundRect.Width==width-10 &&
       boundRect.Height==height-10, "Expected GdipGetVisibleClipBoundsI ok\n");

    GdipDeleteGraphics(graphics);

    SelectObject (hdc, old);
    DeleteObject (bmp);
    DeleteDC (hdc);
    ReleaseDC(hwnd, dc);
}
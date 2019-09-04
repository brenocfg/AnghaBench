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
typedef  int UINT ;
struct TYPE_5__ {int /*<<< orphan*/  member_1; int /*<<< orphan*/  member_0; } ;
struct TYPE_4__ {int member_0; int member_1; int member_2; int member_3; int right; int left; int bottom; int top; } ;
typedef  TYPE_1__ RECT ;
typedef  TYPE_2__ POINT ;
typedef  int /*<<< orphan*/  HGDIOBJ ;
typedef  int /*<<< orphan*/  HDC ;
typedef  int /*<<< orphan*/  HBITMAP ;
typedef  int /*<<< orphan*/  GpStatus ;
typedef  int /*<<< orphan*/  GpSolidFill ;
typedef  int /*<<< orphan*/  GpGraphics ;
typedef  int /*<<< orphan*/  GpBrush ;
typedef  int /*<<< orphan*/  DWORD ;
typedef  scalar_t__ ARGB ;

/* Variables and functions */
 int /*<<< orphan*/  BLUE_COLOR ; 
 int /*<<< orphan*/  CombineModeReplace ; 
 int /*<<< orphan*/  CreateCompatibleBitmap (int /*<<< orphan*/ ,int,int) ; 
 int /*<<< orphan*/  CreateCompatibleDC (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  DeleteDC (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  DeleteObject (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  GdipCreateFromHDC (int /*<<< orphan*/ ,int /*<<< orphan*/ **) ; 
 int /*<<< orphan*/  GdipCreateSolidFill (int /*<<< orphan*/ ,int /*<<< orphan*/ **) ; 
 int /*<<< orphan*/  GdipDeleteBrush (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  GdipDeleteGraphics (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  GdipFillRectangleI (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,int) ; 
 int /*<<< orphan*/  GdipFree (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  GdipSetClipRectI (int /*<<< orphan*/ *,int,int,int,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * GetBitmapPixelBuffer (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,int) ; 
 int /*<<< orphan*/  GetDC (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  Ok ; 
 int /*<<< orphan*/  ReleaseDC (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  SelectObject (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  SetWindowOrgEx (int /*<<< orphan*/ ,int,int,TYPE_2__*) ; 
 int /*<<< orphan*/  expect (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ get_bitmap_pixel (int,int) ; 
 int /*<<< orphan*/  hwnd ; 
 scalar_t__ is_blue_color (scalar_t__) ; 
 int /*<<< orphan*/  ok (int,char*) ; 

__attribute__((used)) static void test_GdipFillRectanglesOnMemoryDCSolidBrush(void)
{
    ARGB color[6] = {0,0,0,0,0,0};
    POINT pt = {0,0};
    RECT rect = {100, 100, 180, 180};
    UINT width = rect.right - rect.left;
    UINT height = rect.bottom - rect.top;
    GpStatus status = 0;
    GpSolidFill *brush = NULL;
    GpGraphics *graphics = NULL;
    HDC dc = GetDC( hwnd);
    HDC hdc = CreateCompatibleDC(dc);
    HBITMAP bmp = CreateCompatibleBitmap(dc, width, height);
    HGDIOBJ old = SelectObject(hdc, bmp);
    DWORD* pixel = NULL;

    /*Change the window origin is the key test point*/
    SetWindowOrgEx(hdc, rect.left, rect.top, &pt);

    status = GdipCreateSolidFill(BLUE_COLOR, &brush);
    expect(Ok, status);

    status = GdipCreateFromHDC(hdc, &graphics);
    expect(Ok, status);

    status = GdipSetClipRectI(graphics, rect.left+width/2, rect.top+height/2,
            width, height, CombineModeReplace);
    expect(Ok, status);

    status = GdipFillRectangleI(graphics, (GpBrush*)brush, 0, 0, rect.right, rect.bottom);
    expect(Ok, status);

    GdipDeleteBrush((GpBrush*)brush);
    GdipDeleteGraphics(graphics);

    pixel = GetBitmapPixelBuffer(hdc, bmp, width, height);
    if (pixel)
    {
       color[0] = get_bitmap_pixel(width/2, height/2);
       color[1] = get_bitmap_pixel(width/2+1, height/2);
       color[2] = get_bitmap_pixel(width/2, height/2+1);
       color[3] = get_bitmap_pixel(width/2-1, height/2-1);
       color[4] = get_bitmap_pixel(width/2-1, height-1);
       color[5] = get_bitmap_pixel(width-1, height/2-1);
    }

    ok(is_blue_color(color[0]) && is_blue_color(color[1]) && is_blue_color(color[2]) &&
       color[3] == 0 && color[4] == 0 && color[5] == 0,
       "Expected GdipFillRectangleI take effect!\n" );
    GdipFree(pixel);

    SelectObject(hdc, old);
    DeleteObject(bmp);
    DeleteDC(hdc);
    ReleaseDC(hwnd, dc);
}
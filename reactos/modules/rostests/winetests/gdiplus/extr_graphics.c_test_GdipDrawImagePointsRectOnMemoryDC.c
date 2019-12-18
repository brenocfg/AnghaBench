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
typedef  int /*<<< orphan*/  GpImage ;
typedef  int /*<<< orphan*/  GpGraphics ;
typedef  int /*<<< orphan*/  GpBitmap ;
typedef  int /*<<< orphan*/  DWORD ;
typedef  int /*<<< orphan*/  BYTE ;
typedef  scalar_t__ ARGB ;

/* Variables and functions */
 int /*<<< orphan*/  BLUE_COLOR ; 
 int /*<<< orphan*/  CreateCompatibleBitmap (int /*<<< orphan*/ ,int,int) ; 
 int /*<<< orphan*/  CreateCompatibleDC (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  DeleteDC (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  DeleteObject (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * GdipAlloc (int) ; 
 int /*<<< orphan*/  GdipCreateBitmapFromScan0 (int,int,int,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ **) ; 
 int /*<<< orphan*/  GdipCreateFromHDC (int /*<<< orphan*/ ,int /*<<< orphan*/ **) ; 
 int /*<<< orphan*/  GdipDeleteGraphics (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  GdipDisposeImage (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  GdipDrawImageRectRectI (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int,int,int,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,int,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  GdipFree (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * GetBitmapPixelBuffer (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,int) ; 
 int /*<<< orphan*/  GetDC (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  Ok ; 
 int /*<<< orphan*/  PixelFormat32bppARGB ; 
 int /*<<< orphan*/  ReleaseDC (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  SelectObject (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  SetWindowOrgEx (int /*<<< orphan*/ ,int,int,TYPE_2__*) ; 
 int /*<<< orphan*/  UnitPixel ; 
 int /*<<< orphan*/  expect (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ get_bitmap_pixel (int,int) ; 
 int /*<<< orphan*/  hwnd ; 
 scalar_t__ is_blue_color (scalar_t__) ; 
 int /*<<< orphan*/  ok (int,char*) ; 

__attribute__((used)) static void test_GdipDrawImagePointsRectOnMemoryDC(void)
{
    ARGB color[6] = {0,0,0,0,0,0};
    POINT pt = {0,0};
    RECT rect = {100, 100, 180, 180};
    UINT width = rect.right - rect.left;
    UINT height = rect.bottom - rect.top;
    GpStatus status = 0;
    union
    {
        GpBitmap *bitmap;
        GpImage *image;
    } src_img;
    GpGraphics *graphics = NULL;
    HDC dc = GetDC( hwnd);
    HDC hdc = CreateCompatibleDC(dc);
    HBITMAP bmp = CreateCompatibleBitmap(dc, width, height);
    HGDIOBJ old = SelectObject(hdc, bmp);

    UINT x = 0;
    UINT y = 0;
    UINT src_img_width = width/2;
    UINT src_img_height = height/2;
    BYTE *src_img_data = GdipAlloc(src_img_width*src_img_height*4);
    DWORD *pixel = (DWORD *)src_img_data;
    ok(pixel != NULL, "Expected src_img_data is valid\n");

    /*Change the window origin is the key test point*/
    SetWindowOrgEx(hdc, rect.left, rect.top, &pt);

    /*build a blue solid image!*/
    for(y = 0; y < src_img_height; ++y)
    {
        for(x = 0; x < src_img_width; ++x)
        {
            pixel[x] = BLUE_COLOR;
        }

        pixel += src_img_width;
    }

    status = GdipCreateBitmapFromScan0(src_img_width, src_img_height, src_img_width*4,
            PixelFormat32bppARGB, src_img_data, &src_img.bitmap);
    expect(Ok, status);

    status = GdipCreateFromHDC(hdc, &graphics);
    expect(Ok, status);

    status = GdipDrawImageRectRectI(graphics, src_img.image,
            rect.left+width/2, rect.top+height/2, width/2, height/2,
            0, 0, src_img_width, src_img_height, UnitPixel, NULL, NULL, NULL);
    expect(Ok, status);

    GdipDisposeImage(src_img.image);
    GdipDeleteGraphics(graphics);
    GdipFree(src_img_data);

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
       "Expected GdipDrawImageRectRectI take effect!\n" );
    GdipFree(pixel);

    SelectObject(hdc, old);
    DeleteObject(bmp);
    DeleteDC(hdc);
    ReleaseDC(hwnd, dc);
}
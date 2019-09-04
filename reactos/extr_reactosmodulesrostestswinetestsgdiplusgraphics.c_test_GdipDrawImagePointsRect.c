#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_11__   TYPE_4__ ;
typedef  struct TYPE_10__   TYPE_2__ ;
typedef  struct TYPE_9__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  rbmi ;
typedef  int /*<<< orphan*/  ptf ;
struct TYPE_9__ {int biSize; int biWidth; int biHeight; int biPlanes; int biBitCount; int /*<<< orphan*/  biCompression; } ;
struct TYPE_11__ {TYPE_1__ bmiHeader; } ;
struct TYPE_10__ {int X; int Y; } ;
typedef  int /*<<< orphan*/  HDC ;
typedef  int /*<<< orphan*/  GpStatus ;
typedef  TYPE_2__ GpPointF ;
typedef  int /*<<< orphan*/  GpImage ;
typedef  int /*<<< orphan*/  GpGraphics ;
typedef  int /*<<< orphan*/  GpBitmap ;
typedef  TYPE_2__ BYTE ;
typedef  int /*<<< orphan*/  BITMAPINFOHEADER ;
typedef  TYPE_4__ BITMAPINFO ;

/* Variables and functions */
 int /*<<< orphan*/  BI_RGB ; 
 int /*<<< orphan*/  GdipCreateBitmapFromGdiDib (TYPE_4__*,TYPE_2__*,int /*<<< orphan*/ **) ; 
 int /*<<< orphan*/  GdipCreateFromHDC (int /*<<< orphan*/ ,int /*<<< orphan*/ **) ; 
 int /*<<< orphan*/  GdipDeleteGraphics (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  GdipDisposeImage (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  GdipDrawImagePointsRect (int /*<<< orphan*/ *,int /*<<< orphan*/ *,TYPE_2__*,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,int,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  GetDC (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  InvalidParameter ; 
 int /*<<< orphan*/  NotImplemented ; 
 int /*<<< orphan*/  Ok ; 
 int /*<<< orphan*/  ReleaseDC (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  UnitPixel ; 
 int /*<<< orphan*/  expect (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  hwnd ; 
 int /*<<< orphan*/  memset (TYPE_2__*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  ok (int,char*) ; 

__attribute__((used)) static void test_GdipDrawImagePointsRect(void)
{
    GpStatus status;
    GpGraphics *graphics = NULL;
    GpPointF ptf[4];
    GpBitmap *bm = NULL;
    BYTE rbmi[sizeof(BITMAPINFOHEADER)];
    BYTE buff[400];
    BITMAPINFO *bmi = (BITMAPINFO*)rbmi;
    HDC hdc = GetDC( hwnd );
    if (!hdc)
        return;

    memset(rbmi, 0, sizeof(rbmi));
    bmi->bmiHeader.biSize = sizeof(BITMAPINFOHEADER);
    bmi->bmiHeader.biWidth = 10;
    bmi->bmiHeader.biHeight = 10;
    bmi->bmiHeader.biPlanes = 1;
    bmi->bmiHeader.biBitCount = 32;
    bmi->bmiHeader.biCompression = BI_RGB;
    status = GdipCreateBitmapFromGdiDib(bmi, buff, &bm);
    expect(Ok, status);
    ok(NULL != bm, "Expected bitmap to be initialized\n");
    status = GdipCreateFromHDC(hdc, &graphics);
    expect(Ok, status);
    ptf[0].X = 0;
    ptf[0].Y = 0;
    ptf[1].X = 10;
    ptf[1].Y = 0;
    ptf[2].X = 0;
    ptf[2].Y = 10;
    ptf[3].X = 10;
    ptf[3].Y = 10;
    status = GdipDrawImagePointsRect(graphics, (GpImage*)bm, ptf, 4, 0, 0, 10, 10, UnitPixel, NULL, NULL, NULL);
    expect(NotImplemented, status);
    status = GdipDrawImagePointsRect(graphics, (GpImage*)bm, ptf, 2, 0, 0, 10, 10, UnitPixel, NULL, NULL, NULL);
    expect(InvalidParameter, status);
    status = GdipDrawImagePointsRect(graphics, (GpImage*)bm, ptf, 3, 0, 0, 10, 10, UnitPixel, NULL, NULL, NULL);
    expect(Ok, status);
    status = GdipDrawImagePointsRect(graphics, NULL, ptf, 3, 0, 0, 10, 10, UnitPixel, NULL, NULL, NULL);
    expect(InvalidParameter, status);
    status = GdipDrawImagePointsRect(graphics, (GpImage*)bm, NULL, 3, 0, 0, 10, 10, UnitPixel, NULL, NULL, NULL);
    expect(InvalidParameter, status);
    status = GdipDrawImagePointsRect(graphics, (GpImage*)bm, ptf, 3, 0, 0, 0, 0, UnitPixel, NULL, NULL, NULL);
    expect(Ok, status);
    memset(ptf, 0, sizeof(ptf));
    status = GdipDrawImagePointsRect(graphics, (GpImage*)bm, ptf, 3, 0, 0, 10, 10, UnitPixel, NULL, NULL, NULL);
    expect(Ok, status);

    GdipDisposeImage((GpImage*)bm);
    GdipDeleteGraphics(graphics);
    ReleaseDC(hwnd, hdc);
}
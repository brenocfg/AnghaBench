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
typedef  int /*<<< orphan*/  ULONG ;
struct TYPE_4__ {int biSize; int biHeight; int biWidth; int biBitCount; int biPlanes; scalar_t__ biClrUsed; int /*<<< orphan*/  biCompression; } ;
struct TYPE_5__ {TYPE_1__ bmiHeader; } ;
typedef  int /*<<< orphan*/ * HRGN ;
typedef  int /*<<< orphan*/ * HDC ;
typedef  int /*<<< orphan*/ * HBITMAP ;
typedef  int /*<<< orphan*/  GpStatus ;
typedef  int /*<<< orphan*/  GpSolidFill ;
typedef  int /*<<< orphan*/  GpGraphics ;
typedef  int /*<<< orphan*/  GpBrush ;
typedef  TYPE_2__ BITMAPINFO ;
typedef  int /*<<< orphan*/  ARGB ;

/* Variables and functions */
 int /*<<< orphan*/  BI_RGB ; 
 int /*<<< orphan*/ * CreateCompatibleDC (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * CreateDIBSection (int /*<<< orphan*/ *,TYPE_2__*,int /*<<< orphan*/ ,void**,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * CreateRectRgn (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,int) ; 
 int /*<<< orphan*/  DIB_RGB_COLORS ; 
 int /*<<< orphan*/  DeleteDC (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  DeleteObject (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  GdipCreateFromHDC (int /*<<< orphan*/ *,int /*<<< orphan*/ **) ; 
 int /*<<< orphan*/  GdipCreateSolidFill (int /*<<< orphan*/ ,int /*<<< orphan*/ **) ; 
 int /*<<< orphan*/  GdipDeleteBrush (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  GdipDeleteGraphics (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  GdipFillRectangleI (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,int) ; 
 int /*<<< orphan*/  OffsetClipRgn (int /*<<< orphan*/ *,int,int) ; 
 int Ok ; 
 int /*<<< orphan*/  SelectClipRgn (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  SelectObject (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  SetViewportOrgEx (int /*<<< orphan*/ *,int,int,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  expect (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  memset (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  ok (int /*<<< orphan*/ ,char*) ; 

__attribute__((used)) static void test_hdc_caching(void)
{
    GpStatus status;
    HDC hdc;
    HBITMAP hbm;
    GpGraphics *graphics;
    ULONG *bits;
    BITMAPINFO bmi;
    HRGN hrgn;
    GpBrush *brush;

    hdc = CreateCompatibleDC(0);
    ok(hdc != NULL, "CreateCompatibleDC failed\n");
    bmi.bmiHeader.biSize = sizeof(bmi.bmiHeader);
    bmi.bmiHeader.biHeight = -5;
    bmi.bmiHeader.biWidth = 5;
    bmi.bmiHeader.biBitCount = 32;
    bmi.bmiHeader.biPlanes = 1;
    bmi.bmiHeader.biCompression = BI_RGB;
    bmi.bmiHeader.biClrUsed = 0;

    hbm = CreateDIBSection(hdc, &bmi, DIB_RGB_COLORS, (void**)&bits, NULL, 0);
    ok(hbm != NULL, "CreateDIBSection failed\n");

    SelectObject(hdc, hbm);

    SetViewportOrgEx(hdc, 1, 1, NULL);

    hrgn = CreateRectRgn(0, 0, 3, 3);
    SelectClipRgn(hdc, hrgn);
    DeleteObject(hrgn);

    status = GdipCreateSolidFill((ARGB)0xffaaaaaa, (GpSolidFill**)&brush);
    expect(Ok, status);

    status = GdipCreateFromHDC(hdc, &graphics);
    expect(Ok, status);

    memset(bits, 0, sizeof(*bits) * 25);
    status = GdipFillRectangleI(graphics, brush, 0, 0, 4, 4);
    expect(Ok, status);

    expect(0, bits[0]);
    expect(0xffaaaaaa, bits[6]);
    expect(0xffaaaaaa, bits[12]);
    expect(0, bits[18]);
    expect(0, bits[24]);

    SetViewportOrgEx(hdc, 0, 0, NULL);
    OffsetClipRgn(hdc, 2, 2);

    memset(bits, 0, sizeof(*bits) * 25);
    status = GdipFillRectangleI(graphics, brush, 0, 0, 4, 4);
    expect(Ok, status);

    expect(0, bits[0]);
    expect(0xffaaaaaa, bits[6]);
    expect(0xffaaaaaa, bits[12]);
    expect(0, bits[18]);
    expect(0, bits[24]);

    GdipDeleteGraphics(graphics);

    GdipDeleteBrush(brush);

    DeleteDC(hdc);
    DeleteObject(hbm);
}
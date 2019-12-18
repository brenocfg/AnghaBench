#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_10__   TYPE_2__ ;
typedef  struct TYPE_9__   TYPE_1__ ;

/* Type definitions */
typedef  char WCHAR ;
struct TYPE_10__ {double member_0; double member_1; } ;
struct TYPE_9__ {double member_0; double member_1; double member_2; double member_3; } ;
typedef  int /*<<< orphan*/  HENHMETAFILE ;
typedef  int /*<<< orphan*/  HDC ;
typedef  int /*<<< orphan*/  HBRUSH ;
typedef  int GpStatus ;
typedef  TYPE_1__ GpRectF ;
typedef  TYPE_2__ GpPointF ;
typedef  int /*<<< orphan*/  GpMetafile ;
typedef  int /*<<< orphan*/  GpImage ;
typedef  int /*<<< orphan*/  GpGraphics ;
typedef  int /*<<< orphan*/  GpBitmap ;
typedef  scalar_t__ BOOL ;
typedef  int ARGB ;

/* Variables and functions */
 int /*<<< orphan*/  CreateCompatibleDC (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  CreateSolidBrush (int) ; 
 int /*<<< orphan*/  DeleteDC (int /*<<< orphan*/ ) ; 
 scalar_t__ DeleteEnhMetaFile (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  DeleteObject (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  EmfTypeEmfPlusOnly ; 
 int GdipBitmapGetPixel (int /*<<< orphan*/ *,int,int,int*) ; 
 int GdipBitmapSetPixel (int /*<<< orphan*/ *,int,int,int /*<<< orphan*/ ) ; 
 int GdipCreateBitmapFromScan0 (int,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ **) ; 
 int GdipDeleteGraphics (int /*<<< orphan*/ *) ; 
 int GdipDisposeImage (int /*<<< orphan*/ *) ; 
 int GdipDrawImagePointsRect (int /*<<< orphan*/ *,int /*<<< orphan*/ *,TYPE_2__ const*,int,double,double,double,double,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int GdipGetDC (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int GdipGetHemfFromMetafile (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int GdipGetImageGraphicsContext (int /*<<< orphan*/ *,int /*<<< orphan*/ **) ; 
 int GdipRecordMetafile (int /*<<< orphan*/ ,int /*<<< orphan*/ ,TYPE_1__ const*,int /*<<< orphan*/ ,char const*,int /*<<< orphan*/ **) ; 
 int GdipReleaseDC (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int InvalidParameter ; 
 int /*<<< orphan*/  MetafileFrameUnitPixel ; 
 int Ok ; 
 int /*<<< orphan*/  PixelFormat32bppARGB ; 
 int /*<<< orphan*/  Rectangle (int /*<<< orphan*/ ,int,int,int,int) ; 
 int /*<<< orphan*/  SelectObject (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  UnitPixel ; 
 int /*<<< orphan*/  check_emfplus (int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  check_metafile (int /*<<< orphan*/ *,int /*<<< orphan*/ ,char*,TYPE_2__ const*,TYPE_1__ const*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  expect (int,int) ; 
 int /*<<< orphan*/  getdc_records ; 
 int /*<<< orphan*/  ok (int,char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  play_metafile (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ ,char*,TYPE_2__ const*,TYPE_1__ const*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  sync_metafile (int /*<<< orphan*/ **,char*) ; 

__attribute__((used)) static void test_getdc(void)
{
    GpStatus stat;
    GpMetafile *metafile;
    GpGraphics *graphics;
    HDC hdc, metafile_dc;
    HENHMETAFILE hemf;
    BOOL ret;
    static const GpRectF frame = {0.0, 0.0, 100.0, 100.0};
    static const GpPointF dst_points[3] = {{0.0,0.0},{100.0,0.0},{0.0,100.0}};
    static const GpPointF dst_points_half[3] = {{0.0,0.0},{50.0,0.0},{0.0,50.0}};
    static const WCHAR description[] = {'w','i','n','e','t','e','s','t',0};
    HBRUSH hbrush, holdbrush;
    GpBitmap *bitmap;
    ARGB color;

    hdc = CreateCompatibleDC(0);

    stat = GdipRecordMetafile(hdc, EmfTypeEmfPlusOnly, &frame, MetafileFrameUnitPixel, description, &metafile);
    expect(Ok, stat);

    DeleteDC(hdc);

    if (stat != Ok)
        return;

    stat = GdipGetHemfFromMetafile(metafile, &hemf);
    expect(InvalidParameter, stat);

    stat = GdipGetImageGraphicsContext((GpImage*)metafile, &graphics);
    expect(Ok, stat);

    stat = GdipGetDC(graphics, &metafile_dc);
    expect(Ok, stat);

    if (stat != Ok)
    {
        GdipDeleteGraphics(graphics);
        GdipDisposeImage((GpImage*)metafile);
        return;
    }

    hbrush = CreateSolidBrush(0xff0000);

    holdbrush = SelectObject(metafile_dc, hbrush);

    Rectangle(metafile_dc, 25, 25, 75, 75);

    SelectObject(metafile_dc, holdbrush);

    DeleteObject(hbrush);

    stat = GdipReleaseDC(graphics, metafile_dc);
    expect(Ok, stat);

    stat = GdipDeleteGraphics(graphics);
    expect(Ok, stat);

    check_metafile(metafile, getdc_records, "getdc metafile", dst_points, &frame, UnitPixel);

    sync_metafile(&metafile, "getdc.emf");

    stat = GdipCreateBitmapFromScan0(100, 100, 0, PixelFormat32bppARGB, NULL, &bitmap);
    expect(Ok, stat);

    stat = GdipGetImageGraphicsContext((GpImage*)bitmap, &graphics);
    expect(Ok, stat);

    play_metafile(metafile, graphics, getdc_records, "getdc playback", dst_points, &frame, UnitPixel);

    stat = GdipBitmapGetPixel(bitmap, 15, 15, &color);
    expect(Ok, stat);
    expect(0, color);

    stat = GdipBitmapGetPixel(bitmap, 50, 50, &color);
    expect(Ok, stat);
    expect(0xff0000ff, color);

    stat = GdipBitmapSetPixel(bitmap, 50, 50, 0);
    expect(Ok, stat);

    play_metafile(metafile, graphics, getdc_records, "getdc playback", dst_points_half, &frame, UnitPixel);

    stat = GdipBitmapGetPixel(bitmap, 15, 15, &color);
    expect(Ok, stat);
    expect(0xff0000ff, color);

    stat = GdipBitmapGetPixel(bitmap, 50, 50, &color);
    expect(Ok, stat);
    expect(0, color);

    stat = GdipBitmapSetPixel(bitmap, 15, 15, 0);
    expect(Ok, stat);

    stat = GdipDrawImagePointsRect(graphics, (GpImage*)metafile, dst_points, 3,
        0.0, 0.0, 100.0, 100.0, UnitPixel, NULL, NULL, NULL);
    expect(Ok, stat);

    stat = GdipBitmapGetPixel(bitmap, 15, 15, &color);
    expect(Ok, stat);
    expect(0, color);

    stat = GdipBitmapGetPixel(bitmap, 50, 50, &color);
    expect(Ok, stat);
    expect(0xff0000ff, color);

    stat = GdipDeleteGraphics(graphics);
    expect(Ok, stat);

    stat = GdipDisposeImage((GpImage*)bitmap);
    expect(Ok, stat);

    stat = GdipGetHemfFromMetafile(metafile, &hemf);
    expect(Ok, stat);

    stat = GdipDisposeImage((GpImage*)metafile);
    expect(Ok, stat);

    check_emfplus(hemf, getdc_records, "getdc emf");

    ret = DeleteEnhMetaFile(hemf);
    ok(ret != 0, "Failed to delete enhmetafile %p\n", hemf);
}
#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_11__   TYPE_2__ ;
typedef  struct TYPE_10__   TYPE_1__ ;

/* Type definitions */
typedef  char WCHAR ;
struct TYPE_11__ {double member_0; double member_1; } ;
struct TYPE_10__ {double member_0; double member_1; double member_2; double member_3; int X; int Y; int Width; int Height; } ;
typedef  int /*<<< orphan*/  HDC ;
typedef  int /*<<< orphan*/  GraphicsState ;
typedef  int GpStatus ;
typedef  int /*<<< orphan*/  GpSolidFill ;
typedef  int /*<<< orphan*/  GpRegion ;
typedef  TYPE_1__ GpRectF ;
typedef  TYPE_2__ GpPointF ;
typedef  int /*<<< orphan*/  GpMetafile ;
typedef  int /*<<< orphan*/  GpImage ;
typedef  int /*<<< orphan*/  GpGraphics ;
typedef  int /*<<< orphan*/  GpBrush ;
typedef  int /*<<< orphan*/  GpBitmap ;
typedef  int ARGB ;

/* Variables and functions */
 int /*<<< orphan*/  CombineModeIntersect ; 
 int /*<<< orphan*/  CombineModeReplace ; 
 int /*<<< orphan*/  CombineModeXor ; 
 int /*<<< orphan*/  CreateCompatibleDC (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  DeleteDC (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  EmfTypeEmfPlusOnly ; 
 int GdipBitmapGetPixel (int /*<<< orphan*/ *,int,int,int*) ; 
 int GdipCreateBitmapFromScan0 (int,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ **) ; 
 int GdipCreateRegionRect (TYPE_1__*,int /*<<< orphan*/ **) ; 
 int GdipCreateSolidFill (int,int /*<<< orphan*/ **) ; 
 int GdipDeleteBrush (int /*<<< orphan*/ *) ; 
 int GdipDeleteGraphics (int /*<<< orphan*/ *) ; 
 int GdipDeleteRegion (int /*<<< orphan*/ *) ; 
 int GdipDisposeImage (int /*<<< orphan*/ *) ; 
 int GdipFillRectangle (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int,int,int,int) ; 
 int GdipGetImageGraphicsContext (int /*<<< orphan*/ *,int /*<<< orphan*/ **) ; 
 int GdipGetVisibleClipBounds (int /*<<< orphan*/ *,TYPE_1__*) ; 
 int GdipRecordMetafile (int /*<<< orphan*/ ,int /*<<< orphan*/ ,TYPE_1__ const*,int /*<<< orphan*/ ,char const*,int /*<<< orphan*/ **) ; 
 int GdipRestoreGraphics (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int GdipSaveGraphics (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int GdipSetClipRect (int /*<<< orphan*/ *,int,int,int,int,int /*<<< orphan*/ ) ; 
 int GdipSetClipRegion (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  MetafileFrameUnitPixel ; 
 int Ok ; 
 int /*<<< orphan*/  PixelFormat32bppARGB ; 
 int /*<<< orphan*/  UnitPixel ; 
 int /*<<< orphan*/  check_metafile (int /*<<< orphan*/ *,int /*<<< orphan*/ ,char*,TYPE_2__ const*,TYPE_1__ const*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  clipping_records ; 
 int /*<<< orphan*/  expect (int,int) ; 
 int /*<<< orphan*/  ok (int,char*,int) ; 
 int /*<<< orphan*/  play_metafile (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ ,char*,TYPE_2__ const*,TYPE_1__ const*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  sync_metafile (int /*<<< orphan*/ **,char*) ; 

__attribute__((used)) static void test_clipping(void)
{
    GpStatus stat;
    GpMetafile *metafile;
    GpGraphics *graphics;
    GpBitmap *bitmap;
    GpRegion *region;
    GpBrush *brush;
    GpRectF rect;
    ARGB color;
    HDC hdc;
    static const GpRectF frame = {0.0, 0.0, 100.0, 100.0};
    static const GpPointF dst_points[3] = {{0.0,0.0},{100.0,0.0},{0.0,100.0}};
    static const WCHAR description[] = {'w','i','n','e','t','e','s','t',0};
    GraphicsState state;

    hdc = CreateCompatibleDC(0);

    stat = GdipRecordMetafile(hdc, EmfTypeEmfPlusOnly, &frame, MetafileFrameUnitPixel, description, &metafile);
    expect(Ok, stat);

    DeleteDC(hdc);

    if (stat != Ok)
        return;

    stat = GdipGetImageGraphicsContext((GpImage*)metafile, &graphics);
    expect(Ok, stat);

    stat = GdipSaveGraphics(graphics, &state);
    expect(Ok, stat);

    stat = GdipGetVisibleClipBounds(graphics, &rect);
    expect(Ok, stat);
    ok(rect.X == -0x400000, "rect.X = %f\n", rect.X);
    ok(rect.Y == -0x400000, "rect.Y = %f\n", rect.Y);
    ok(rect.Width == 0x800000, "rect.Width = %f\n", rect.Width);
    ok(rect.Height == 0x800000, "rect.Height = %f\n", rect.Height);

    stat = GdipSetClipRect(graphics, 30, 30, 10, 10, CombineModeReplace);
    expect(Ok, stat);

    stat = GdipGetVisibleClipBounds(graphics, &rect);
    expect(Ok, stat);
    ok(rect.X == 30, "rect.X = %f\n", rect.X);
    ok(rect.Y == 30, "rect.Y = %f\n", rect.Y);
    ok(rect.Width == 10, "rect.Width = %f\n", rect.Width);
    ok(rect.Height == 10, "rect.Height = %f\n", rect.Height);

    stat = GdipCreateSolidFill((ARGB)0xff000000, (GpSolidFill**)&brush);
    expect(Ok, stat);

    stat = GdipFillRectangle(graphics, brush, 0, 0, 100, 100);
    expect(Ok, stat);

    stat = GdipDeleteBrush(brush);
    expect(Ok, stat);

    stat = GdipRestoreGraphics(graphics, state);
    expect(Ok, stat);

    stat = GdipSetClipRect(graphics, 30, 30, 10, 10, CombineModeXor);
    expect(Ok, stat);

    stat = GdipCreateSolidFill((ARGB)0xff0000ff, (GpSolidFill**)&brush);
    expect(Ok, stat);

    stat = GdipFillRectangle(graphics, brush, 30, 30, 20, 10);
    expect(Ok, stat);

    stat = GdipDeleteBrush(brush);
    expect(Ok, stat);

    stat = GdipCreateRegionRect(&rect, &region);
    expect(Ok, stat);

    stat = GdipSetClipRegion(graphics, region, CombineModeIntersect);
    expect(Ok, stat);

    stat = GdipDeleteRegion(region);
    expect(Ok, stat);

    stat = GdipDeleteGraphics(graphics);
    expect(Ok, stat);

    check_metafile(metafile, clipping_records, "clipping metafile", dst_points, &frame, UnitPixel);

    sync_metafile(&metafile, "clipping.emf");

    stat = GdipCreateBitmapFromScan0(100, 100, 0, PixelFormat32bppARGB, NULL, &bitmap);
    expect(Ok, stat);

    stat = GdipGetImageGraphicsContext((GpImage*)bitmap, &graphics);
    expect(Ok, stat);

    play_metafile(metafile, graphics, clipping_records, "clipping playback", dst_points, &frame, UnitPixel);

    stat = GdipBitmapGetPixel(bitmap, 80, 80, &color);
    expect(Ok, stat);
    expect(0, color);

    stat = GdipBitmapGetPixel(bitmap, 35, 35, &color);
    expect(Ok, stat);
    expect(0xff000000, color);

    stat = GdipBitmapGetPixel(bitmap, 45, 35, &color);
    expect(Ok, stat);
    expect(0xff0000ff, color);

    stat = GdipDeleteGraphics(graphics);
    expect(Ok, stat);

    stat = GdipDisposeImage((GpImage*)bitmap);
    expect(Ok, stat);

    stat = GdipDisposeImage((GpImage*)metafile);
    expect(Ok, stat);
}
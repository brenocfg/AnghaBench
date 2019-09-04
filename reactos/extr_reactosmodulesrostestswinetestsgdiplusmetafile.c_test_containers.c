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
struct TYPE_10__ {double member_0; double member_1; double member_2; double member_3; double X; double Y; double Width; double Height; } ;
typedef  double REAL ;
typedef  int /*<<< orphan*/  HDC ;
typedef  int /*<<< orphan*/  GraphicsContainer ;
typedef  int GpStatus ;
typedef  int /*<<< orphan*/  GpSolidFill ;
typedef  TYPE_1__ GpRectF ;
typedef  TYPE_2__ GpPointF ;
typedef  int /*<<< orphan*/  GpMetafile ;
typedef  int /*<<< orphan*/  GpImage ;
typedef  int /*<<< orphan*/  GpGraphics ;
typedef  int /*<<< orphan*/  GpBrush ;
typedef  int /*<<< orphan*/  GpBitmap ;
typedef  int ARGB ;

/* Variables and functions */
 int /*<<< orphan*/  CreateCompatibleDC (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  DeleteDC (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  EmfTypeEmfPlusOnly ; 
 int GdipBeginContainer (int /*<<< orphan*/ *,TYPE_1__*,TYPE_1__*,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int GdipBeginContainer2 (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int GdipBitmapGetPixel (int /*<<< orphan*/ *,int,int,int*) ; 
 int GdipCreateBitmapFromScan0 (int,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ **) ; 
 int GdipCreateSolidFill (int,int /*<<< orphan*/ **) ; 
 int GdipDeleteBrush (int /*<<< orphan*/ *) ; 
 int GdipDeleteGraphics (int /*<<< orphan*/ *) ; 
 int GdipDisposeImage (int /*<<< orphan*/ *) ; 
 int GdipEndContainer (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int GdipFillRectangle (int /*<<< orphan*/ *,int /*<<< orphan*/ *,double,double,double,double) ; 
 int GdipGetDpiX (int /*<<< orphan*/ *,double*) ; 
 int GdipGetDpiY (int /*<<< orphan*/ *,double*) ; 
 int GdipGetImageGraphicsContext (int /*<<< orphan*/ *,int /*<<< orphan*/ **) ; 
 int GdipRecordMetafile (int /*<<< orphan*/ ,int /*<<< orphan*/ ,TYPE_1__ const*,int /*<<< orphan*/ ,char const*,int /*<<< orphan*/ **) ; 
 int GdipRestoreGraphics (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int GdipSaveGraphics (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int GdipScaleWorldTransform (int /*<<< orphan*/ *,double,double,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  MatrixOrderPrepend ; 
 int /*<<< orphan*/  MetafileFrameUnitPixel ; 
 int Ok ; 
 int /*<<< orphan*/  PixelFormat32bppARGB ; 
 int /*<<< orphan*/  UnitInch ; 
 int /*<<< orphan*/  UnitPixel ; 
 int /*<<< orphan*/  check_metafile (int /*<<< orphan*/ *,int /*<<< orphan*/ ,char*,TYPE_2__ const*,TYPE_1__ const*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  container_records ; 
 int /*<<< orphan*/  expect (int,int) ; 
 int /*<<< orphan*/  play_metafile (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ ,char*,TYPE_2__ const*,TYPE_1__ const*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  sync_metafile (int /*<<< orphan*/ **,char*) ; 

__attribute__((used)) static void test_containers(void)
{
    GpStatus stat;
    GpMetafile *metafile;
    GpGraphics *graphics;
    GpBitmap *bitmap;
    GpBrush *brush;
    ARGB color;
    HDC hdc;
    static const GpRectF frame = {0.0, 0.0, 100.0, 100.0};
    static const GpPointF dst_points[3] = {{0.0,0.0},{100.0,0.0},{0.0,100.0}};
    static const WCHAR description[] = {'w','i','n','e','t','e','s','t',0};
    GraphicsContainer state1, state2;
    GpRectF srcrect, dstrect;
    REAL dpix, dpiy;

    hdc = CreateCompatibleDC(0);

    stat = GdipRecordMetafile(hdc, EmfTypeEmfPlusOnly, &frame, MetafileFrameUnitPixel, description, &metafile);
    expect(Ok, stat);

    DeleteDC(hdc);

    if (stat != Ok)
        return;

    stat = GdipGetImageGraphicsContext((GpImage*)metafile, &graphics);
    expect(Ok, stat);

    /* Normal usage */
    stat = GdipBeginContainer2(graphics, &state1);
    expect(Ok, stat);

    stat = GdipScaleWorldTransform(graphics, 2.0, 2.0, MatrixOrderPrepend);
    expect(Ok, stat);

    stat = GdipCreateSolidFill((ARGB)0xff000000, (GpSolidFill**)&brush);
    expect(Ok, stat);

    stat = GdipFillRectangle(graphics, brush, 5.0, 5.0, 5.0, 5.0);
    expect(Ok, stat);

    stat = GdipDeleteBrush(brush);
    expect(Ok, stat);

    stat = GdipEndContainer(graphics, state1);
    expect(Ok, stat);

    stat = GdipScaleWorldTransform(graphics, 1.0, 1.0, MatrixOrderPrepend);
    expect(Ok, stat);

    stat = GdipCreateSolidFill((ARGB)0xff0000ff, (GpSolidFill**)&brush);
    expect(Ok, stat);

    stat = GdipFillRectangle(graphics, brush, 5.0, 5.0, 5.0, 5.0);
    expect(Ok, stat);

    stat = GdipDeleteBrush(brush);
    expect(Ok, stat);

    stat = GdipSaveGraphics(graphics, &state1);
    expect(Ok, stat);

    stat = GdipRestoreGraphics(graphics, state1);
    expect(Ok, stat);

    /* Popping two states at once */
    stat = GdipScaleWorldTransform(graphics, 2.0, 2.0, MatrixOrderPrepend);
    expect(Ok, stat);

    stat = GdipBeginContainer2(graphics, &state1);
    expect(Ok, stat);

    stat = GdipScaleWorldTransform(graphics, 4.0, 4.0, MatrixOrderPrepend);
    expect(Ok, stat);

    stat = GdipBeginContainer2(graphics, &state2);
    expect(Ok, stat);

    stat = GdipEndContainer(graphics, state1);
    expect(Ok, stat);

    stat = GdipCreateSolidFill((ARGB)0xff00ff00, (GpSolidFill**)&brush);
    expect(Ok, stat);

    stat = GdipFillRectangle(graphics, brush, 20.0, 20.0, 5.0, 5.0);
    expect(Ok, stat);

    stat = GdipDeleteBrush(brush);
    expect(Ok, stat);

    /* With transform applied */
    stat = GdipGetDpiX(graphics, &dpix);
    expect(Ok, stat);

    stat = GdipGetDpiY(graphics, &dpiy);
    expect(Ok, stat);

    srcrect.X = 0.0;
    srcrect.Y = 0.0;
    srcrect.Width = 1.0;
    srcrect.Height = 1.0;

    dstrect.X = 25.0;
    dstrect.Y = 0.0;
    dstrect.Width = 5.0;
    dstrect.Height = 5.0;

    stat = GdipBeginContainer(graphics, &dstrect, &srcrect, UnitInch, &state1);
    expect(Ok, stat);

    stat = GdipCreateSolidFill((ARGB)0xff00ffff, (GpSolidFill**)&brush);
    expect(Ok, stat);

    stat = GdipFillRectangle(graphics, brush, 0.0, 0.0, dpix, dpiy);
    expect(Ok, stat);

    stat = GdipDeleteBrush(brush);
    expect(Ok, stat);

    stat = GdipEndContainer(graphics, state1);
    expect(Ok, stat);

    /* Restoring an invalid state seems to break the graphics object? */
    if (0) {
        stat = GdipEndContainer(graphics, state1);
        expect(Ok, stat);
    }

    /* Ending metafile with a state open */
    stat = GdipBeginContainer2(graphics, &state1);
    expect(Ok, stat);

    stat = GdipDeleteGraphics(graphics);
    expect(Ok, stat);

    check_metafile(metafile, container_records, "container metafile", dst_points, &frame, UnitPixel);

    sync_metafile(&metafile, "container.emf");

    stat = GdipCreateBitmapFromScan0(100, 100, 0, PixelFormat32bppARGB, NULL, &bitmap);
    expect(Ok, stat);

    stat = GdipGetImageGraphicsContext((GpImage*)bitmap, &graphics);
    expect(Ok, stat);

    play_metafile(metafile, graphics, container_records, "container playback", dst_points, &frame, UnitPixel);

    stat = GdipBitmapGetPixel(bitmap, 80, 80, &color);
    expect(Ok, stat);
    expect(0, color);

    stat = GdipBitmapGetPixel(bitmap, 12, 12, &color);
    expect(Ok, stat);
    expect(0xff000000, color);

    stat = GdipBitmapGetPixel(bitmap, 8, 8, &color);
    expect(Ok, stat);
    expect(0xff0000ff, color);

    stat = GdipBitmapGetPixel(bitmap, 42, 42, &color);
    expect(Ok, stat);
    expect(0xff00ff00, color);

    stat = GdipBitmapGetPixel(bitmap, 55, 5, &color);
    expect(Ok, stat);
    expect(0xff00ffff, color);

    stat = GdipDeleteGraphics(graphics);
    expect(Ok, stat);

    stat = GdipDisposeImage((GpImage*)bitmap);
    expect(Ok, stat);

    stat = GdipDisposeImage((GpImage*)metafile);
    expect(Ok, stat);
}
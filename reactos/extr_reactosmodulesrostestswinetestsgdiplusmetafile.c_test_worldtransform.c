#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_9__   TYPE_2__ ;
typedef  struct TYPE_8__   TYPE_1__ ;

/* Type definitions */
typedef  char WCHAR ;
struct TYPE_9__ {double member_0; double member_1; } ;
struct TYPE_8__ {double member_0; double member_1; double member_2; double member_3; } ;
typedef  int /*<<< orphan*/  REAL ;
typedef  int /*<<< orphan*/  HDC ;
typedef  int GpStatus ;
typedef  int /*<<< orphan*/  GpSolidFill ;
typedef  TYPE_1__ GpRectF ;
typedef  TYPE_2__ GpPointF ;
typedef  int /*<<< orphan*/  GpMetafile ;
typedef  int /*<<< orphan*/  GpMatrix ;
typedef  int /*<<< orphan*/  GpImage ;
typedef  int /*<<< orphan*/  GpGraphics ;
typedef  int /*<<< orphan*/  GpBrush ;
typedef  int /*<<< orphan*/  GpBitmap ;
typedef  int BOOL ;
typedef  int ARGB ;

/* Variables and functions */
 int /*<<< orphan*/  CreateCompatibleDC (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  DeleteDC (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  EmfTypeEmfPlusOnly ; 
 int GdipBitmapGetPixel (int /*<<< orphan*/ *,int,int,int*) ; 
 int GdipCreateBitmapFromScan0 (int,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ **) ; 
 int GdipCreateMatrix (int /*<<< orphan*/ **) ; 
 int GdipCreateSolidFill (int,int /*<<< orphan*/ **) ; 
 int GdipDeleteBrush (int /*<<< orphan*/ *) ; 
 int GdipDeleteGraphics (int /*<<< orphan*/ *) ; 
 int GdipDeleteMatrix (int /*<<< orphan*/ *) ; 
 int GdipDisposeImage (int /*<<< orphan*/ *) ; 
 int GdipFillRectangle (int /*<<< orphan*/ *,int /*<<< orphan*/ *,double,double,double,double) ; 
 int GdipFillRectangleI (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,int) ; 
 int GdipGetImageGraphicsContext (int /*<<< orphan*/ *,int /*<<< orphan*/ **) ; 
 int GdipGetMatrixElements (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int GdipGetWorldTransform (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int GdipIsMatrixIdentity (int /*<<< orphan*/ *,int*) ; 
 int GdipMultiplyWorldTransform (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int GdipRecordMetafile (int /*<<< orphan*/ ,int /*<<< orphan*/ ,TYPE_1__ const*,int /*<<< orphan*/ ,char const*,int /*<<< orphan*/ **) ; 
 int GdipResetWorldTransform (int /*<<< orphan*/ *) ; 
 int GdipRotateWorldTransform (int /*<<< orphan*/ *,double,int /*<<< orphan*/ ) ; 
 int GdipScaleWorldTransform (int /*<<< orphan*/ *,double,double,int /*<<< orphan*/ ) ; 
 int GdipSetMatrixElements (int /*<<< orphan*/ *,double,double,double,double,double,double) ; 
 int GdipSetWorldTransform (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int GdipTranslateWorldTransform (int /*<<< orphan*/ *,double,double,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  MatrixOrderAppend ; 
 int /*<<< orphan*/  MatrixOrderPrepend ; 
 int /*<<< orphan*/  MetafileFrameUnitPixel ; 
 int Ok ; 
 int /*<<< orphan*/  PixelFormat32bppARGB ; 
 int TRUE ; 
 int /*<<< orphan*/  UnitPixel ; 
 int /*<<< orphan*/  check_metafile (int /*<<< orphan*/ *,int /*<<< orphan*/ ,char*,TYPE_2__ const*,TYPE_1__ const*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  expect (int,int) ; 
 int /*<<< orphan*/  expectf (double,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  play_metafile (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ ,char*,TYPE_2__ const*,TYPE_1__ const*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  sync_metafile (int /*<<< orphan*/ **,char*) ; 
 int /*<<< orphan*/  worldtransform_records ; 

__attribute__((used)) static void test_worldtransform(void)
{
    GpStatus stat;
    GpMetafile *metafile;
    GpGraphics *graphics;
    HDC hdc;
    static const GpRectF frame = {0.0, 0.0, 5.0, 5.0};
    static const GpPointF dst_points[3] = {{0.0,0.0},{100.0,0.0},{0.0,100.0}};
    static const WCHAR description[] = {'w','i','n','e','t','e','s','t',0};
    GpBitmap *bitmap;
    ARGB color;
    GpBrush *brush;
    GpMatrix *transform;
    BOOL identity;
    REAL elements[6];

    hdc = CreateCompatibleDC(0);

    stat = GdipRecordMetafile(hdc, EmfTypeEmfPlusOnly, &frame, MetafileFrameUnitPixel, description, &metafile);
    expect(Ok, stat);

    DeleteDC(hdc);

    if (stat != Ok)
        return;

    stat = GdipCreateMatrix(&transform);
    expect(Ok, stat);

    stat = GdipGetImageGraphicsContext((GpImage*)metafile, &graphics);
    expect(Ok, stat);

    /* initial transform */
    stat = GdipGetWorldTransform(graphics, transform);
    expect(Ok, stat);

    stat = GdipIsMatrixIdentity(transform, &identity);
    expect(Ok, stat);
    expect(TRUE, identity);

    stat = GdipCreateSolidFill((ARGB)0xff0000ff, (GpSolidFill**)&brush);
    expect(Ok, stat);

    stat = GdipFillRectangleI(graphics, brush, 0, 0, 1, 1);
    expect(Ok, stat);

    stat = GdipDeleteBrush(brush);
    expect(Ok, stat);

    /* scale transform */
    stat = GdipScaleWorldTransform(graphics, 2.0, 4.0, MatrixOrderPrepend);
    expect(Ok, stat);

    stat = GdipGetWorldTransform(graphics, transform);
    expect(Ok, stat);

    stat = GdipGetMatrixElements(transform, elements);
    expect(Ok, stat);
    expectf(2.0, elements[0]);
    expectf(0.0, elements[1]);
    expectf(0.0, elements[2]);
    expectf(4.0, elements[3]);
    expectf(0.0, elements[4]);
    expectf(0.0, elements[5]);

    stat = GdipCreateSolidFill((ARGB)0xff00ff00, (GpSolidFill**)&brush);
    expect(Ok, stat);

    stat = GdipFillRectangle(graphics, brush, 0.5, 0.5, 0.5, 0.25);
    expect(Ok, stat);

    stat = GdipDeleteBrush(brush);
    expect(Ok, stat);

    /* reset transform */
    stat = GdipResetWorldTransform(graphics);
    expect(Ok, stat);

    stat = GdipGetWorldTransform(graphics, transform);
    expect(Ok, stat);

    stat = GdipIsMatrixIdentity(transform, &identity);
    expect(Ok, stat);
    expect(TRUE, identity);

    stat = GdipCreateSolidFill((ARGB)0xff00ffff, (GpSolidFill**)&brush);
    expect(Ok, stat);

    stat = GdipFillRectangle(graphics, brush, 1.0, 0.0, 1.0, 1.0);
    expect(Ok, stat);

    stat = GdipDeleteBrush(brush);
    expect(Ok, stat);

    /* multiply transform */
    stat = GdipSetMatrixElements(transform, 2.0, 0.0, 0.0, 1.0, 0.0, 0.0);
    expect(Ok, stat);

    stat = GdipMultiplyWorldTransform(graphics, transform, MatrixOrderPrepend);
    expect(Ok, stat);

    stat = GdipGetWorldTransform(graphics, transform);
    expect(Ok, stat);

    stat = GdipGetMatrixElements(transform, elements);
    expect(Ok, stat);
    expectf(2.0, elements[0]);
    expectf(0.0, elements[1]);
    expectf(0.0, elements[2]);
    expectf(1.0, elements[3]);
    expectf(0.0, elements[4]);
    expectf(0.0, elements[5]);

    stat = GdipCreateSolidFill((ARGB)0xffff0000, (GpSolidFill**)&brush);
    expect(Ok, stat);

    stat = GdipFillRectangle(graphics, brush, 1.0, 1.0, 0.5, 1.0);
    expect(Ok, stat);

    stat = GdipDeleteBrush(brush);
    expect(Ok, stat);

    /* rotate transform */
    stat = GdipRotateWorldTransform(graphics, 90.0, MatrixOrderAppend);
    expect(Ok, stat);

    stat = GdipGetWorldTransform(graphics, transform);
    expect(Ok, stat);

    stat = GdipGetMatrixElements(transform, elements);
    expect(Ok, stat);
    expectf(0.0, elements[0]);
    expectf(2.0, elements[1]);
    expectf(-1.0, elements[2]);
    expectf(0.0, elements[3]);
    expectf(0.0, elements[4]);
    expectf(0.0, elements[5]);

    stat = GdipCreateSolidFill((ARGB)0xffff00ff, (GpSolidFill**)&brush);
    expect(Ok, stat);

    stat = GdipFillRectangle(graphics, brush, 1.0, -1.0, 0.5, 1.0);
    expect(Ok, stat);

    stat = GdipDeleteBrush(brush);
    expect(Ok, stat);

    /* set transform */
    stat = GdipSetMatrixElements(transform, 1.0, 0.0, 0.0, 3.0, 0.0, 0.0);
    expect(Ok, stat);

    stat = GdipSetWorldTransform(graphics, transform);
    expect(Ok, stat);

    stat = GdipGetWorldTransform(graphics, transform);
    expect(Ok, stat);

    stat = GdipGetMatrixElements(transform, elements);
    expect(Ok, stat);
    expectf(1.0, elements[0]);
    expectf(0.0, elements[1]);
    expectf(0.0, elements[2]);
    expectf(3.0, elements[3]);
    expectf(0.0, elements[4]);
    expectf(0.0, elements[5]);

    stat = GdipCreateSolidFill((ARGB)0xffffff00, (GpSolidFill**)&brush);
    expect(Ok, stat);

    stat = GdipFillRectangle(graphics, brush, 1.0, 1.0, 1.0, 1.0);
    expect(Ok, stat);

    stat = GdipDeleteBrush(brush);
    expect(Ok, stat);

    /* translate transform */
    stat = GdipTranslateWorldTransform(graphics, -1.0, 0.0, MatrixOrderAppend);
    expect(Ok, stat);

    stat = GdipGetWorldTransform(graphics, transform);
    expect(Ok, stat);

    stat = GdipGetMatrixElements(transform, elements);
    expect(Ok, stat);
    expectf(1.0, elements[0]);
    expectf(0.0, elements[1]);
    expectf(0.0, elements[2]);
    expectf(3.0, elements[3]);
    expectf(-1.0, elements[4]);
    expectf(0.0, elements[5]);

    stat = GdipCreateSolidFill((ARGB)0xffffffff, (GpSolidFill**)&brush);
    expect(Ok, stat);

    stat = GdipFillRectangle(graphics, brush, 1.0, 1.0, 1.0, 1.0);
    expect(Ok, stat);

    stat = GdipDeleteBrush(brush);
    expect(Ok, stat);

    stat = GdipDeleteMatrix(transform);
    expect(Ok, stat);

    stat = GdipDeleteGraphics(graphics);
    expect(Ok, stat);

    check_metafile(metafile, worldtransform_records, "worldtransform metafile", dst_points, &frame, UnitPixel);

    sync_metafile(&metafile, "worldtransform.emf");

    stat = GdipCreateBitmapFromScan0(100, 100, 0, PixelFormat32bppARGB, NULL, &bitmap);
    expect(Ok, stat);

    stat = GdipGetImageGraphicsContext((GpImage*)bitmap, &graphics);
    expect(Ok, stat);

    play_metafile(metafile, graphics, worldtransform_records, "worldtransform playback", dst_points, &frame, UnitPixel);

    stat = GdipBitmapGetPixel(bitmap, 80, 80, &color);
    expect(Ok, stat);
    expect(0, color);

    stat = GdipBitmapGetPixel(bitmap, 10, 10, &color);
    expect(Ok, stat);
    expect(0xff0000ff, color);

    stat = GdipBitmapGetPixel(bitmap, 30, 50, &color);
    expect(Ok, stat);
    expect(0xff00ff00, color);

    stat = GdipBitmapGetPixel(bitmap, 30, 10, &color);
    expect(Ok, stat);
    expect(0xff00ffff, color);

    stat = GdipBitmapGetPixel(bitmap, 50, 30, &color);
    expect(Ok, stat);
    expect(0xffff0000, color);

    stat = GdipBitmapGetPixel(bitmap, 10, 50, &color);
    expect(Ok, stat);
    expect(0xffff00ff, color);

    stat = GdipBitmapGetPixel(bitmap, 30, 90, &color);
    expect(Ok, stat);
    expect(0xffffff00, color);

    stat = GdipBitmapGetPixel(bitmap, 10, 90, &color);
    expect(Ok, stat);
    expect(0xffffffff, color);

    stat = GdipDeleteGraphics(graphics);
    expect(Ok, stat);

    stat = GdipDisposeImage((GpImage*)bitmap);
    expect(Ok, stat);

    stat = GdipDisposeImage((GpImage*)metafile);
    expect(Ok, stat);
}
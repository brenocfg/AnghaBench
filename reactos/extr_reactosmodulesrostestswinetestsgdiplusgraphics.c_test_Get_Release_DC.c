#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_37__   TYPE_4__ ;
typedef  struct TYPE_36__   TYPE_3__ ;
typedef  struct TYPE_35__   TYPE_2__ ;
typedef  struct TYPE_34__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  TextRenderingHint ;
struct TYPE_37__ {int X; int Y; } ;
struct TYPE_36__ {void* Y; void* X; } ;
struct TYPE_35__ {int Width; int Height; scalar_t__ Y; scalar_t__ X; } ;
struct TYPE_34__ {void* Width; void* Height; void* Y; void* X; } ;
typedef  int /*<<< orphan*/  SmoothingMode ;
typedef  void* REAL ;
typedef  int /*<<< orphan*/  PixelOffsetMode ;
typedef  int /*<<< orphan*/  InterpolationMode ;
typedef  int INT ;
typedef  int /*<<< orphan*/  HRGN ;
typedef  int /*<<< orphan*/ * HDC ;
typedef  int /*<<< orphan*/  GpUnit ;
typedef  int /*<<< orphan*/  GpStatus ;
typedef  int /*<<< orphan*/  GpSolidFill ;
typedef  int /*<<< orphan*/  GpRegion ;
typedef  TYPE_1__ GpRectF ;
typedef  TYPE_2__ GpRect ;
typedef  TYPE_3__ GpPointF ;
typedef  TYPE_4__ GpPoint ;
typedef  int /*<<< orphan*/  GpPen ;
typedef  int /*<<< orphan*/  GpPath ;
typedef  int /*<<< orphan*/  GpMatrix ;
typedef  int /*<<< orphan*/  GpGraphics ;
typedef  int /*<<< orphan*/  GpBrush ;
typedef  int /*<<< orphan*/  CompositingQuality ;
typedef  int /*<<< orphan*/  CompositingMode ;
typedef  int /*<<< orphan*/  BOOL ;
typedef  int ARGB ;

/* Variables and functions */
 int /*<<< orphan*/  CombineModeReplace ; 
 int /*<<< orphan*/  CompositingModeSourceOver ; 
 int /*<<< orphan*/  CompositingQualityDefault ; 
 int /*<<< orphan*/  CoordinateSpacePage ; 
 int /*<<< orphan*/  CoordinateSpaceWorld ; 
 int /*<<< orphan*/  CreateRectRgn (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,int) ; 
 int /*<<< orphan*/  DeleteObject (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  FillModeAlternate ; 
 int /*<<< orphan*/  FlushIntentionFlush ; 
 int /*<<< orphan*/  GdipCreateFromHDC (int /*<<< orphan*/ *,int /*<<< orphan*/ **) ; 
 int /*<<< orphan*/  GdipCreateMatrix (int /*<<< orphan*/ **) ; 
 int /*<<< orphan*/  GdipCreatePath (int /*<<< orphan*/ ,int /*<<< orphan*/ **) ; 
 int /*<<< orphan*/  GdipCreatePen1 (int,float,int /*<<< orphan*/ ,int /*<<< orphan*/ **) ; 
 int /*<<< orphan*/  GdipCreateRegion (int /*<<< orphan*/ **) ; 
 int /*<<< orphan*/  GdipCreateSolidFill (int,int /*<<< orphan*/ **) ; 
 int /*<<< orphan*/  GdipDeleteBrush (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  GdipDeleteGraphics (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  GdipDeleteMatrix (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  GdipDeletePath (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  GdipDeletePen (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  GdipDeleteRegion (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  GdipDrawArc (int /*<<< orphan*/ *,int /*<<< orphan*/ *,double,double,double,double,double,double) ; 
 int /*<<< orphan*/  GdipDrawArcI (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,int,double,double) ; 
 int /*<<< orphan*/  GdipDrawBezier (int /*<<< orphan*/ *,int /*<<< orphan*/ *,double,double,double,double,double,double,double,double) ; 
 int /*<<< orphan*/  GdipDrawBezierI (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  GdipDrawBeziers (int /*<<< orphan*/ *,int /*<<< orphan*/ *,TYPE_3__*,int) ; 
 int /*<<< orphan*/  GdipDrawBeziersI (int /*<<< orphan*/ *,int /*<<< orphan*/ *,TYPE_4__*,int) ; 
 int /*<<< orphan*/  GdipDrawClosedCurve (int /*<<< orphan*/ *,int /*<<< orphan*/ *,TYPE_3__*,int) ; 
 int /*<<< orphan*/  GdipDrawClosedCurve2 (int /*<<< orphan*/ *,int /*<<< orphan*/ *,TYPE_3__*,int,double) ; 
 int /*<<< orphan*/  GdipDrawClosedCurve2I (int /*<<< orphan*/ *,int /*<<< orphan*/ *,TYPE_4__*,int,double) ; 
 int /*<<< orphan*/  GdipDrawClosedCurveI (int /*<<< orphan*/ *,int /*<<< orphan*/ *,TYPE_4__*,int) ; 
 int /*<<< orphan*/  GdipDrawCurve (int /*<<< orphan*/ *,int /*<<< orphan*/ *,TYPE_3__*,int) ; 
 int /*<<< orphan*/  GdipDrawCurve2 (int /*<<< orphan*/ *,int /*<<< orphan*/ *,TYPE_3__*,int,double) ; 
 int /*<<< orphan*/  GdipDrawCurve2I (int /*<<< orphan*/ *,int /*<<< orphan*/ *,TYPE_4__*,int,double) ; 
 int /*<<< orphan*/  GdipDrawCurveI (int /*<<< orphan*/ *,int /*<<< orphan*/ *,TYPE_4__*,int) ; 
 int /*<<< orphan*/  GdipDrawEllipse (int /*<<< orphan*/ *,int /*<<< orphan*/ *,double,double,double,double) ; 
 int /*<<< orphan*/  GdipDrawEllipseI (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,int) ; 
 int /*<<< orphan*/  GdipDrawLine (int /*<<< orphan*/ *,int /*<<< orphan*/ *,double,double,double,double) ; 
 int /*<<< orphan*/  GdipDrawLineI (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,int) ; 
 int /*<<< orphan*/  GdipDrawLines (int /*<<< orphan*/ *,int /*<<< orphan*/ *,TYPE_3__*,int) ; 
 int /*<<< orphan*/  GdipDrawLinesI (int /*<<< orphan*/ *,int /*<<< orphan*/ *,TYPE_4__*,int) ; 
 int /*<<< orphan*/  GdipDrawPath (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  GdipDrawPie (int /*<<< orphan*/ *,int /*<<< orphan*/ *,double,double,double,double,double,double) ; 
 int /*<<< orphan*/  GdipDrawPieI (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,int,double,double) ; 
 int /*<<< orphan*/  GdipDrawPolygon (int /*<<< orphan*/ *,int /*<<< orphan*/ *,TYPE_3__*,int) ; 
 int /*<<< orphan*/  GdipDrawPolygonI (int /*<<< orphan*/ *,int /*<<< orphan*/ *,TYPE_4__*,int) ; 
 int /*<<< orphan*/  GdipDrawRectangle (int /*<<< orphan*/ *,int /*<<< orphan*/ *,double,double,double,double) ; 
 int /*<<< orphan*/  GdipDrawRectangleI (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,int) ; 
 int /*<<< orphan*/  GdipDrawRectangles (int /*<<< orphan*/ *,int /*<<< orphan*/ *,TYPE_1__*,int) ; 
 int /*<<< orphan*/  GdipDrawRectanglesI (int /*<<< orphan*/ *,int /*<<< orphan*/ *,TYPE_2__*,int) ; 
 int /*<<< orphan*/  GdipFillClosedCurve (int /*<<< orphan*/ *,int /*<<< orphan*/ *,TYPE_3__*,int) ; 
 int /*<<< orphan*/  GdipFillClosedCurve2 (int /*<<< orphan*/ *,int /*<<< orphan*/ *,TYPE_3__*,int,double,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  GdipFillClosedCurve2I (int /*<<< orphan*/ *,int /*<<< orphan*/ *,TYPE_4__*,int,double,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  GdipFillClosedCurveI (int /*<<< orphan*/ *,int /*<<< orphan*/ *,TYPE_4__*,int) ; 
 int /*<<< orphan*/  GdipFillEllipse (int /*<<< orphan*/ *,int /*<<< orphan*/ *,double,double,double,double) ; 
 int /*<<< orphan*/  GdipFillEllipseI (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,int) ; 
 int /*<<< orphan*/  GdipFillPath (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  GdipFillPie (int /*<<< orphan*/ *,int /*<<< orphan*/ *,double,double,double,double,double,double) ; 
 int /*<<< orphan*/  GdipFillPieI (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,int,double,double) ; 
 int /*<<< orphan*/  GdipFillPolygon (int /*<<< orphan*/ *,int /*<<< orphan*/ *,TYPE_3__*,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  GdipFillPolygon2 (int /*<<< orphan*/ *,int /*<<< orphan*/ *,TYPE_3__*,int) ; 
 int /*<<< orphan*/  GdipFillPolygon2I (int /*<<< orphan*/ *,int /*<<< orphan*/ *,TYPE_4__*,int) ; 
 int /*<<< orphan*/  GdipFillPolygonI (int /*<<< orphan*/ *,int /*<<< orphan*/ *,TYPE_4__*,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  GdipFillRectangle (int /*<<< orphan*/ *,int /*<<< orphan*/ *,double,double,double,double) ; 
 int /*<<< orphan*/  GdipFillRectangleI (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,int) ; 
 int /*<<< orphan*/  GdipFillRectangles (int /*<<< orphan*/ *,int /*<<< orphan*/ *,TYPE_1__*,int) ; 
 int /*<<< orphan*/  GdipFillRectanglesI (int /*<<< orphan*/ *,int /*<<< orphan*/ *,TYPE_2__*,int) ; 
 int /*<<< orphan*/  GdipFillRegion (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  GdipFlush (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  GdipGetClip (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  GdipGetClipBounds (int /*<<< orphan*/ *,TYPE_1__*) ; 
 int /*<<< orphan*/  GdipGetClipBoundsI (int /*<<< orphan*/ *,TYPE_2__*) ; 
 int /*<<< orphan*/  GdipGetCompositingMode (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  GdipGetCompositingQuality (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  GdipGetDC (int /*<<< orphan*/ *,int /*<<< orphan*/ **) ; 
 int /*<<< orphan*/  GdipGetDpiX (int /*<<< orphan*/ *,void**) ; 
 int /*<<< orphan*/  GdipGetDpiY (int /*<<< orphan*/ *,void**) ; 
 int /*<<< orphan*/  GdipGetInterpolationMode (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  GdipGetNearestColor (int /*<<< orphan*/ *,int*) ; 
 int /*<<< orphan*/  GdipGetPageScale (int /*<<< orphan*/ *,void**) ; 
 int /*<<< orphan*/  GdipGetPageUnit (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  GdipGetPixelOffsetMode (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  GdipGetSmoothingMode (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  GdipGetTextRenderingHint (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  GdipGetWorldTransform (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  GdipGraphicsClear (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  GdipIsVisiblePoint (int /*<<< orphan*/ *,double,double,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  GdipIsVisiblePointI (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  GdipMultiplyWorldTransform (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  GdipReleaseDC (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  GdipResetClip (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  GdipResetWorldTransform (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  GdipRotateWorldTransform (int /*<<< orphan*/ *,double,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  GdipScaleWorldTransform (int /*<<< orphan*/ *,double,double,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  GdipSetClipHrgn (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  GdipSetClipPath (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  GdipSetClipRect (int /*<<< orphan*/ *,double,double,double,double,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  GdipSetClipRectI (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  GdipSetClipRegion (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  GdipSetCompositingMode (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  GdipSetCompositingQuality (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  GdipSetInterpolationMode (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  GdipSetPageScale (int /*<<< orphan*/ *,double) ; 
 int /*<<< orphan*/  GdipSetPageUnit (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  GdipSetPixelOffsetMode (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  GdipSetSmoothingMode (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  GdipSetTextRenderingHint (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  GdipSetWorldTransform (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  GdipTransformPoints (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,TYPE_3__*,int) ; 
 int /*<<< orphan*/  GdipTranslateClip (int /*<<< orphan*/ *,double,double) ; 
 int /*<<< orphan*/  GdipTranslateClipI (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  GdipTranslateWorldTransform (int /*<<< orphan*/ *,double,double,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * GetDC (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  InterpolationModeDefault ; 
 int /*<<< orphan*/  InvalidParameter ; 
 int /*<<< orphan*/  MatrixOrderPrepend ; 
 int /*<<< orphan*/  ObjectBusy ; 
 int /*<<< orphan*/  Ok ; 
 int /*<<< orphan*/  PixelOffsetModeDefault ; 
 int /*<<< orphan*/  ReleaseDC (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  SmoothingModeDefault ; 
 int /*<<< orphan*/  TextRenderingHintSystemDefault ; 
 int /*<<< orphan*/  UnitPixel ; 
 int /*<<< orphan*/  UnitWorld ; 
 int /*<<< orphan*/  expect (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  hwnd ; 
 int /*<<< orphan*/  ok (int,char*) ; 

__attribute__((used)) static void test_Get_Release_DC(void)
{
    GpStatus status;
    GpGraphics *graphics = NULL;
    GpPen *pen;
    GpSolidFill *brush;
    GpPath *path;
    HDC hdc = GetDC( hwnd );
    HDC retdc;
    REAL r;
    CompositingQuality quality;
    CompositingMode compmode;
    InterpolationMode intmode;
    GpMatrix *m;
    GpRegion *region;
    GpUnit unit;
    PixelOffsetMode offsetmode;
    SmoothingMode smoothmode;
    TextRenderingHint texthint;
    GpPointF ptf[5];
    GpPoint  pt[5];
    GpRectF  rectf[2];
    GpRect   rect[2];
    GpRegion *clip;
    INT i;
    BOOL res;
    ARGB color = 0x00000000;
    HRGN hrgn = CreateRectRgn(0, 0, 10, 10);

    pt[0].X = 10;
    pt[0].Y = 10;
    pt[1].X = 20;
    pt[1].Y = 15;
    pt[2].X = 40;
    pt[2].Y = 80;
    pt[3].X = -20;
    pt[3].Y = 20;
    pt[4].X = 50;
    pt[4].Y = 110;

    for(i = 0; i < 5;i++){
        ptf[i].X = (REAL)pt[i].X;
        ptf[i].Y = (REAL)pt[i].Y;
    }

    rect[0].X = 0;
    rect[0].Y = 0;
    rect[0].Width  = 50;
    rect[0].Height = 70;
    rect[1].X = 0;
    rect[1].Y = 0;
    rect[1].Width  = 10;
    rect[1].Height = 20;

    for(i = 0; i < 2;i++){
        rectf[i].X = (REAL)rect[i].X;
        rectf[i].Y = (REAL)rect[i].Y;
        rectf[i].Height = (REAL)rect[i].Height;
        rectf[i].Width  = (REAL)rect[i].Width;
    }

    status = GdipCreateMatrix(&m);
    expect(Ok, status);
    status = GdipCreateRegion(&region);
    expect(Ok, status);
    GdipCreateSolidFill((ARGB)0xdeadbeef, &brush);
    GdipCreatePath(FillModeAlternate, &path);
    status = GdipCreateRegion(&clip);
    expect(Ok, status);

    status = GdipCreateFromHDC(hdc, &graphics);
    expect(Ok, status);
    ok(graphics != NULL, "Expected graphics to be initialized\n");
    status = GdipCreatePen1((ARGB)0xffff00ff, 10.0f, UnitPixel, &pen);
    expect(Ok, status);

    /* NULL arguments */
    status = GdipGetDC(NULL, NULL);
    expect(InvalidParameter, status);
    status = GdipGetDC(graphics, NULL);
    expect(InvalidParameter, status);
    status = GdipGetDC(NULL, &retdc);
    expect(InvalidParameter, status);

    status = GdipReleaseDC(NULL, NULL);
    expect(InvalidParameter, status);
    status = GdipReleaseDC(graphics, NULL);
    expect(InvalidParameter, status);
    status = GdipReleaseDC(NULL, (HDC)0xdeadbeef);
    expect(InvalidParameter, status);

    /* Release without Get */
    status = GdipReleaseDC(graphics, hdc);
    expect(InvalidParameter, status);

    retdc = NULL;
    status = GdipGetDC(graphics, &retdc);
    expect(Ok, status);
    ok(retdc == hdc, "Invalid HDC returned\n");
    /* call it once more */
    status = GdipGetDC(graphics, &retdc);
    expect(ObjectBusy, status);

    /* try all Graphics calls here */
    status = GdipDrawArc(graphics, pen, 0.0, 0.0, 1.0, 1.0, 0.0, 0.0);
    expect(ObjectBusy, status);
    status = GdipDrawArcI(graphics, pen, 0, 0, 1, 1, 0.0, 0.0);
    expect(ObjectBusy, status);
    status = GdipDrawBezier(graphics, pen, 0.0, 10.0, 20.0, 15.0, 35.0, -10.0, 10.0, 10.0);
    expect(ObjectBusy, status);
    status = GdipDrawBezierI(graphics, pen, 0, 0, 0, 0, 0, 0, 0, 0);
    expect(ObjectBusy, status);
    status = GdipDrawBeziers(graphics, pen, ptf, 5);
    expect(ObjectBusy, status);
    status = GdipDrawBeziersI(graphics, pen, pt, 5);
    expect(ObjectBusy, status);
    status = GdipDrawClosedCurve(graphics, pen, ptf, 5);
    expect(ObjectBusy, status);
    status = GdipDrawClosedCurveI(graphics, pen, pt, 5);
    expect(ObjectBusy, status);
    status = GdipDrawClosedCurve2(graphics, pen, ptf, 5, 1.0);
    expect(ObjectBusy, status);
    status = GdipDrawClosedCurve2I(graphics, pen, pt, 5, 1.0);
    expect(ObjectBusy, status);
    status = GdipDrawCurve(graphics, pen, ptf, 5);
    expect(ObjectBusy, status);
    status = GdipDrawCurveI(graphics, pen, pt, 5);
    expect(ObjectBusy, status);
    status = GdipDrawCurve2(graphics, pen, ptf, 5, 1.0);
    expect(ObjectBusy, status);
    status = GdipDrawCurve2I(graphics, pen, pt, 5, 1.0);
    expect(ObjectBusy, status);
    status = GdipDrawEllipse(graphics, pen, 0.0, 0.0, 100.0, 50.0);
    expect(ObjectBusy, status);
    status = GdipDrawEllipseI(graphics, pen, 0, 0, 100, 50);
    expect(ObjectBusy, status);
    /* GdipDrawImage/GdipDrawImageI */
    /* GdipDrawImagePointsRect/GdipDrawImagePointsRectI */
    /* GdipDrawImageRectRect/GdipDrawImageRectRectI */
    /* GdipDrawImageRect/GdipDrawImageRectI */
    status = GdipDrawLine(graphics, pen, 0.0, 0.0, 100.0, 200.0);
    expect(ObjectBusy, status);
    status = GdipDrawLineI(graphics, pen, 0, 0, 100, 200);
    expect(ObjectBusy, status);
    status = GdipDrawLines(graphics, pen, ptf, 5);
    expect(ObjectBusy, status);
    status = GdipDrawLinesI(graphics, pen, pt, 5);
    expect(ObjectBusy, status);
    status = GdipDrawPath(graphics, pen, path);
    expect(ObjectBusy, status);
    status = GdipDrawPie(graphics, pen, 0.0, 0.0, 100.0, 100.0, 0.0, 90.0);
    expect(ObjectBusy, status);
    status = GdipDrawPieI(graphics, pen, 0, 0, 100, 100, 0.0, 90.0);
    expect(ObjectBusy, status);
    status = GdipDrawRectangle(graphics, pen, 0.0, 0.0, 100.0, 300.0);
    expect(ObjectBusy, status);
    status = GdipDrawRectangleI(graphics, pen, 0, 0, 100, 300);
    expect(ObjectBusy, status);
    status = GdipDrawRectangles(graphics, pen, rectf, 2);
    expect(ObjectBusy, status);
    status = GdipDrawRectanglesI(graphics, pen, rect, 2);
    expect(ObjectBusy, status);
    /* GdipDrawString */
    status = GdipFillClosedCurve2(graphics, (GpBrush*)brush, ptf, 5, 1.0, FillModeAlternate);
    expect(ObjectBusy, status);
    status = GdipFillClosedCurve2I(graphics, (GpBrush*)brush, pt, 5, 1.0, FillModeAlternate);
    expect(ObjectBusy, status);
    status = GdipFillClosedCurve(graphics, (GpBrush*)brush, ptf, 5);
    expect(ObjectBusy, status);
    status = GdipFillClosedCurveI(graphics, (GpBrush*)brush, pt, 5);
    expect(ObjectBusy, status);
    status = GdipFillEllipse(graphics, (GpBrush*)brush, 0.0, 0.0, 100.0, 100.0);
    expect(ObjectBusy, status);
    status = GdipFillEllipseI(graphics, (GpBrush*)brush, 0, 0, 100, 100);
    expect(ObjectBusy, status);
    status = GdipFillPath(graphics, (GpBrush*)brush, path);
    expect(ObjectBusy, status);
    status = GdipFillPie(graphics, (GpBrush*)brush, 0.0, 0.0, 100.0, 100.0, 0.0, 15.0);
    expect(ObjectBusy, status);
    status = GdipFillPieI(graphics, (GpBrush*)brush, 0, 0, 100, 100, 0.0, 15.0);
    expect(ObjectBusy, status);
    status = GdipFillPolygon(graphics, (GpBrush*)brush, ptf, 5, FillModeAlternate);
    expect(ObjectBusy, status);
    status = GdipFillPolygonI(graphics, (GpBrush*)brush, pt, 5, FillModeAlternate);
    expect(ObjectBusy, status);
    status = GdipFillPolygon2(graphics, (GpBrush*)brush, ptf, 5);
    expect(ObjectBusy, status);
    status = GdipFillPolygon2I(graphics, (GpBrush*)brush, pt, 5);
    expect(ObjectBusy, status);
    status = GdipFillRectangle(graphics, (GpBrush*)brush, 0.0, 0.0, 100.0, 100.0);
    expect(ObjectBusy, status);
    status = GdipFillRectangleI(graphics, (GpBrush*)brush, 0, 0, 100, 100);
    expect(ObjectBusy, status);
    status = GdipFillRectangles(graphics, (GpBrush*)brush, rectf, 2);
    expect(ObjectBusy, status);
    status = GdipFillRectanglesI(graphics, (GpBrush*)brush, rect, 2);
    expect(ObjectBusy, status);
    status = GdipFillRegion(graphics, (GpBrush*)brush, region);
    expect(ObjectBusy, status);
    status = GdipFlush(graphics, FlushIntentionFlush);
    expect(ObjectBusy, status);
    status = GdipGetClipBounds(graphics, rectf);
    expect(ObjectBusy, status);
    status = GdipGetClipBoundsI(graphics, rect);
    expect(ObjectBusy, status);
    status = GdipGetCompositingMode(graphics, &compmode);
    expect(ObjectBusy, status);
    status = GdipGetCompositingQuality(graphics, &quality);
    expect(ObjectBusy, status);
    status = GdipGetInterpolationMode(graphics, &intmode);
    expect(ObjectBusy, status);
    status = GdipGetNearestColor(graphics, &color);
    expect(ObjectBusy, status);
    status = GdipGetPageScale(graphics, &r);
    expect(ObjectBusy, status);
    status = GdipGetPageUnit(graphics, &unit);
    expect(ObjectBusy, status);
    status = GdipGetPixelOffsetMode(graphics, &offsetmode);
    expect(ObjectBusy, status);
    status = GdipGetSmoothingMode(graphics, &smoothmode);
    expect(ObjectBusy, status);
    status = GdipGetTextRenderingHint(graphics, &texthint);
    expect(ObjectBusy, status);
    status = GdipGetWorldTransform(graphics, m);
    expect(ObjectBusy, status);
    status = GdipGraphicsClear(graphics, 0xdeadbeef);
    expect(ObjectBusy, status);
    status = GdipIsVisiblePoint(graphics, 0.0, 0.0, &res);
    expect(ObjectBusy, status);
    status = GdipIsVisiblePointI(graphics, 0, 0, &res);
    expect(ObjectBusy, status);
    /* GdipMeasureCharacterRanges */
    /* GdipMeasureString */
    status = GdipResetClip(graphics);
    expect(ObjectBusy, status);
    status = GdipResetWorldTransform(graphics);
    expect(ObjectBusy, status);
    /* GdipRestoreGraphics */
    status = GdipRotateWorldTransform(graphics, 15.0, MatrixOrderPrepend);
    expect(ObjectBusy, status);
    /*  GdipSaveGraphics */
    status = GdipScaleWorldTransform(graphics, 1.0, 1.0, MatrixOrderPrepend);
    expect(ObjectBusy, status);
    status = GdipSetCompositingMode(graphics, CompositingModeSourceOver);
    expect(ObjectBusy, status);
    status = GdipSetCompositingQuality(graphics, CompositingQualityDefault);
    expect(ObjectBusy, status);
    status = GdipSetInterpolationMode(graphics, InterpolationModeDefault);
    expect(ObjectBusy, status);
    status = GdipSetPageScale(graphics, 1.0);
    expect(ObjectBusy, status);
    status = GdipSetPageUnit(graphics, UnitWorld);
    expect(ObjectBusy, status);
    status = GdipSetPixelOffsetMode(graphics, PixelOffsetModeDefault);
    expect(ObjectBusy, status);
    status = GdipSetSmoothingMode(graphics, SmoothingModeDefault);
    expect(ObjectBusy, status);
    status = GdipSetTextRenderingHint(graphics, TextRenderingHintSystemDefault);
    expect(ObjectBusy, status);
    status = GdipSetWorldTransform(graphics, m);
    expect(ObjectBusy, status);
    status = GdipTranslateWorldTransform(graphics, 0.0, 0.0, MatrixOrderPrepend);
    expect(ObjectBusy, status);
    status = GdipSetClipHrgn(graphics, hrgn, CombineModeReplace);
    expect(ObjectBusy, status);
    status = GdipSetClipPath(graphics, path, CombineModeReplace);
    expect(ObjectBusy, status);
    status = GdipSetClipRect(graphics, 0.0, 0.0, 10.0, 10.0, CombineModeReplace);
    expect(ObjectBusy, status);
    status = GdipSetClipRectI(graphics, 0, 0, 10, 10, CombineModeReplace);
    expect(ObjectBusy, status);
    status = GdipSetClipRegion(graphics, clip, CombineModeReplace);
    expect(ObjectBusy, status);
    status = GdipTranslateClip(graphics, 0.0, 0.0);
    expect(ObjectBusy, status);
    status = GdipTranslateClipI(graphics, 0, 0);
    expect(ObjectBusy, status);
    status = GdipDrawPolygon(graphics, pen, ptf, 5);
    expect(ObjectBusy, status);
    status = GdipDrawPolygonI(graphics, pen, pt, 5);
    expect(ObjectBusy, status);
    status = GdipGetDpiX(graphics, &r);
    expect(ObjectBusy, status);
    status = GdipGetDpiY(graphics, &r);
    expect(ObjectBusy, status);
    status = GdipMultiplyWorldTransform(graphics, m, MatrixOrderPrepend);
    expect(ObjectBusy, status);
    status = GdipGetClip(graphics, region);
    expect(ObjectBusy, status);
    status = GdipTransformPoints(graphics, CoordinateSpacePage, CoordinateSpaceWorld, ptf, 5);
    expect(ObjectBusy, status);

    /* try to delete before release */
    status = GdipDeleteGraphics(graphics);
    expect(ObjectBusy, status);

    status = GdipReleaseDC(graphics, retdc);
    expect(Ok, status);

    GdipDeletePen(pen);
    GdipDeleteGraphics(graphics);

    GdipDeleteRegion(clip);
    GdipDeletePath(path);
    GdipDeleteBrush((GpBrush*)brush);
    GdipDeleteRegion(region);
    GdipDeleteMatrix(m);
    DeleteObject(hrgn);

    ReleaseDC(hwnd, hdc);
}
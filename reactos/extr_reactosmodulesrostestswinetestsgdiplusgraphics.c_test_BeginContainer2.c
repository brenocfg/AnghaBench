#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
typedef  scalar_t__ UINT ;
typedef  scalar_t__ TextRenderingHint ;
struct TYPE_3__ {int X; int Y; int Width; int Height; } ;
typedef  scalar_t__ SmoothingMode ;
typedef  int REAL ;
typedef  scalar_t__ PixelOffsetMode ;
typedef  scalar_t__ InterpolationMode ;
typedef  int /*<<< orphan*/ * HDC ;
typedef  int /*<<< orphan*/  GraphicsContainer ;
typedef  scalar_t__ GpUnit ;
typedef  int /*<<< orphan*/  GpStatus ;
typedef  TYPE_1__ GpRectF ;
typedef  int /*<<< orphan*/  GpMatrix ;
typedef  int /*<<< orphan*/  GpGraphics ;
typedef  scalar_t__ CompositingQuality ;
typedef  scalar_t__ CompositingMode ;

/* Variables and functions */
 int /*<<< orphan*/  CombineModeReplace ; 
 scalar_t__ CompositingModeSourceCopy ; 
 scalar_t__ CompositingModeSourceOver ; 
 scalar_t__ CompositingQualityHighQuality ; 
 scalar_t__ CompositingQualityHighSpeed ; 
 int /*<<< orphan*/  GdipBeginContainer2 (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  GdipCreateFromHDC (int /*<<< orphan*/ *,int /*<<< orphan*/ **) ; 
 int /*<<< orphan*/  GdipCreateMatrix (int /*<<< orphan*/ **) ; 
 int /*<<< orphan*/  GdipCreateMatrix2 (int,int,int,int,int,int,int /*<<< orphan*/ **) ; 
 int /*<<< orphan*/  GdipDeleteGraphics (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  GdipDeleteMatrix (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  GdipEndContainer (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  GdipGetClipBounds (int /*<<< orphan*/ *,TYPE_1__*) ; 
 int /*<<< orphan*/  GdipGetCompositingMode (int /*<<< orphan*/ *,scalar_t__*) ; 
 int /*<<< orphan*/  GdipGetCompositingQuality (int /*<<< orphan*/ *,scalar_t__*) ; 
 int /*<<< orphan*/  GdipGetInterpolationMode (int /*<<< orphan*/ *,scalar_t__*) ; 
 int /*<<< orphan*/  GdipGetMatrixElements (int /*<<< orphan*/ *,int*) ; 
 int /*<<< orphan*/  GdipGetPageScale (int /*<<< orphan*/ *,int*) ; 
 int /*<<< orphan*/  GdipGetPageUnit (int /*<<< orphan*/ *,scalar_t__*) ; 
 int /*<<< orphan*/  GdipGetPixelOffsetMode (int /*<<< orphan*/ *,scalar_t__*) ; 
 int /*<<< orphan*/  GdipGetSmoothingMode (int /*<<< orphan*/ *,scalar_t__*) ; 
 int /*<<< orphan*/  GdipGetTextContrast (int /*<<< orphan*/ *,scalar_t__*) ; 
 int /*<<< orphan*/  GdipGetTextRenderingHint (int /*<<< orphan*/ *,scalar_t__*) ; 
 int /*<<< orphan*/  GdipGetWorldTransform (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  GdipSetClipRect (int /*<<< orphan*/ *,int,int,int,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  GdipSetCompositingMode (int /*<<< orphan*/ *,scalar_t__) ; 
 int /*<<< orphan*/  GdipSetCompositingQuality (int /*<<< orphan*/ *,scalar_t__) ; 
 int /*<<< orphan*/  GdipSetInterpolationMode (int /*<<< orphan*/ *,scalar_t__) ; 
 int /*<<< orphan*/  GdipSetPageScale (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  GdipSetPageUnit (int /*<<< orphan*/ *,scalar_t__) ; 
 int /*<<< orphan*/  GdipSetPixelOffsetMode (int /*<<< orphan*/ *,scalar_t__) ; 
 int /*<<< orphan*/  GdipSetSmoothingMode (int /*<<< orphan*/ *,scalar_t__) ; 
 int /*<<< orphan*/  GdipSetTextContrast (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  GdipSetTextRenderingHint (int /*<<< orphan*/ *,scalar_t__) ; 
 int /*<<< orphan*/  GdipSetWorldTransform (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * GetDC (int /*<<< orphan*/ ) ; 
 scalar_t__ InterpolationModeBilinear ; 
 scalar_t__ InterpolationModeHighQualityBicubic ; 
 int /*<<< orphan*/  InvalidParameter ; 
 int /*<<< orphan*/  Ok ; 
 scalar_t__ PixelOffsetModeHalf ; 
 scalar_t__ PixelOffsetModeHighSpeed ; 
 int /*<<< orphan*/  ReleaseDC (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 scalar_t__ SmoothingModeAntiAlias ; 
 scalar_t__ SmoothingModeNone ; 
 scalar_t__ TextRenderingHintAntiAlias ; 
 scalar_t__ TextRenderingHintClearTypeGridFit ; 
 scalar_t__ UnitDocument ; 
 scalar_t__ UnitPixel ; 
 int /*<<< orphan*/  expect (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 double fabs (int) ; 
 int /*<<< orphan*/  hwnd ; 
 int /*<<< orphan*/  ok (int,char*,...) ; 

__attribute__((used)) static void test_BeginContainer2(void)
{
    GpMatrix *transform;
    GpRectF clip;
    REAL defClip[] = {5, 10, 15, 20};
    REAL elems[6], defTrans[] = {1, 2, 3, 4, 5, 6};
    GraphicsContainer cont1, cont2, cont3, cont4;
    CompositingQuality compqual, defCompqual = CompositingQualityHighSpeed;
    CompositingMode compmode, defCompmode = CompositingModeSourceOver;
    InterpolationMode interp, defInterp = InterpolationModeHighQualityBicubic;
    REAL scale, defScale = 17;
    GpUnit unit, defUnit = UnitPixel;
    PixelOffsetMode offsetmode, defOffsetmode = PixelOffsetModeHighSpeed;
    SmoothingMode smoothmode, defSmoothmode = SmoothingModeAntiAlias;
    UINT contrast, defContrast = 5;
    TextRenderingHint texthint, defTexthint = TextRenderingHintAntiAlias;

    GpStatus status;
    GpGraphics *graphics = NULL;
    HDC hdc = GetDC( hwnd );

    ok(hdc != NULL, "Expected HDC to be initialized\n");

    status = GdipCreateFromHDC(hdc, &graphics);
    expect(Ok, status);
    ok(graphics != NULL, "Expected graphics to be initialized\n");

    /* null graphics, null container */
    status = GdipBeginContainer2(NULL, &cont1);
    expect(InvalidParameter, status);

    status = GdipBeginContainer2(graphics, NULL);
    expect(InvalidParameter, status);

    status = GdipEndContainer(NULL, cont1);
    expect(InvalidParameter, status);

    /* test all quality-related values */
    GdipSetCompositingMode(graphics, defCompmode);
    GdipSetCompositingQuality(graphics, defCompqual);
    GdipSetInterpolationMode(graphics, defInterp);
    GdipSetPageScale(graphics, defScale);
    GdipSetPageUnit(graphics, defUnit);
    GdipSetPixelOffsetMode(graphics, defOffsetmode);
    GdipSetSmoothingMode(graphics, defSmoothmode);
    GdipSetTextContrast(graphics, defContrast);
    GdipSetTextRenderingHint(graphics, defTexthint);

    status = GdipBeginContainer2(graphics, &cont1);
    expect(Ok, status);

    GdipSetCompositingMode(graphics, CompositingModeSourceCopy);
    GdipSetCompositingQuality(graphics, CompositingQualityHighQuality);
    GdipSetInterpolationMode(graphics, InterpolationModeBilinear);
    GdipSetPageScale(graphics, 10);
    GdipSetPageUnit(graphics, UnitDocument);
    GdipSetPixelOffsetMode(graphics, PixelOffsetModeHalf);
    GdipSetSmoothingMode(graphics, SmoothingModeNone);
    GdipSetTextContrast(graphics, 7);
    GdipSetTextRenderingHint(graphics, TextRenderingHintClearTypeGridFit);

    status = GdipEndContainer(graphics, cont1);
    expect(Ok, status);

    GdipGetCompositingMode(graphics, &compmode);
    ok(defCompmode == compmode, "Expected Compositing Mode to be restored to %d, got %d\n", defCompmode, compmode);

    GdipGetCompositingQuality(graphics, &compqual);
    ok(defCompqual == compqual, "Expected Compositing Quality to be restored to %d, got %d\n", defCompqual, compqual);

    GdipGetInterpolationMode(graphics, &interp);
    ok(defInterp == interp, "Expected Interpolation Mode to be restored to %d, got %d\n", defInterp, interp);

    GdipGetPageScale(graphics, &scale);
    ok(fabs(defScale - scale) < 0.0001, "Expected Page Scale to be restored to %f, got %f\n", defScale, scale);

    GdipGetPageUnit(graphics, &unit);
    ok(defUnit == unit, "Expected Page Unit to be restored to %d, got %d\n", defUnit, unit);

    GdipGetPixelOffsetMode(graphics, &offsetmode);
    ok(defOffsetmode == offsetmode, "Expected Pixel Offset Mode to be restored to %d, got %d\n", defOffsetmode, offsetmode);

    GdipGetSmoothingMode(graphics, &smoothmode);
    ok(defSmoothmode == smoothmode, "Expected Smoothing Mode to be restored to %d, got %d\n", defSmoothmode, smoothmode);

    GdipGetTextContrast(graphics, &contrast);
    ok(defContrast == contrast, "Expected Text Contrast to be restored to %d, got %d\n", defContrast, contrast);

    status = GdipGetTextRenderingHint(graphics, &texthint);
    expect(Ok, status);
    ok(defTexthint == texthint, "Expected Text Hint to be restored to %d, got %d\n", defTexthint, texthint);

    /* test world transform */
    status = GdipBeginContainer2(graphics, &cont1);
    expect(Ok, status);

    status = GdipCreateMatrix2(defTrans[0], defTrans[1], defTrans[2], defTrans[3],
            defTrans[4], defTrans[5], &transform);
    expect(Ok, status);
    GdipSetWorldTransform(graphics, transform);
    GdipDeleteMatrix(transform);
    transform = NULL;

    status = GdipBeginContainer2(graphics, &cont2);
    expect(Ok, status);

    status = GdipCreateMatrix2(10, 20, 30, 40, 50, 60, &transform);
    expect(Ok, status);
    status = GdipSetWorldTransform(graphics, transform);
    expect(Ok, status);
    GdipDeleteMatrix(transform);
    transform = NULL;

    status = GdipEndContainer(graphics, cont2);
    expect(Ok, status);

    status = GdipCreateMatrix(&transform);
    expect(Ok, status);
    status = GdipGetWorldTransform(graphics, transform);
    expect(Ok, status);
    status = GdipGetMatrixElements(transform, elems);
    expect(Ok, status);
    ok(fabs(defTrans[0] - elems[0]) < 0.0001 &&
            fabs(defTrans[1] - elems[1]) < 0.0001 &&
            fabs(defTrans[2] - elems[2]) < 0.0001 &&
            fabs(defTrans[3] - elems[3]) < 0.0001 &&
            fabs(defTrans[4] - elems[4]) < 0.0001 &&
            fabs(defTrans[5] - elems[5]) < 0.0001,
            "Expected World Transform Matrix to be restored to [%f, %f, %f, %f, %f, %f], got [%f, %f, %f, %f, %f, %f]\n",
            defTrans[0], defTrans[1], defTrans[2], defTrans[3], defTrans[4], defTrans[5],
            elems[0], elems[1], elems[2], elems[3], elems[4], elems[5]);
    GdipDeleteMatrix(transform);
    transform = NULL;

    status = GdipEndContainer(graphics, cont1);
    expect(Ok, status);

    /* test clipping */
    status = GdipBeginContainer2(graphics, &cont1);
    expect(Ok, status);

    status = GdipSetClipRect(graphics, defClip[0], defClip[1], defClip[2], defClip[3], CombineModeReplace);
    expect(Ok, status);

    status = GdipBeginContainer2(graphics, &cont2);
    expect(Ok, status);

    status = GdipSetClipRect(graphics, 2, 4, 6, 8, CombineModeReplace);
    expect(Ok, status);

    status = GdipEndContainer(graphics, cont2);
    expect(Ok, status);

    status = GdipGetClipBounds(graphics, &clip);
    expect(Ok, status);

    ok(fabs(defClip[0] - clip.X) < 0.0001 &&
            fabs(defClip[1] - clip.Y) < 0.0001 &&
            fabs(defClip[2] - clip.Width) < 0.0001 &&
            fabs(defClip[3] - clip.Height) < 0.0001,
            "Expected Clipping Rectangle to be restored to [%f, %f, %f, %f], got [%f, %f, %f, %f]\n",
            defClip[0], defClip[1], defClip[2], defClip[3],
            clip.X, clip.Y, clip.Width, clip.Height);

    status = GdipEndContainer(graphics, cont1);
    expect(Ok, status);

    /* nesting */
    status = GdipBeginContainer2(graphics, &cont1);
    expect(Ok, status);

    status = GdipBeginContainer2(graphics, &cont2);
    expect(Ok, status);

    status = GdipBeginContainer2(graphics, &cont3);
    expect(Ok, status);

    status = GdipEndContainer(graphics, cont3);
    expect(Ok, status);

    status = GdipBeginContainer2(graphics, &cont4);
    expect(Ok, status);

    status = GdipEndContainer(graphics, cont4);
    expect(Ok, status);

    /* skip cont2 */
    status = GdipEndContainer(graphics, cont1);
    expect(Ok, status);

    /* end an already-ended container */
    status = GdipEndContainer(graphics, cont1);
    expect(Ok, status);

    GdipDeleteGraphics(graphics);
    ReleaseDC(hwnd, hdc);
}
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
struct TYPE_9__ {double X; double Y; } ;
struct TYPE_8__ {double X; double Y; double Width; double Height; } ;
typedef  double REAL ;
typedef  int /*<<< orphan*/  MSG ;
typedef  int /*<<< orphan*/  HDC ;
typedef  int /*<<< orphan*/  GpTexture ;
typedef  int /*<<< orphan*/  GpStatus ;
typedef  TYPE_1__ GpRectF ;
typedef  TYPE_2__ GpPointF ;
typedef  int /*<<< orphan*/  GpMatrix ;
typedef  int /*<<< orphan*/  GpLineGradient ;
typedef  int /*<<< orphan*/  GpImage ;
typedef  int /*<<< orphan*/  GpGraphics ;
typedef  int /*<<< orphan*/  GpBrush ;
typedef  int /*<<< orphan*/  GpBitmap ;
typedef  int /*<<< orphan*/  BOOL ;
typedef  int /*<<< orphan*/  ARGB ;

/* Variables and functions */
 int /*<<< orphan*/  DispatchMessageW (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  GdipCreateBitmapFromGraphics (int,int,int /*<<< orphan*/ *,int /*<<< orphan*/ **) ; 
 int /*<<< orphan*/  GdipCreateFromHDC (int /*<<< orphan*/ ,int /*<<< orphan*/ **) ; 
 int /*<<< orphan*/  GdipCreateFromHWND (int /*<<< orphan*/ ,int /*<<< orphan*/ **) ; 
 int /*<<< orphan*/  GdipCreateLineBrush (TYPE_2__*,TYPE_2__*,int /*<<< orphan*/ ,int,int /*<<< orphan*/ ,int /*<<< orphan*/ **) ; 
 int /*<<< orphan*/  GdipCreateLineBrushFromRect (TYPE_1__*,int /*<<< orphan*/ ,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ **) ; 
 int /*<<< orphan*/  GdipCreateMatrix2 (double,double,double,double,double,double,int /*<<< orphan*/ **) ; 
 int /*<<< orphan*/  GdipCreateTexture (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ **) ; 
 int /*<<< orphan*/  GdipDeleteBrush (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  GdipDeleteGraphics (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  GdipDeleteMatrix (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  GdipDisposeImage (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  GdipFillRectangle (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int,int,int,int) ; 
 int /*<<< orphan*/  GdipGetLineRect (int /*<<< orphan*/ *,TYPE_1__*) ; 
 int /*<<< orphan*/  GdipGetLineTransform (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  GdipGetMatrixElements (int /*<<< orphan*/ *,double*) ; 
 int /*<<< orphan*/  GdipGetTextureTransform (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  GdipIsMatrixEqual (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  GdipIsMatrixIdentity (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  GdipMultiplyLineTransform (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  GdipResetLineTransform (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  GdipResetTextureTransform (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  GdipRotateMatrix (int /*<<< orphan*/ *,double,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  GdipScaleLineTransform (int /*<<< orphan*/ *,double,double,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  GdipScaleMatrix (int /*<<< orphan*/ *,double,double,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  GdipSetLineTransform (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  GdipSetMatrixElements (int /*<<< orphan*/ *,double,double,double,double,double,double) ; 
 int /*<<< orphan*/  GdipSetTextureTransform (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  GdipTranslateLineTransform (int /*<<< orphan*/ *,double,double,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  GetDC (int /*<<< orphan*/ ) ; 
 scalar_t__ GetMessageW (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  InvalidParameter ; 
 int /*<<< orphan*/  LinearGradientModeHorizontal ; 
 int /*<<< orphan*/  MatrixOrderAppend ; 
 int /*<<< orphan*/  MatrixOrderPrepend ; 
 int /*<<< orphan*/  Ok ; 
 int /*<<< orphan*/  ReleaseDC (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  TRUE ; 
 int /*<<< orphan*/  TranslateMessage (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  WrapModeTile ; 
 int /*<<< orphan*/  expect (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  expectf (double,double) ; 
 int /*<<< orphan*/  hwnd ; 
 int /*<<< orphan*/  memset (TYPE_1__*,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static void test_transform(void)
{
    GpStatus status;
    GpTexture *texture;
    GpLineGradient *line;
    GpGraphics *graphics = NULL;
    GpBitmap *bitmap;
    HDC hdc = GetDC(0);
    GpMatrix *m, *m1;
    BOOL res;
    GpPointF start, end;
    GpRectF rectf;
    REAL elements[6];

    /* GpTexture */
    status = GdipCreateMatrix2(2.0, 0.0, 0.0, 0.0, 0.0, 0.0, &m);
    expect(Ok, status);

    status = GdipCreateFromHDC(hdc, &graphics);
    expect(Ok, status);
    status = GdipCreateBitmapFromGraphics(1, 1, graphics, &bitmap);
    expect(Ok, status);

    status = GdipCreateTexture((GpImage*)bitmap, WrapModeTile, &texture);
    expect(Ok, status);

    /* NULL */
    status = GdipGetTextureTransform(NULL, NULL);
    expect(InvalidParameter, status);
    status = GdipGetTextureTransform(texture, NULL);
    expect(InvalidParameter, status);

    /* get default value - identity matrix */
    status = GdipGetTextureTransform(texture, m);
    expect(Ok, status);
    status = GdipIsMatrixIdentity(m, &res);
    expect(Ok, status);
    expect(TRUE, res);
    /* set and get then */
    status = GdipCreateMatrix2(2.0, 0.0, 0.0, 2.0, 0.0, 0.0, &m1);
    expect(Ok, status);
    status = GdipSetTextureTransform(texture, m1);
    expect(Ok, status);
    status = GdipGetTextureTransform(texture, m);
    expect(Ok, status);
    status = GdipIsMatrixEqual(m, m1, &res);
    expect(Ok, status);
    expect(TRUE, res);
    /* reset */
    status = GdipResetTextureTransform(texture);
    expect(Ok, status);
    status = GdipGetTextureTransform(texture, m);
    expect(Ok, status);
    status = GdipIsMatrixIdentity(m, &res);
    expect(Ok, status);
    expect(TRUE, res);

    status = GdipDeleteBrush((GpBrush*)texture);
    expect(Ok, status);

    status = GdipDeleteMatrix(m1);
    expect(Ok, status);
    status = GdipDeleteMatrix(m);
    expect(Ok, status);
    status = GdipDisposeImage((GpImage*)bitmap);
    expect(Ok, status);
    status = GdipDeleteGraphics(graphics);
    expect(Ok, status);



    status = GdipCreateFromHWND(hwnd, &graphics);
    expect(Ok, status);

    /* GpLineGradient */
    /* create with vertical gradient line */
    start.X = start.Y = end.X = 0.0;
    end.Y = 100.0;

    status = GdipCreateLineBrush(&start, &end, (ARGB)0xffff0000, 0xff00ff00, WrapModeTile, &line);
    expect(Ok, status);

    status = GdipCreateMatrix2(1.0, 0.0, 0.0, 1.0, 0.0, 0.0, &m);
    expect(Ok, status);

    /* NULL arguments */
    status = GdipResetLineTransform(NULL);
    expect(InvalidParameter, status);
    status = GdipSetLineTransform(NULL, m);
    expect(InvalidParameter, status);
    status = GdipSetLineTransform(line, NULL);
    expect(InvalidParameter, status);
    status = GdipGetLineTransform(NULL, m);
    expect(InvalidParameter, status);
    status = GdipGetLineTransform(line, NULL);
    expect(InvalidParameter, status);
    status = GdipScaleLineTransform(NULL, 1, 1, MatrixOrderPrepend);
    expect(InvalidParameter, status);
    status = GdipMultiplyLineTransform(NULL, m, MatrixOrderPrepend);
    expect(InvalidParameter, status);
    status = GdipTranslateLineTransform(NULL, 0, 0, MatrixOrderPrepend);
    expect(InvalidParameter, status);

    /* initial transform */
    status = GdipGetLineTransform(line, m);
    expect(Ok, status);

    status = GdipGetMatrixElements(m, elements);
    expect(Ok, status);
    expectf(0.0, elements[0]);
    expectf(1.0, elements[1]);
    expectf(-1.0, elements[2]);
    expectf(0.0, elements[3]);
    expectf(50.0, elements[4]);
    expectf(50.0, elements[5]);

    status = GdipGetLineRect(line, &rectf);
    expect(Ok, status);
    expectf(-50.0, rectf.X);
    expectf(0.0, rectf.Y);
    expectf(100.0, rectf.Width);
    expectf(100.0, rectf.Height);

    status = GdipFillRectangle(graphics, (GpBrush*)line, 0, 0, 200, 200);
    expect(Ok, status);

    /* manually set transform */
    GdipSetMatrixElements(m, 2.0, 0.0, 0.0, 4.0, 0.0, 0.0);

    status = GdipSetLineTransform(line, m);
    expect(Ok, status);

    status = GdipGetLineTransform(line, m);
    expect(Ok, status);

    status = GdipGetMatrixElements(m, elements);
    expect(Ok, status);
    expectf(2.0, elements[0]);
    expectf(0.0, elements[1]);
    expectf(0.0, elements[2]);
    expectf(4.0, elements[3]);
    expectf(0.0, elements[4]);
    expectf(0.0, elements[5]);

    status = GdipGetLineRect(line, &rectf);
    expect(Ok, status);
    expectf(-50.0, rectf.X);
    expectf(0.0, rectf.Y);
    expectf(100.0, rectf.Width);
    expectf(100.0, rectf.Height);

    status = GdipFillRectangle(graphics, (GpBrush*)line, 200, 0, 200, 200);
    expect(Ok, status);

    /* scale transform */
    status = GdipScaleLineTransform(line, 4.0, 0.5, MatrixOrderAppend);
    expect(Ok, status);

    status = GdipGetLineTransform(line, m);
    expect(Ok, status);

    status = GdipGetMatrixElements(m, elements);
    expect(Ok, status);
    expectf(8.0, elements[0]);
    expectf(0.0, elements[1]);
    expectf(0.0, elements[2]);
    expectf(2.0, elements[3]);
    expectf(0.0, elements[4]);
    expectf(0.0, elements[5]);

    status = GdipGetLineRect(line, &rectf);
    expect(Ok, status);
    expectf(-50.0, rectf.X);
    expectf(0.0, rectf.Y);
    expectf(100.0, rectf.Width);
    expectf(100.0, rectf.Height);

    status = GdipFillRectangle(graphics, (GpBrush*)line, 400, 0, 200, 200);
    expect(Ok, status);

    /* translate transform */
    status = GdipTranslateLineTransform(line, 10.0, -20.0, MatrixOrderAppend);
    expect(Ok, status);

    status = GdipGetLineTransform(line, m);
    expect(Ok, status);

    status = GdipGetMatrixElements(m, elements);
    expect(Ok, status);
    expectf(8.0, elements[0]);
    expectf(0.0, elements[1]);
    expectf(0.0, elements[2]);
    expectf(2.0, elements[3]);
    expectf(10.0, elements[4]);
    expectf(-20.0, elements[5]);

    status = GdipGetLineRect(line, &rectf);
    expect(Ok, status);
    expectf(-50.0, rectf.X);
    expectf(0.0, rectf.Y);
    expectf(100.0, rectf.Width);
    expectf(100.0, rectf.Height);

    status = GdipFillRectangle(graphics, (GpBrush*)line, 0, 200, 200, 200);
    expect(Ok, status);

    /* multiply transform */
    GdipSetMatrixElements(m, 1.0, 0.0, 0.0, 1.0, 0.0, 0.0);
    GdipRotateMatrix(m, 45.0, MatrixOrderAppend);
    GdipScaleMatrix(m, 0.25, 0.5, MatrixOrderAppend);

    status = GdipMultiplyLineTransform(line, m, MatrixOrderAppend);
    expect(Ok, status);

    /* NULL transform does nothing */
    status = GdipMultiplyLineTransform(line, NULL, MatrixOrderAppend);
    expect(Ok, status);

    status = GdipGetLineTransform(line, m);
    expect(Ok, status);

    status = GdipGetMatrixElements(m, elements);
    expect(Ok, status);
    expectf(1.414214, elements[0]);
    expectf(2.828427, elements[1]);
    expectf(-0.353553, elements[2]);
    expectf(0.707107, elements[3]);
    expectf(5.303300, elements[4]);
    expectf(-3.535534, elements[5]);

    status = GdipGetLineRect(line, &rectf);
    expect(Ok, status);
    expectf(-50.0, rectf.X);
    expectf(0.0, rectf.Y);
    expectf(100.0, rectf.Width);
    expectf(100.0, rectf.Height);

    status = GdipFillRectangle(graphics, (GpBrush*)line, 200, 200, 200, 200);
    expect(Ok, status);

    /* reset transform sets to identity */
    status = GdipResetLineTransform(line);
    expect(Ok, status);

    status = GdipGetLineTransform(line, m);
    expect(Ok, status);

    status = GdipGetMatrixElements(m, elements);
    expect(Ok, status);
    expectf(1.0, elements[0]);
    expectf(0.0, elements[1]);
    expectf(0.0, elements[2]);
    expectf(1.0, elements[3]);
    expectf(0.0, elements[4]);
    expectf(0.0, elements[5]);

    status = GdipGetLineRect(line, &rectf);
    expect(Ok, status);
    expectf(-50.0, rectf.X);
    expectf(0.0, rectf.Y);
    expectf(100.0, rectf.Width);
    expectf(100.0, rectf.Height);

    status = GdipFillRectangle(graphics, (GpBrush*)line, 400, 200, 200, 200);
    expect(Ok, status);

    GdipDeleteBrush((GpBrush*)line);

    /* passing negative Width/Height to LinearGradientModeHorizontal */
    rectf.X = rectf.Y = 10.0;
    rectf.Width = rectf.Height = -100.0;
    status = GdipCreateLineBrushFromRect(&rectf, (ARGB)0xffff0000, 0xff00ff00,
            LinearGradientModeHorizontal, WrapModeTile, &line);
    expect(Ok, status);
    memset(&rectf, 0, sizeof(GpRectF));
    status = GdipGetLineRect(line, &rectf);
    expect(Ok, status);
    expectf(10.0, rectf.X);
    expectf(10.0, rectf.Y);
    expectf(-100.0, rectf.Width);
    expectf(-100.0, rectf.Height);
    status = GdipGetLineTransform(line, m);
    expect(Ok, status);
    status = GdipGetMatrixElements(m, elements);
    expect(Ok,status);
    expectf(1.0, elements[0]);
    expectf(0.0, elements[1]);
    expectf(0.0, elements[2]);
    expectf(1.0, elements[3]);
    expectf(0.0, elements[4]);
    expectf(0.0, elements[5]);
    status = GdipFillRectangle(graphics, (GpBrush*)line, 0, 400, 200, 200);
    expect(Ok, status);
    status = GdipDeleteBrush((GpBrush*)line);
    expect(Ok,status);

    if(0){
        /* enable to visually compare with Windows */
        MSG msg;
        while(GetMessageW(&msg, hwnd, 0, 0) > 0){
            TranslateMessage(&msg);
            DispatchMessageW(&msg);
        }
    }

    GdipDeleteMatrix(m);
    GdipDeleteGraphics(graphics);
    ReleaseDC(0, hdc);
}
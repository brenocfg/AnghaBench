#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */

/* Type definitions */
typedef  int /*<<< orphan*/  REAL ;
typedef  int /*<<< orphan*/  GpStatus ;
typedef  int /*<<< orphan*/  GpPen ;
typedef  int /*<<< orphan*/  GpMatrix ;
typedef  int /*<<< orphan*/  ARGB ;

/* Variables and functions */
 int /*<<< orphan*/  GdipCreateMatrix (int /*<<< orphan*/ **) ; 
 int /*<<< orphan*/  GdipCreateMatrix2 (double,double,double,double,double,double,int /*<<< orphan*/ **) ; 
 int /*<<< orphan*/  GdipCreatePen1 (int /*<<< orphan*/ ,float,int /*<<< orphan*/ ,int /*<<< orphan*/ **) ; 
 int /*<<< orphan*/  GdipDeleteMatrix (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  GdipDeletePen (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  GdipGetMatrixElements (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  GdipGetPenTransform (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  GdipMultiplyPenTransform (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  GdipResetPenTransform (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  GdipRotatePenTransform (int /*<<< orphan*/ *,double,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  GdipScalePenTransform (int /*<<< orphan*/ *,double,double,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  GdipSetMatrixElements (int /*<<< orphan*/ *,double,double,double,double,double,double) ; 
 int /*<<< orphan*/  GdipSetPenTransform (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  GdipTranslatePenTransform (int /*<<< orphan*/ *,double,double,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  InvalidParameter ; 
 int /*<<< orphan*/  MatrixOrderAppend ; 
 int /*<<< orphan*/  MatrixOrderPrepend ; 
 int /*<<< orphan*/  Ok ; 
 int /*<<< orphan*/  UnitPixel ; 
 int /*<<< orphan*/  expect (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  expectf (double,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  get_pen_transform (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 

__attribute__((used)) static void test_transform(void)
{
    GpStatus status;
    GpPen *pen;
    GpMatrix *matrix, *matrix2;
    REAL values[6];

    status = GdipCreatePen1((ARGB)0xffff00ff, 10.0f, UnitPixel, &pen);
    expect(Ok, status);

    status = GdipCreateMatrix(&matrix);
    expect(Ok, status);

    status = GdipGetPenTransform(pen, matrix);
    expect(Ok, status);

    status = GdipGetMatrixElements(matrix, values);
    expect(Ok, status);

    expectf(1.0, values[0]);
    expectf(0.0, values[1]);
    expectf(0.0, values[2]);
    expectf(1.0, values[3]);
    expectf(0.0, values[4]);
    expectf(0.0, values[5]);

    GdipCreateMatrix2(3.0, -2.0, 5.0, 2.0, 6.0, 3.0, &matrix2);
    status = GdipSetPenTransform(pen, matrix2);
    expect(Ok, status);
    GdipDeleteMatrix(matrix2);

    status = GdipGetPenTransform(pen, matrix);
    expect(Ok, status);
    status = GdipGetMatrixElements(matrix, values);
    expect(Ok, status);
    expectf(3.0,  values[0]);
    expectf(-2.0,  values[1]);
    expectf(5.0,  values[2]);
    expectf(2.0, values[3]);
    expectf(6.0, values[4]);
    expectf(3.0,  values[5]);

    /* Translate */
    status = GdipTranslatePenTransform(NULL, 1.0, -2.0, MatrixOrderAppend);
    expect(InvalidParameter, status);

    status = GdipTranslatePenTransform(pen, 1.0, -2.0, MatrixOrderAppend);
    expect(Ok, status);

    status = GdipGetPenTransform(pen, matrix);
    expect(Ok, status);
    status = GdipGetMatrixElements(matrix, values);
    expect(Ok, status);
    expectf(3.0,  values[0]);
    expectf(-2.0,  values[1]);
    expectf(5.0,  values[2]);
    expectf(2.0, values[3]);
    expectf(7.0, values[4]);
    expectf(1.0,  values[5]);

    status = GdipTranslatePenTransform(pen, -3.0, 5.0, MatrixOrderPrepend);
    expect(Ok, status);

    status = GdipGetPenTransform(pen, matrix);
    expect(Ok, status);
    status = GdipGetMatrixElements(matrix, values);
    expect(Ok, status);
    expectf(3.0,  values[0]);
    expectf(-2.0,  values[1]);
    expectf(5.0,  values[2]);
    expectf(2.0, values[3]);
    expectf(23.0, values[4]);
    expectf(17.0,  values[5]);

    status = GdipResetPenTransform(pen);
    expect(Ok, status);

    status = GdipGetPenTransform(pen, matrix);
    expect(Ok, status);
    status = GdipGetMatrixElements(matrix, values);
    expect(Ok, status);

    expectf(1.0, values[0]);
    expectf(0.0, values[1]);
    expectf(0.0, values[2]);
    expectf(1.0, values[3]);
    expectf(0.0, values[4]);
    expectf(0.0, values[5]);

    /* Scale */
    status = GdipScalePenTransform(NULL, 1.0, 1.0, MatrixOrderPrepend);
    expect(InvalidParameter, status);

    status = GdipScalePenTransform(pen, 1.0, 1.0, MatrixOrderPrepend);
    expect(Ok, status);

    get_pen_transform(pen, values);
    expectf(1.0, values[0]);
    expectf(0.0, values[1]);
    expectf(0.0, values[2]);
    expectf(1.0, values[3]);
    expectf(0.0, values[4]);
    expectf(0.0, values[5]);

    status = GdipScalePenTransform(pen, 2.0, -10.0, MatrixOrderPrepend);
    expect(Ok, status);

    get_pen_transform(pen, values);
    expectf(2.0, values[0]);
    expectf(0.0, values[1]);
    expectf(0.0, values[2]);
    expectf(-10.0, values[3]);
    expectf(0.0, values[4]);
    expectf(0.0, values[5]);

    status = GdipScalePenTransform(pen, 2.0, -10.0, MatrixOrderAppend);
    expect(Ok, status);

    get_pen_transform(pen, values);
    expectf(4.0, values[0]);
    expectf(0.0, values[1]);
    expectf(0.0, values[2]);
    expectf(100.0, values[3]);
    expectf(0.0, values[4]);
    expectf(0.0, values[5]);

    status = GdipTranslatePenTransform(pen, 1.0, -2.0, MatrixOrderAppend);
    expect(Ok, status);

    get_pen_transform(pen, values);
    expectf(4.0, values[0]);
    expectf(0.0, values[1]);
    expectf(0.0, values[2]);
    expectf(100.0, values[3]);
    expectf(1.0, values[4]);
    expectf(-2.0, values[5]);

    status = GdipScalePenTransform(pen, 2.0, -10.0, MatrixOrderPrepend);
    expect(Ok, status);

    get_pen_transform(pen, values);
    expectf(8.0, values[0]);
    expectf(0.0, values[1]);
    expectf(0.0, values[2]);
    expectf(-1000.0, values[3]);
    expectf(1.0, values[4]);
    expectf(-2.0, values[5]);

    /* Multiply */
    status = GdipResetPenTransform(pen);
    expect(Ok, status);

    status = GdipSetMatrixElements(matrix, 2.0, 1.0, 1.0, 4.0, 1.0, 2.0);
    expect(Ok, status);

    status = GdipMultiplyPenTransform(NULL, matrix, MatrixOrderPrepend);
    expect(InvalidParameter, status);

    status = GdipMultiplyPenTransform(pen, matrix, MatrixOrderPrepend);
    expect(Ok, status);

    get_pen_transform(pen, values);
    expectf(2.0, values[0]);
    expectf(1.0, values[1]);
    expectf(1.0, values[2]);
    expectf(4.0, values[3]);
    expectf(1.0, values[4]);
    expectf(2.0, values[5]);

    status = GdipScalePenTransform(pen, 2.0, -10.0, MatrixOrderAppend);
    expect(Ok, status);

    status = GdipMultiplyPenTransform(pen, matrix, MatrixOrderAppend);
    expect(Ok, status);

    get_pen_transform(pen, values);
    expectf(-2.0, values[0]);
    expectf(-36.0, values[1]);
    expectf(-36.0, values[2]);
    expectf(-158.0, values[3]);
    expectf(-15.0, values[4]);
    expectf(-76.0, values[5]);

    /* Rotate */
    status = GdipResetPenTransform(pen);
    expect(Ok, status);

    status = GdipSetMatrixElements(matrix, 2.0, 1.0, 1.0, 4.0, 1.0, 2.0);
    expect(Ok, status);

    status = GdipSetPenTransform(pen, matrix);
    expect(Ok, status);

    status = GdipRotatePenTransform(NULL, 10.0, MatrixOrderPrepend);
    expect(InvalidParameter, status);

    status = GdipRotatePenTransform(pen, 45.0, MatrixOrderPrepend);
    expect(Ok, status);

    get_pen_transform(pen, values);
    expectf(2.12, values[0]);
    expectf(3.54, values[1]);
    expectf(-0.71, values[2]);
    expectf(2.12, values[3]);
    expectf(1.0, values[4]);
    expectf(2.0, values[5]);

    status = GdipScalePenTransform(pen, 2.0, -10.0, MatrixOrderAppend);
    expect(Ok, status);

    status = GdipRotatePenTransform(pen, 180.0, MatrixOrderAppend);
    expect(Ok, status);

    get_pen_transform(pen, values);
    expectf(-4.24, values[0]);
    expectf(35.36, values[1]);
    expectf(1.41, values[2]);
    expectf(21.21, values[3]);
    expectf(-2.0, values[4]);
    expectf(20.0, values[5]);

    GdipDeletePen(pen);

    GdipDeleteMatrix(matrix);
}
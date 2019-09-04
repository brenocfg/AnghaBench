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
typedef  int /*<<< orphan*/  GpStatus ;
typedef  int /*<<< orphan*/  GpMatrix ;
typedef  int /*<<< orphan*/  BOOL ;

/* Variables and functions */
 int /*<<< orphan*/  GdipCreateMatrix2 (double,double,double,double,double,double,int /*<<< orphan*/ **) ; 
 int /*<<< orphan*/  GdipDeleteMatrix (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  GdipIsMatrixEqual (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  GdipShearMatrix (int /*<<< orphan*/ *,double,double,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  InvalidParameter ; 
 int /*<<< orphan*/  MatrixOrderAppend ; 
 int /*<<< orphan*/  MatrixOrderPrepend ; 
 int /*<<< orphan*/  Ok ; 
 int /*<<< orphan*/  TRUE ; 
 int /*<<< orphan*/  expect (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void test_shear(void)
{
    GpStatus status;
    GpMatrix *matrix  = NULL;
    GpMatrix *sheared = NULL;
    BOOL equal;

    /* NULL */
    status = GdipShearMatrix(NULL, 0.0, 0.0, MatrixOrderPrepend);
    expect(InvalidParameter, status);

    /* X only shearing, MatrixOrderPrepend */
    GdipCreateMatrix2(1.0, 2.0, 4.0, -1.0, 6.0, 3.0, &matrix);
    status = GdipShearMatrix(matrix, 1.5, 0.0, MatrixOrderPrepend);
    expect(Ok, status);
    GdipCreateMatrix2(1.0, 2.0, 5.5, 2.0, 6.0, 3.0, &sheared);
    GdipIsMatrixEqual(matrix, sheared, &equal);
    expect(TRUE, equal);
    GdipDeleteMatrix(sheared);
    GdipDeleteMatrix(matrix);

    /* X only shearing, MatrixOrderAppend */
    GdipCreateMatrix2(1.0, 2.0, 4.0, -1.0, 6.0, 3.0, &matrix);
    status = GdipShearMatrix(matrix, 1.5, 0.0, MatrixOrderAppend);
    expect(Ok, status);
    GdipCreateMatrix2(4.0, 2.0, 2.5, -1.0, 10.5, 3.0, &sheared);
    GdipIsMatrixEqual(matrix, sheared, &equal);
    expect(TRUE, equal);
    GdipDeleteMatrix(sheared);
    GdipDeleteMatrix(matrix);

    /* Y only shearing, MatrixOrderPrepend */
    GdipCreateMatrix2(1.0, 2.0, 4.0, -1.0, 6.0, 3.0, &matrix);
    status = GdipShearMatrix(matrix, 0.0, 1.5, MatrixOrderPrepend);
    expect(Ok, status);
    GdipCreateMatrix2(7.0, 0.5, 4.0, -1.0, 6.0, 3.0, &sheared);
    GdipIsMatrixEqual(matrix, sheared, &equal);
    expect(TRUE, equal);
    GdipDeleteMatrix(sheared);
    GdipDeleteMatrix(matrix);

    /* Y only shearing, MatrixOrderAppend */
    GdipCreateMatrix2(1.0, 2.0, 4.0, -1.0, 6.0, 3.0, &matrix);
    status = GdipShearMatrix(matrix, 0.0, 1.5, MatrixOrderAppend);
    expect(Ok, status);
    GdipCreateMatrix2(1.0, 3.5, 4.0, 5.0, 6.0, 12.0, &sheared);
    GdipIsMatrixEqual(matrix, sheared, &equal);
    expect(TRUE, equal);
    GdipDeleteMatrix(sheared);
    GdipDeleteMatrix(matrix);

    /* X,Y shearing, MatrixOrderPrepend */
    GdipCreateMatrix2(1.0, 2.0, 4.0, -1.0, 6.0, 3.0, &matrix);
    status = GdipShearMatrix(matrix, 4.0, 1.5, MatrixOrderPrepend);
    expect(Ok, status);
    GdipCreateMatrix2(7.0, 0.5, 8.0, 7.0, 6.0, 3.0, &sheared);
    GdipIsMatrixEqual(matrix, sheared, &equal);
    expect(TRUE, equal);
    GdipDeleteMatrix(sheared);
    GdipDeleteMatrix(matrix);

    /* X,Y shearing, MatrixOrderAppend */
    GdipCreateMatrix2(1.0, 2.0, 4.0, -1.0, 6.0, 3.0, &matrix);
    status = GdipShearMatrix(matrix, 4.0, 1.5, MatrixOrderAppend);
    expect(Ok, status);
    GdipCreateMatrix2(9.0, 3.5, 0.0, 5.0, 18.0, 12.0, &sheared);
    GdipIsMatrixEqual(matrix, sheared, &equal);
    expect(TRUE, equal);
    GdipDeleteMatrix(sheared);
    GdipDeleteMatrix(matrix);
}
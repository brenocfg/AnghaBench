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
typedef  int /*<<< orphan*/  GpMatrix ;
typedef  int /*<<< orphan*/  BOOL ;

/* Variables and functions */
 int /*<<< orphan*/  FALSE ; 
 int /*<<< orphan*/  GdipCreateMatrix2 (double,double,double,double,int,int,int /*<<< orphan*/ **) ; 
 int /*<<< orphan*/  GdipDeleteMatrix (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  GdipGetMatrixElements (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  GdipInvertMatrix (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  GdipIsMatrixEqual (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  InvalidParameter ; 
 int /*<<< orphan*/  Ok ; 
 int /*<<< orphan*/  TRUE ; 
 int /*<<< orphan*/  compare_float (int /*<<< orphan*/ ,double,int) ; 
 int /*<<< orphan*/  expect (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ok (int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void test_invert(void)
{
    GpStatus status;
    GpMatrix *matrix = NULL;
    GpMatrix *inverted = NULL;
    BOOL equal = FALSE;
    REAL elems[6];

    /* NULL */
    status = GdipInvertMatrix(NULL);
    expect(InvalidParameter, status);

    /* noninvertible */
    GdipCreateMatrix2(2.0, -1.0, 6.0, -3.0, 2.2, 3.0, &matrix);
    status = GdipInvertMatrix(matrix);
    expect(InvalidParameter, status);
    GdipDeleteMatrix(matrix);

    /* invertible */
    GdipCreateMatrix2(3.0, -2.0, 5.0, 2.0, 6.0, 3.0, &matrix);
    status = GdipInvertMatrix(matrix);
    expect(Ok, status);
    GdipCreateMatrix2(2.0/16.0, 2.0/16.0, -5.0/16.0, 3.0/16.0, 3.0/16.0, -21.0/16.0, &inverted);
    GdipIsMatrixEqual(matrix, inverted, &equal);
    expect(TRUE, equal);
    GdipDeleteMatrix(matrix);

    GdipCreateMatrix2(0.0006, 0, 0, 0.0006, 400, 400, &matrix);
    status = GdipInvertMatrix(matrix);
    expect(Ok, status);
    status = GdipGetMatrixElements(matrix, elems);
    expect(Ok, status);
    ok(compare_float(elems[0], 1666.666504, 1), "elems[0] = %.10g\n", elems[0]);
    ok(compare_float(elems[1], 0, 0), "elems[1] = %.10g\n", elems[1]);
    ok(compare_float(elems[2], 0, 0), "elems[2] = %.10g\n", elems[2]);
    ok(compare_float(elems[3], 1666.666504, 1), "elems[3] = %.10g\n", elems[3]);
    ok(compare_float(elems[4], -666666.6875, 1), "elems[4] = %.10g\n", elems[4]);
    ok(compare_float(elems[5], -666666.6875, 1), "elems[5] = %.10g\n", elems[5]);

    GdipDeleteMatrix(inverted);
    GdipDeleteMatrix(matrix);
}
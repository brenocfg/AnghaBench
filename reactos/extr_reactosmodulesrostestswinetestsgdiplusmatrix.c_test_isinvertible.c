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
 int /*<<< orphan*/  FALSE ; 
 int /*<<< orphan*/  GdipCreateMatrix2 (double,double,double,double,double,double,int /*<<< orphan*/ **) ; 
 int /*<<< orphan*/  GdipDeleteMatrix (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  GdipIsMatrixInvertible (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  InvalidParameter ; 
 int /*<<< orphan*/  Ok ; 
 int /*<<< orphan*/  TRUE ; 
 int /*<<< orphan*/  expect (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void test_isinvertible(void)
{
    GpStatus status;
    GpMatrix *matrix = NULL;
    BOOL result;

    /* NULL arguments */
    status = GdipIsMatrixInvertible(NULL, &result);
    expect(InvalidParameter, status);
    status = GdipIsMatrixInvertible((GpMatrix*)0xdeadbeef, NULL);
    expect(InvalidParameter, status);
    status = GdipIsMatrixInvertible(NULL, NULL);
    expect(InvalidParameter, status);

    /* invertible */
    GdipCreateMatrix2(1.0, 1.2, 2.3, -1.0, 2.0, 3.0, &matrix);
    status = GdipIsMatrixInvertible(matrix, &result);
    expect(Ok, status);
    expect(TRUE, result);
    GdipDeleteMatrix(matrix);

    /* noninvertible */
    GdipCreateMatrix2(2.0, -1.0, 6.0, -3.0, 2.2, 3.0, &matrix);
    status = GdipIsMatrixInvertible(matrix, &result);
    expect(Ok, status);
    expect(FALSE, result);
    GdipDeleteMatrix(matrix);
}
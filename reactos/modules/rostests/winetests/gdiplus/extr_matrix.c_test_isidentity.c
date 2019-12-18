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
typedef  scalar_t__ BOOL ;

/* Variables and functions */
 scalar_t__ FALSE ; 
 int /*<<< orphan*/  GdipCreateMatrix2 (double,double,double,double,double,double,int /*<<< orphan*/ **) ; 
 int /*<<< orphan*/  GdipDeleteMatrix (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  GdipIsMatrixIdentity (int /*<<< orphan*/ *,scalar_t__*) ; 
 int /*<<< orphan*/  GdipSetMatrixElements (int /*<<< orphan*/ *,double,double,double,double,double,double) ; 
 int /*<<< orphan*/  InvalidParameter ; 
 int /*<<< orphan*/  Ok ; 
 scalar_t__ TRUE ; 
 int /*<<< orphan*/  expect (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ok (int,char*,scalar_t__) ; 

__attribute__((used)) static void test_isidentity(void)
{
    GpMatrix *matrix;
    GpStatus stat;
    BOOL result;

    stat = GdipIsMatrixIdentity(NULL, NULL);
    expect(InvalidParameter, stat);

    stat = GdipIsMatrixIdentity(NULL, &result);
    expect(InvalidParameter, stat);

    stat = GdipCreateMatrix2(1.0, 0.0, 0.0, 1.0, 0.0, 0.0, &matrix);
    expect(Ok, stat);

    stat = GdipIsMatrixIdentity(matrix, NULL);
    expect(InvalidParameter, stat);

    result = FALSE;
    stat = GdipIsMatrixIdentity(matrix, &result);
    expect(Ok, stat);
    ok(!!result, "got %d\n", result);

    stat = GdipSetMatrixElements(matrix, 1.0, 0.0, 0.0, 1.0, 0.1, 0.0);
    expect(Ok, stat);

    result = TRUE;
    stat = GdipIsMatrixIdentity(matrix, &result);
    expect(Ok, stat);
    ok(!result, "got %d\n", result);

    GdipDeleteMatrix(matrix);
}
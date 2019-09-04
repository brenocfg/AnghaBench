#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_5__ {scalar_t__ Y; scalar_t__ X; } ;
struct TYPE_4__ {int X; double Y; } ;
typedef  int REAL ;
typedef  int INT ;
typedef  int /*<<< orphan*/  GpStatus ;
typedef  TYPE_1__ GpPointF ;
typedef  int /*<<< orphan*/  GpMatrix ;
typedef  int BOOL ;

/* Variables and functions */
 int /*<<< orphan*/  GdipCreateMatrix2 (double,double,double,double,double,double,int /*<<< orphan*/ **) ; 
 int /*<<< orphan*/  GdipDeleteMatrix (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  GdipTransformMatrixPoints (int /*<<< orphan*/ *,TYPE_1__*,int) ; 
 int /*<<< orphan*/  InvalidParameter ; 
 int /*<<< orphan*/  Ok ; 
 int /*<<< orphan*/  expect (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 double fabs (scalar_t__) ; 
 int /*<<< orphan*/  ok (int,char*,int,scalar_t__,scalar_t__,int,double) ; 
 TYPE_2__* transform_points ; 

__attribute__((used)) static void test_transform(void)
{
    GpStatus status;
    GpMatrix *matrix = NULL;
    GpPointF pts[10];
    INT i;
    BOOL match;

    for(i = 0; i < 10; i ++){
        pts[i].X = i * 5.0 * (REAL)(i % 2);
        pts[i].Y = 50.0 - i * 5.0;
    }

    GdipCreateMatrix2(1.0, -2.0, 30.0, 40.0, -500.0, 600.0, &matrix);

    status = GdipTransformMatrixPoints(matrix, pts, 0);
    expect(InvalidParameter, status);

    status = GdipTransformMatrixPoints(matrix, pts, 10);
    expect(Ok, status);

    for(i = 0; i < 10; i ++){
        match = fabs(transform_points[i].X - pts[i].X) < 2.0
            && fabs(transform_points[i].Y -  pts[i].Y) < 2.0;

        ok(match, "Expected #%d to be (%.2f, %.2f) but got (%.2f, %.2f)\n", i,
           transform_points[i].X, transform_points[i].Y, pts[i].X, pts[i].Y);
    }

    GdipDeleteMatrix(matrix);
}
#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct TYPE_6__ {int X; int Y; } ;
struct TYPE_5__ {int X; int Y; int Width; int Height; } ;
typedef  int /*<<< orphan*/  REAL ;
typedef  int /*<<< orphan*/  GpStatus ;
typedef  TYPE_1__ GpRectF ;
typedef  TYPE_2__ GpPointF ;
typedef  int /*<<< orphan*/  GpMatrix ;

/* Variables and functions */
 int /*<<< orphan*/  GdipCreateMatrix3 (TYPE_1__*,TYPE_2__*,int /*<<< orphan*/ **) ; 
 int /*<<< orphan*/  GdipDeleteMatrix (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  GdipGetMatrixElements (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  Ok ; 
 int /*<<< orphan*/  expect (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  expectf (double,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void test_constructor3(void)
{
    /* MSDN is on crack. GdipCreateMatrix3 makes a matrix that transforms the
     * corners of the given rectangle to the three points given. */
    GpMatrix *matrix;
    REAL values[6];
    GpRectF rc;
    GpPointF pt[3];
    GpStatus stat;

    rc.X = 10;
    rc.Y = 10;
    rc.Width = 10;
    rc.Height = 10;

    pt[0].X = 10;
    pt[0].Y = 10;
    pt[1].X = 20;
    pt[1].Y = 10;
    pt[2].X = 10;
    pt[2].Y = 20;

    stat = GdipCreateMatrix3(&rc, pt, &matrix);
    expect(Ok, stat);

    stat = GdipGetMatrixElements(matrix, values);
    expect(Ok, stat);

    expectf(1.0, values[0]);
    expectf(0.0, values[1]);
    expectf(0.0, values[2]);
    expectf(1.0, values[3]);
    expectf(0.0, values[4]);
    expectf(0.0, values[5]);

    GdipDeleteMatrix(matrix);

    pt[0].X = 20;
    pt[0].Y = 10;
    pt[1].X = 40;
    pt[1].Y = 10;
    pt[2].X = 20;
    pt[2].Y = 20;

    stat = GdipCreateMatrix3(&rc, pt, &matrix);
    expect(Ok, stat);

    stat = GdipGetMatrixElements(matrix, values);
    expect(Ok, stat);

    expectf(2.0, values[0]);
    expectf(0.0, values[1]);
    expectf(0.0, values[2]);
    expectf(1.0, values[3]);
    expectf(0.0, values[4]);
    expectf(0.0, values[5]);

    GdipDeleteMatrix(matrix);

    pt[0].X = 10;
    pt[0].Y = 20;
    pt[1].X = 20;
    pt[1].Y = 30;
    pt[2].X = 10;
    pt[2].Y = 30;

    stat = GdipCreateMatrix3(&rc, pt, &matrix);
    expect(Ok, stat);

    stat = GdipGetMatrixElements(matrix, values);
    expect(Ok, stat);

    expectf(1.0, values[0]);
    expectf(1.0, values[1]);
    expectf(0.0, values[2]);
    expectf(1.0, values[3]);
    expectf(0.0, values[4]);
    expectf(0.0, values[5]);

    GdipDeleteMatrix(matrix);
}
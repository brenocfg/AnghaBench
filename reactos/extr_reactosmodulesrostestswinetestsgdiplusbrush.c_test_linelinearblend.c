#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_4__ {double X; double Y; } ;
typedef  float REAL ;
typedef  int INT ;
typedef  int GpStatus ;
typedef  TYPE_1__ GpPointF ;
typedef  int /*<<< orphan*/  GpLineGradient ;
typedef  int /*<<< orphan*/  GpBrush ;

/* Variables and functions */
 int GdipCreateLineBrush (TYPE_1__*,TYPE_1__*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ **) ; 
 int GdipDeleteBrush (int /*<<< orphan*/ *) ; 
 int GdipGetLineBlend (int /*<<< orphan*/ *,float*,float*,int) ; 
 int GdipGetLineBlendCount (int /*<<< orphan*/ *,int*) ; 
 int GdipSetLineLinearBlend (int /*<<< orphan*/ *,double,double) ; 
 int InvalidParameter ; 
 int Ok ; 
 int /*<<< orphan*/  WrapModeTile ; 
 int /*<<< orphan*/  expect (int,int) ; 
 int /*<<< orphan*/  expectf (double,float) ; 

__attribute__((used)) static void test_linelinearblend(void)
{
    GpLineGradient *brush;
    GpStatus status;
    GpPointF pt1, pt2;
    INT count=10;
    REAL res_factors[3] = {0.3f};
    REAL res_positions[3] = {0.3f};

    status = GdipSetLineLinearBlend(NULL, 0.6, 0.8);
    expect(InvalidParameter, status);

    pt1.X = pt1.Y = 1.0;
    pt2.X = pt2.Y = 100.0;
    status = GdipCreateLineBrush(&pt1, &pt2, 0, 0, WrapModeTile, &brush);
    expect(Ok, status);


    status = GdipSetLineLinearBlend(brush, 0.6, 0.8);
    expect(Ok, status);

    status = GdipGetLineBlendCount(brush, &count);
    expect(Ok, status);
    expect(3, count);

    status = GdipGetLineBlend(brush, res_factors, res_positions, 3);
    expect(Ok, status);
    expectf(0.0, res_factors[0]);
    expectf(0.0, res_positions[0]);
    expectf(0.8, res_factors[1]);
    expectf(0.6, res_positions[1]);
    expectf(0.0, res_factors[2]);
    expectf(1.0, res_positions[2]);


    status = GdipSetLineLinearBlend(brush, 0.0, 0.8);
    expect(Ok, status);

    status = GdipGetLineBlendCount(brush, &count);
    expect(Ok, status);
    expect(2, count);

    status = GdipGetLineBlend(brush, res_factors, res_positions, 3);
    expect(Ok, status);
    expectf(0.8, res_factors[0]);
    expectf(0.0, res_positions[0]);
    expectf(0.0, res_factors[1]);
    expectf(1.0, res_positions[1]);


    status = GdipSetLineLinearBlend(brush, 1.0, 0.8);
    expect(Ok, status);

    status = GdipGetLineBlendCount(brush, &count);
    expect(Ok, status);
    expect(2, count);

    status = GdipGetLineBlend(brush, res_factors, res_positions, 3);
    expect(Ok, status);
    expectf(0.0, res_factors[0]);
    expectf(0.0, res_positions[0]);
    expectf(0.8, res_factors[1]);
    expectf(1.0, res_positions[1]);

    status = GdipDeleteBrush((GpBrush*)brush);
    expect(Ok, status);
}
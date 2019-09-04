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
struct TYPE_3__ {int member_0; int member_1; } ;
typedef  float REAL ;
typedef  int INT ;
typedef  int GpStatus ;
typedef  TYPE_1__ GpPointF ;
typedef  int /*<<< orphan*/  GpPathGradient ;
typedef  int /*<<< orphan*/  GpBrush ;

/* Variables and functions */
 int GdipCreatePathGradient (TYPE_1__ const*,int,int /*<<< orphan*/ ,int /*<<< orphan*/ **) ; 
 int GdipDeleteBrush (int /*<<< orphan*/ *) ; 
 int GdipGetPathGradientBlend (int /*<<< orphan*/ *,float*,float*,int) ; 
 int GdipGetPathGradientBlendCount (int /*<<< orphan*/ *,int*) ; 
 int GdipSetPathGradientBlend (int /*<<< orphan*/ *,float const*,float const*,int) ; 
 int InsufficientBuffer ; 
 int InvalidParameter ; 
 int Ok ; 
 int /*<<< orphan*/  WrapModeClamp ; 
 int /*<<< orphan*/  expect (int,int) ; 
 int /*<<< orphan*/  expectf (float const,float) ; 

__attribute__((used)) static void test_pathgradientblend(void)
{
    static const GpPointF path_points[] = {{0,0}, {3,0}, {0,4}};
    GpPathGradient *brush;
    GpStatus status;
    INT count, i;
    const REAL factors[5] = {0.0f, 0.1f, 0.5f, 0.9f, 1.0f};
    const REAL positions[5] = {0.0f, 0.2f, 0.5f, 0.8f, 1.0f};
    REAL res_factors[6] = {0.3f, 0.0f, 0.0f, 0.0f, 0.0f};
    REAL res_positions[6] = {0.3f, 0.0f, 0.0f, 0.0f, 0.0f};

    status = GdipCreatePathGradient(path_points, 3, WrapModeClamp, &brush);
    expect(Ok, status);

    status = GdipGetPathGradientBlendCount(NULL, &count);
    expect(InvalidParameter, status);

    status = GdipGetPathGradientBlendCount(brush, NULL);
    expect(InvalidParameter, status);

    status = GdipGetPathGradientBlendCount(brush, &count);
    expect(Ok, status);
    expect(1, count);

    status = GdipGetPathGradientBlend(NULL, res_factors, res_positions, 1);
    expect(InvalidParameter, status);

    status = GdipGetPathGradientBlend(brush, NULL, res_positions, 1);
    expect(InvalidParameter, status);

    status = GdipGetPathGradientBlend(brush, res_factors, NULL, 1);
    expect(InvalidParameter, status);

    status = GdipGetPathGradientBlend(brush, res_factors, res_positions, 0);
    expect(InvalidParameter, status);

    status = GdipGetPathGradientBlend(brush, res_factors, res_positions, -1);
    expect(InvalidParameter, status);

    status = GdipGetPathGradientBlend(brush, res_factors, res_positions, 1);
    expect(Ok, status);

    status = GdipGetPathGradientBlend(brush, res_factors, res_positions, 2);
    expect(Ok, status);

    status = GdipSetPathGradientBlend(NULL, factors, positions, 5);
    expect(InvalidParameter, status);

    status = GdipSetPathGradientBlend(brush, NULL, positions, 5);
    expect(InvalidParameter, status);

    status = GdipSetPathGradientBlend(brush, factors, NULL, 5);
    expect(InvalidParameter, status);

    status = GdipSetPathGradientBlend(brush, factors, positions, 0);
    expect(InvalidParameter, status);

    status = GdipSetPathGradientBlend(brush, factors, positions, -1);
    expect(InvalidParameter, status);

    /* leave off the 0.0 position */
    status = GdipSetPathGradientBlend(brush, &factors[1], &positions[1], 4);
    expect(InvalidParameter, status);

    /* leave off the 1.0 position */
    status = GdipSetPathGradientBlend(brush, factors, positions, 4);
    expect(InvalidParameter, status);

    status = GdipSetPathGradientBlend(brush, factors, positions, 5);
    expect(Ok, status);

    status = GdipGetPathGradientBlendCount(brush, &count);
    expect(Ok, status);
    expect(5, count);

    status = GdipGetPathGradientBlend(brush, res_factors, res_positions, 4);
    expect(InsufficientBuffer, status);

    status = GdipGetPathGradientBlend(brush, res_factors, res_positions, 5);
    expect(Ok, status);

    for (i=0; i<5; i++)
    {
        expectf(factors[i], res_factors[i]);
        expectf(positions[i], res_positions[i]);
    }

    status = GdipGetPathGradientBlend(brush, res_factors, res_positions, 6);
    expect(Ok, status);

    status = GdipSetPathGradientBlend(brush, factors, positions, 1);
    expect(Ok, status);

    status = GdipGetPathGradientBlendCount(brush, &count);
    expect(Ok, status);
    expect(1, count);

    status = GdipGetPathGradientBlend(brush, res_factors, res_positions, 1);
    expect(Ok, status);

    status = GdipDeleteBrush((GpBrush*)brush);
    expect(Ok, status);
}
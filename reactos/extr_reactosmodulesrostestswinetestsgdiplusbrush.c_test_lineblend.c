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
typedef  int ARGB ;

/* Variables and functions */
 int GdipCreateLineBrush (TYPE_1__*,TYPE_1__*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ **) ; 
 int GdipDeleteBrush (int /*<<< orphan*/ *) ; 
 int GdipGetLineBlend (int /*<<< orphan*/ *,float*,float*,int) ; 
 int GdipGetLineBlendCount (int /*<<< orphan*/ *,int*) ; 
 int GdipGetLinePresetBlend (int /*<<< orphan*/ *,int*,float*,int) ; 
 int GdipGetLinePresetBlendCount (int /*<<< orphan*/ *,int*) ; 
 int GdipSetLineBlend (int /*<<< orphan*/ *,float const*,float const*,int) ; 
 int GdipSetLinePresetBlend (int /*<<< orphan*/ *,int const*,float const*,int) ; 
 int const GenericError ; 
 int const InsufficientBuffer ; 
 int const InvalidParameter ; 
 int const Ok ; 
 int const OutOfMemory ; 
 int /*<<< orphan*/  WrapModeTile ; 
 int /*<<< orphan*/  expect (int const,int) ; 
 int /*<<< orphan*/  expectf (float const,float) ; 

__attribute__((used)) static void test_lineblend(void)
{
    GpLineGradient *brush;
    GpStatus status;
    GpPointF pt1, pt2;
    INT count=10;
    int i;
    const REAL factors[5] = {0.0f, 0.1f, 0.5f, 0.9f, 1.0f};
    const REAL positions[5] = {0.0f, 0.2f, 0.5f, 0.8f, 1.0f};
    const REAL two_positions[2] = {0.0f, 1.0f};
    const ARGB colors[5] = {0xff0000ff, 0xff00ff00, 0xff00ffff, 0xffff0000, 0xffffffff};
    REAL res_factors[6] = {0.3f, 0.0f, 0.0f, 0.0f, 0.0f};
    REAL res_positions[6] = {0.3f, 0.0f, 0.0f, 0.0f, 0.0f};
    ARGB res_colors[6] = {0xdeadbeef, 0, 0, 0, 0};

    pt1.X = pt1.Y = pt2.Y = pt2.X = 1.0;
    status = GdipCreateLineBrush(&pt1, &pt2, 0, 0, WrapModeTile, &brush);
    expect(OutOfMemory, status);

    pt1.X = pt1.Y = 1.0;
    pt2.X = pt2.Y = 100.0;
    status = GdipCreateLineBrush(&pt1, &pt2, 0, 0, WrapModeTile, &brush);
    expect(Ok, status);

    status = GdipGetLineBlendCount(NULL, &count);
    expect(InvalidParameter, status);

    status = GdipGetLineBlendCount(brush, NULL);
    expect(InvalidParameter, status);

    status = GdipGetLineBlendCount(brush, &count);
    expect(Ok, status);
    expect(1, count);

    status = GdipGetLineBlend(NULL, res_factors, res_positions, 1);
    expect(InvalidParameter, status);

    status = GdipGetLineBlend(brush, NULL, res_positions, 1);
    expect(InvalidParameter, status);

    status = GdipGetLineBlend(brush, res_factors, NULL, 1);
    expect(InvalidParameter, status);

    status = GdipGetLineBlend(brush, res_factors, res_positions, 0);
    expect(InvalidParameter, status);

    status = GdipGetLineBlend(brush, res_factors, res_positions, -1);
    expect(InvalidParameter, status);

    status = GdipGetLineBlend(brush, res_factors, res_positions, 1);
    expect(Ok, status);

    status = GdipGetLineBlend(brush, res_factors, res_positions, 2);
    expect(Ok, status);

    status = GdipSetLineBlend(NULL, factors, positions, 5);
    expect(InvalidParameter, status);

    status = GdipSetLineBlend(brush, NULL, positions, 5);
    expect(InvalidParameter, status);

    status = GdipSetLineBlend(brush, factors, NULL, 5);
    expect(InvalidParameter, status);

    status = GdipSetLineBlend(brush, factors, positions, 0);
    expect(InvalidParameter, status);

    status = GdipSetLineBlend(brush, factors, positions, -1);
    expect(InvalidParameter, status);

    /* leave off the 0.0 position */
    status = GdipSetLineBlend(brush, &factors[1], &positions[1], 4);
    expect(InvalidParameter, status);

    /* leave off the 1.0 position */
    status = GdipSetLineBlend(brush, factors, positions, 4);
    expect(InvalidParameter, status);

    status = GdipSetLineBlend(brush, factors, positions, 5);
    expect(Ok, status);

    status = GdipGetLineBlendCount(brush, &count);
    expect(Ok, status);
    expect(5, count);

    status = GdipGetLineBlend(brush, res_factors, res_positions, 4);
    expect(InsufficientBuffer, status);

    status = GdipGetLineBlend(brush, res_factors, res_positions, 5);
    expect(Ok, status);

    for (i=0; i<5; i++)
    {
        expectf(factors[i], res_factors[i]);
        expectf(positions[i], res_positions[i]);
    }

    status = GdipGetLineBlend(brush, res_factors, res_positions, 6);
    expect(Ok, status);

    status = GdipSetLineBlend(brush, factors, positions, 1);
    expect(Ok, status);

    status = GdipGetLineBlendCount(brush, &count);
    expect(Ok, status);
    expect(1, count);

    status = GdipGetLineBlend(brush, res_factors, res_positions, 1);
    expect(Ok, status);

    status = GdipGetLinePresetBlendCount(NULL, &count);
    expect(InvalidParameter, status);

    status = GdipGetLinePresetBlendCount(brush, NULL);
    expect(InvalidParameter, status);

    status = GdipGetLinePresetBlendCount(brush, &count);
    expect(Ok, status);
    expect(0, count);

    status = GdipGetLinePresetBlend(NULL, res_colors, res_positions, 1);
    expect(InvalidParameter, status);

    status = GdipGetLinePresetBlend(brush, NULL, res_positions, 1);
    expect(InvalidParameter, status);

    status = GdipGetLinePresetBlend(brush, res_colors, NULL, 1);
    expect(InvalidParameter, status);

    status = GdipGetLinePresetBlend(brush, res_colors, res_positions, 0);
    expect(InvalidParameter, status);

    status = GdipGetLinePresetBlend(brush, res_colors, res_positions, -1);
    expect(InvalidParameter, status);

    status = GdipGetLinePresetBlend(brush, res_colors, res_positions, 1);
    expect(InvalidParameter, status);

    status = GdipGetLinePresetBlend(brush, res_colors, res_positions, 2);
    expect(GenericError, status);

    status = GdipSetLinePresetBlend(NULL, colors, positions, 5);
    expect(InvalidParameter, status);

    status = GdipSetLinePresetBlend(brush, NULL, positions, 5);
    expect(InvalidParameter, status);

    status = GdipSetLinePresetBlend(brush, colors, NULL, 5);
    expect(InvalidParameter, status);

    status = GdipSetLinePresetBlend(brush, colors, positions, 0);
    expect(InvalidParameter, status);

    status = GdipSetLinePresetBlend(brush, colors, positions, -1);
    expect(InvalidParameter, status);

    status = GdipSetLinePresetBlend(brush, colors, positions, 1);
    expect(InvalidParameter, status);

    /* leave off the 0.0 position */
    status = GdipSetLinePresetBlend(brush, &colors[1], &positions[1], 4);
    expect(InvalidParameter, status);

    /* leave off the 1.0 position */
    status = GdipSetLinePresetBlend(brush, colors, positions, 4);
    expect(InvalidParameter, status);

    status = GdipSetLinePresetBlend(brush, colors, positions, 5);
    expect(Ok, status);

    status = GdipGetLinePresetBlendCount(brush, &count);
    expect(Ok, status);
    expect(5, count);

    status = GdipGetLinePresetBlend(brush, res_colors, res_positions, 4);
    expect(InsufficientBuffer, status);

    status = GdipGetLinePresetBlend(brush, res_colors, res_positions, 5);
    expect(Ok, status);

    for (i=0; i<5; i++)
    {
        expect(colors[i], res_colors[i]);
        expectf(positions[i], res_positions[i]);
    }

    status = GdipGetLinePresetBlend(brush, res_colors, res_positions, 6);
    expect(Ok, status);

    status = GdipSetLinePresetBlend(brush, colors, two_positions, 2);
    expect(Ok, status);

    status = GdipDeleteBrush((GpBrush*)brush);
    expect(Ok, status);
}
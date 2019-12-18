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
struct TYPE_3__ {int X; double Y; } ;
typedef  int REAL ;
typedef  int /*<<< orphan*/  GpStatus ;
typedef  TYPE_1__ GpPointF ;
typedef  int /*<<< orphan*/  GpPath ;

/* Variables and functions */
 int /*<<< orphan*/  ARRAY_SIZE (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  FALSE ; 
 int /*<<< orphan*/  FillModeAlternate ; 
 int /*<<< orphan*/  GdipAddPathLine2 (int /*<<< orphan*/ *,TYPE_1__*,int) ; 
 int /*<<< orphan*/  GdipClosePathFigure (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  GdipCreatePath (int /*<<< orphan*/ ,int /*<<< orphan*/ **) ; 
 int /*<<< orphan*/  GdipDeletePath (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  Ok ; 
 int /*<<< orphan*/  expect (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  line2_path ; 
 int /*<<< orphan*/  ok_path (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void test_line2(void)
{
    GpStatus status;
    GpPath* path;
    int i;
    GpPointF line2_points[9];

    for(i = 0; i < 9; i ++){
        line2_points[i].X = i * 5.0 * (REAL)(i % 2);
        line2_points[i].Y = 50.0 - i * 5.0;
    }

    GdipCreatePath(FillModeAlternate, &path);
    status = GdipAddPathLine2(path, line2_points, 3);
    expect(Ok, status);
    status = GdipAddPathLine2(path, &(line2_points[3]), 3);
    expect(Ok, status);
    status = GdipClosePathFigure(path);
    expect(Ok, status);
    status = GdipAddPathLine2(path, &(line2_points[6]), 3);
    expect(Ok, status);

    ok_path(path, line2_path, ARRAY_SIZE(line2_path), FALSE);

    GdipDeletePath(path);
}
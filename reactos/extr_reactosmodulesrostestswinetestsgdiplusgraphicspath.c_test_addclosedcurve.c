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
struct TYPE_3__ {double X; double Y; } ;
typedef  int /*<<< orphan*/  GpStatus ;
typedef  TYPE_1__ GpPointF ;
typedef  int /*<<< orphan*/  GpPath ;

/* Variables and functions */
 int /*<<< orphan*/  ARRAY_SIZE (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  FALSE ; 
 int /*<<< orphan*/  FillModeAlternate ; 
 int /*<<< orphan*/  GdipAddPathClosedCurve2 (int /*<<< orphan*/ *,TYPE_1__*,int,double) ; 
 int /*<<< orphan*/  GdipCreatePath (int /*<<< orphan*/ ,int /*<<< orphan*/ **) ; 
 int /*<<< orphan*/  GdipDeletePath (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  InvalidParameter ; 
 int /*<<< orphan*/  Ok ; 
 int /*<<< orphan*/  addclosedcurve_path ; 
 int /*<<< orphan*/  expect (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ok_path (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void test_addclosedcurve(void)
{
    GpStatus status;
    GpPath *path;
    GpPointF points[4];

    points[0].X = 0.0;
    points[0].Y = 0.0;
    points[1].X = 10.0;
    points[1].Y = 10.0;
    points[2].X = 10.0;
    points[2].Y = 20.0;
    points[3].X = 30.0;
    points[3].Y = 10.0;

    GdipCreatePath(FillModeAlternate, &path);

    /* NULL args */
    status = GdipAddPathClosedCurve2(NULL, NULL, 0, 0.0);
    expect(InvalidParameter, status);
    status = GdipAddPathClosedCurve2(path, NULL, 0, 0.0);
    expect(InvalidParameter, status);
    status = GdipAddPathClosedCurve2(path, points, -1, 0.0);
    expect(InvalidParameter, status);
    status = GdipAddPathClosedCurve2(path, points, 1, 1.0);
    expect(InvalidParameter, status);

    /* add to empty path */
    status = GdipAddPathClosedCurve2(path, points, 4, 1.0);
    expect(Ok, status);
    ok_path(path, addclosedcurve_path, ARRAY_SIZE(addclosedcurve_path), FALSE);
    GdipDeletePath(path);
}
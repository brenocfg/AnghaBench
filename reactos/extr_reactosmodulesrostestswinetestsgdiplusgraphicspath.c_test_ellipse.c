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
 int /*<<< orphan*/  GdipAddPathEllipse (int /*<<< orphan*/ *,double,double,double,double) ; 
 int /*<<< orphan*/  GdipAddPathLine2 (int /*<<< orphan*/ *,TYPE_1__*,int) ; 
 int /*<<< orphan*/  GdipClosePathFigure (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  GdipCreatePath (int /*<<< orphan*/ ,int /*<<< orphan*/ **) ; 
 int /*<<< orphan*/  GdipDeletePath (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  Ok ; 
 int /*<<< orphan*/  ellipse_path ; 
 int /*<<< orphan*/  expect (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ok_path (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void test_ellipse(void)
{
    GpStatus status;
    GpPath *path;
    GpPointF points[2];

    points[0].X = 7.0;
    points[0].Y = 11.0;
    points[1].X = 13.0;
    points[1].Y = 17.0;

    GdipCreatePath(FillModeAlternate, &path);
    status = GdipAddPathEllipse(path, 10.0, 100.0, 20.0, 50.5);
    expect(Ok, status);
    GdipAddPathLine2(path, points, 2);
    status = GdipAddPathEllipse(path, 10.0, 200.0, -5.0, -10.0);
    expect(Ok, status);
    GdipClosePathFigure(path);
    status = GdipAddPathEllipse(path, 10.0, 300.0, 0.0, 1.0);
    expect(Ok, status);

    ok_path(path, ellipse_path, ARRAY_SIZE(ellipse_path), FALSE);

    GdipDeletePath(path);
}
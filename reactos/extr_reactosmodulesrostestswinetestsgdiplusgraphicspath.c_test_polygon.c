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
 int /*<<< orphan*/  GdipAddPathLine (int /*<<< orphan*/ *,double,double,double,double) ; 
 int /*<<< orphan*/  GdipAddPathPolygon (int /*<<< orphan*/ *,TYPE_1__*,int) ; 
 int /*<<< orphan*/  GdipCreatePath (int /*<<< orphan*/ ,int /*<<< orphan*/ **) ; 
 int /*<<< orphan*/  GdipDeletePath (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  InvalidParameter ; 
 int /*<<< orphan*/  Ok ; 
 int /*<<< orphan*/  expect (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ok_path (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  poly_path ; 

__attribute__((used)) static void test_polygon(void)
{
    GpStatus status;
    GpPath *path;
    GpPointF points[5];

    points[0].X = 0.0;
    points[0].Y = 0.0;
    points[1].X = 10.0;
    points[1].Y = 10.0;
    points[2].X = 10.0;
    points[2].Y = 20.0;
    points[3].X = 30.0;
    points[3].Y = 10.0;
    points[4].X = 20.0;
    points[4].Y = 0.0;

    GdipCreatePath(FillModeAlternate, &path);

    /* NULL args */
    status = GdipAddPathPolygon(NULL, points, 5);
    expect(InvalidParameter, status);
    status = GdipAddPathPolygon(path, NULL, 5);
    expect(InvalidParameter, status);
    /* Polygon should have 3 points at least */
    status = GdipAddPathPolygon(path, points, 2);
    expect(InvalidParameter, status);

    /* to test how it prolongs not empty path */
    status = GdipAddPathLine(path, 5.0, 5.0, 6.0, 8.0);
    expect(Ok, status);
    status = GdipAddPathPolygon(path, points, 5);
    expect(Ok, status);
    /* check resulting path */
    ok_path(path, poly_path, ARRAY_SIZE(poly_path), FALSE);

    GdipDeletePath(path);
}
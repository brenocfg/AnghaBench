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
typedef  int GpStatus ;
typedef  TYPE_1__ GpPointF ;
typedef  int /*<<< orphan*/  GpPath ;

/* Variables and functions */
 int /*<<< orphan*/  FillModeAlternate ; 
 int GdipAddPathRectangle (int /*<<< orphan*/ *,double,double,double,double) ; 
 int /*<<< orphan*/  GdipCreatePath (int /*<<< orphan*/ ,int /*<<< orphan*/ **) ; 
 int /*<<< orphan*/  GdipDeletePath (int /*<<< orphan*/ *) ; 
 int GdipGetPathLastPoint (int /*<<< orphan*/ *,TYPE_1__*) ; 
 int /*<<< orphan*/  InvalidParameter ; 
 int /*<<< orphan*/  Ok ; 
 int /*<<< orphan*/  TRUE ; 
 int /*<<< orphan*/  expect (int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static void test_lastpoint(void)
{
    GpStatus status;
    GpPath *path;
    GpPointF ptf;

    GdipCreatePath(FillModeAlternate, &path);
    status = GdipAddPathRectangle(path, 5.0, 5.0, 100.0, 50.0);
    expect(Ok, status);

    /* invalid args */
    status = GdipGetPathLastPoint(NULL, &ptf);
    expect(InvalidParameter, status);
    status = GdipGetPathLastPoint(path, NULL);
    expect(InvalidParameter, status);
    status = GdipGetPathLastPoint(NULL, NULL);
    expect(InvalidParameter, status);

    status = GdipGetPathLastPoint(path, &ptf);
    expect(Ok, status);
    expect(TRUE, (ptf.X == 5.0) && (ptf.Y == 55.0));

    GdipDeletePath(path);
}
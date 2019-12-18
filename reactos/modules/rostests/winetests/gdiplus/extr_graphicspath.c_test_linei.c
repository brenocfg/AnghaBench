#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */

/* Type definitions */
typedef  int /*<<< orphan*/  GpStatus ;
typedef  int /*<<< orphan*/  GpPath ;

/* Variables and functions */
 int /*<<< orphan*/  ARRAY_SIZE (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  FALSE ; 
 int /*<<< orphan*/  FillModeAlternate ; 
 int /*<<< orphan*/  GdipAddPathArc (int /*<<< orphan*/ *,double,double,double,double,double,double) ; 
 int /*<<< orphan*/  GdipAddPathLineI (int /*<<< orphan*/ *,double,double,double,double) ; 
 int /*<<< orphan*/  GdipClosePathFigure (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  GdipCreatePath (int /*<<< orphan*/ ,int /*<<< orphan*/ **) ; 
 int /*<<< orphan*/  GdipDeletePath (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  Ok ; 
 int /*<<< orphan*/  expect (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  linei_path ; 
 int /*<<< orphan*/  ok_path (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void test_linei(void)
{
    GpStatus status;
    GpPath *path;

    GdipCreatePath(FillModeAlternate, &path);
    status = GdipAddPathLineI(path, 5.0, 5.0, 6.0, 8.0);
    expect(Ok, status);
    GdipAddPathArc(path, 100.0, 100.0, 500.0, 700.0, -80.0, 100.0);
    status = GdipAddPathLineI(path, 15.0, 15.0, 26.0, 28.0);
    expect(Ok, status);
    GdipClosePathFigure(path);
    status = GdipAddPathLineI(path, 35.0, 35.0, 36.0, 38.0);
    expect(Ok, status);

    ok_path(path, linei_path, ARRAY_SIZE(linei_path), FALSE);

    GdipDeletePath(path);
}
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
 int /*<<< orphan*/  GdipAddPathPath (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  GdipCreatePath (int /*<<< orphan*/ ,int /*<<< orphan*/ **) ; 
 int /*<<< orphan*/  GdipDeletePath (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  Ok ; 
 int /*<<< orphan*/  TRUE ; 
 int /*<<< orphan*/  expect (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ok_path (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pathpath_path ; 

__attribute__((used)) static void test_pathpath(void)
{
    GpStatus status;
    GpPath* path1, *path2;

    GdipCreatePath(FillModeAlternate, &path2);
    GdipAddPathArc(path2, 100.0, 100.0, 500.0, 700.0, 95.0, 100.0);

    GdipCreatePath(FillModeAlternate, &path1);
    GdipAddPathArc(path1, 100.0, 100.0, 500.0, 700.0, 0.0, 90.0);
    status = GdipAddPathPath(path1, path2, FALSE);
    expect(Ok, status);
    GdipAddPathArc(path1, 100.0, 100.0, 500.0, 700.0, -80.0, 100.0);
    status = GdipAddPathPath(path1, path2, TRUE);
    expect(Ok, status);

    ok_path(path1, pathpath_path, ARRAY_SIZE(pathpath_path), FALSE);

    GdipDeletePath(path1);
    GdipDeletePath(path2);
}
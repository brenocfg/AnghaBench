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
 int /*<<< orphan*/  GdipCreatePath (int /*<<< orphan*/ ,int /*<<< orphan*/ **) ; 
 int /*<<< orphan*/  GdipDeletePath (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  Ok ; 
 int /*<<< orphan*/  arc_path ; 
 int /*<<< orphan*/  expect (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ok_path (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void test_arc(void)
{
    GpStatus status;
    GpPath* path;

    GdipCreatePath(FillModeAlternate, &path);
    /* Exactly 90 degrees */
    status = GdipAddPathArc(path, 100.0, 100.0, 500.0, 700.0, 0.0, 90.0);
    expect(Ok, status);
    /* Over 90 degrees */
    status = GdipAddPathArc(path, 100.0, 100.0, 500.0, 700.0, 0.0, 100.0);
    expect(Ok, status);
    /* Negative start angle */
    status = GdipAddPathArc(path, 100.0, 100.0, 500.0, 700.0, -80.0, 100.0);
    expect(Ok, status);
    /* Negative sweep angle */
    status = GdipAddPathArc(path, 100.0, 100.0, 500.0, 700.0, 80.0, -100.0);
    expect(Ok, status);
    /* More than a full revolution */
    status = GdipAddPathArc(path, 100.0, 100.0, 500.0, 700.0, 50.0, -400.0);
    expect(Ok, status);
    /* 0 sweep angle */
    status = GdipAddPathArc(path, 100.0, 100.0, 500.0, 700.0, 50.0, 0.0);
    expect(Ok, status);

    ok_path(path, arc_path, ARRAY_SIZE(arc_path), FALSE);

    GdipDeletePath(path);
}
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
typedef  int /*<<< orphan*/  GpMatrix ;

/* Variables and functions */
 int /*<<< orphan*/  ARRAY_SIZE (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  FALSE ; 
 int /*<<< orphan*/  FillModeAlternate ; 
 int /*<<< orphan*/  GdipAddPathArc (int /*<<< orphan*/ *,double,double,double,double,double,double) ; 
 int /*<<< orphan*/  GdipAddPathEllipse (int /*<<< orphan*/ *,double,double,double,double) ; 
 int /*<<< orphan*/  GdipAddPathLine (int /*<<< orphan*/ *,double,double,double,double) ; 
 int /*<<< orphan*/  GdipCreateMatrix (int /*<<< orphan*/ **) ; 
 int /*<<< orphan*/  GdipCreatePath (int /*<<< orphan*/ ,int /*<<< orphan*/ **) ; 
 int /*<<< orphan*/  GdipDeleteMatrix (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  GdipDeletePath (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  GdipFlattenPath (int /*<<< orphan*/ *,int /*<<< orphan*/ *,double) ; 
 int /*<<< orphan*/  GdipResetPath (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  GdipTransformPath (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  InvalidParameter ; 
 int /*<<< orphan*/  Ok ; 
 int /*<<< orphan*/  TRUE ; 
 int /*<<< orphan*/  expect (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  flattenarc_path ; 
 int /*<<< orphan*/  flattenellipse_path ; 
 int /*<<< orphan*/  flattenline_path ; 
 int /*<<< orphan*/  flattenquater_path ; 
 int /*<<< orphan*/  ok_path (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void test_flatten(void)
{
    GpStatus status;
    GpPath *path;
    GpMatrix *m;

    status = GdipCreatePath(FillModeAlternate, &path);
    expect(Ok, status);
    status = GdipCreateMatrix(&m);
    expect(Ok, status);

    /* NULL arguments */
    status = GdipFlattenPath(NULL, NULL, 0.0);
    expect(InvalidParameter, status);
    status = GdipFlattenPath(NULL, m, 0.0);
    expect(InvalidParameter, status);

    /* flatten empty path */
    status = GdipFlattenPath(path, NULL, 1.0);
    expect(Ok, status);

    status = GdipTransformPath(path, 0);
    expect(Ok, status);

    status = GdipAddPathEllipse(path, 0.0, 0.0, 100.0, 50.0);
    expect(Ok, status);

    status = GdipFlattenPath(path, NULL, 1.0);
    expect(Ok, status);
    ok_path(path, flattenellipse_path, ARRAY_SIZE(flattenellipse_path), TRUE);

    status = GdipResetPath(path);
    expect(Ok, status);
    status = GdipAddPathLine(path, 5.0, 10.0, 50.0, 100.0);
    expect(Ok, status);
    status = GdipFlattenPath(path, NULL, 1.0);
    expect(Ok, status);
    ok_path(path, flattenline_path, ARRAY_SIZE(flattenline_path), FALSE);

    status = GdipResetPath(path);
    expect(Ok, status);
    status = GdipAddPathArc(path, 0.0, 0.0, 100.0, 50.0, 0.0, 90.0);
    expect(Ok, status);
    status = GdipFlattenPath(path, NULL, 1.0);
    expect(Ok, status);
    ok_path(path, flattenarc_path, ARRAY_SIZE(flattenarc_path), TRUE);

    /* easy case - quater of a full circle */
    status = GdipResetPath(path);
    expect(Ok, status);
    status = GdipAddPathArc(path, 0.0, 0.0, 100.0, 100.0, 0.0, 90.0);
    expect(Ok, status);
    status = GdipFlattenPath(path, NULL, 1.0);
    expect(Ok, status);
    ok_path(path, flattenquater_path, ARRAY_SIZE(flattenquater_path), FALSE);

    GdipDeleteMatrix(m);
    GdipDeletePath(path);
}
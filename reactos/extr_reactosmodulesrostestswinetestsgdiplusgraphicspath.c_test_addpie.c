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
 int /*<<< orphan*/  GdipAddPathPie (int /*<<< orphan*/ *,double,double,double,double,double,double) ; 
 int /*<<< orphan*/  GdipCreatePath (int /*<<< orphan*/ ,int /*<<< orphan*/ **) ; 
 int /*<<< orphan*/  GdipDeletePath (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  GdipResetPath (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  InvalidParameter ; 
 int /*<<< orphan*/  Ok ; 
 int /*<<< orphan*/  addpie_path ; 
 int /*<<< orphan*/  addpie_path2 ; 
 int /*<<< orphan*/  addpie_path3 ; 
 int /*<<< orphan*/  expect (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ok_path (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void test_addpie(void)
{
    GpStatus status;
    GpPath *path;

    GdipCreatePath(FillModeAlternate, &path);

    /* NULL argument */
    status = GdipAddPathPie(NULL, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0);
    expect(InvalidParameter, status);

    status = GdipAddPathPie(path, 0.0, 0.0, 100.0, 50.0, 10.0, 50.0);
    expect(Ok, status);
    ok_path(path, addpie_path, ARRAY_SIZE(addpie_path), FALSE);
    status = GdipResetPath(path);
    expect(Ok, status);

    /* zero width base ellipse */
    status = GdipAddPathPie(path, 0.0, 0.0, 0.0, 60.0, -90.0, 24.0);
    expect(InvalidParameter, status);
    ok_path(path, addpie_path2, ARRAY_SIZE(addpie_path2), FALSE);
    status = GdipResetPath(path);
    expect(Ok, status);

    /* zero height base ellipse */
    status = GdipAddPathPie(path, 0.0, 0.0, 60.0, 0.0 , -90.0, 24.0);
    expect(InvalidParameter, status);
    ok_path(path, addpie_path3, ARRAY_SIZE(addpie_path3), FALSE);

    GdipDeletePath(path);
}
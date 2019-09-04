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
typedef  int /*<<< orphan*/  GpPathIterator ;
typedef  int /*<<< orphan*/  GpPath ;

/* Variables and functions */
 int /*<<< orphan*/  FillModeAlternate ; 
 int /*<<< orphan*/  GdipAddPathRectangle (int /*<<< orphan*/ *,double,double,double,double) ; 
 int /*<<< orphan*/  GdipCreatePath (int /*<<< orphan*/ ,int /*<<< orphan*/ **) ; 
 int /*<<< orphan*/  GdipCreatePathIter (int /*<<< orphan*/ **,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  GdipDeletePath (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  GdipDeletePathIter (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  InvalidParameter ; 
 int /*<<< orphan*/  Ok ; 
 int /*<<< orphan*/  expect (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ok (int /*<<< orphan*/ ,char*) ; 

__attribute__((used)) static void test_constructor_destructor(void)
{
    GpPath *path;
    GpPathIterator *iter;
    GpStatus stat;

    GdipCreatePath(FillModeAlternate, &path);
    GdipAddPathRectangle(path, 5.0, 5.0, 100.0, 50.0);

    /* NULL args */
    stat = GdipCreatePathIter(NULL, NULL);
    expect(InvalidParameter, stat);
    iter = NULL;
    stat = GdipCreatePathIter(&iter, NULL);
    expect(Ok, stat);
    ok(iter != NULL, "Expected iterator to be created\n");
    GdipDeletePathIter(iter);
    stat = GdipCreatePathIter(NULL, path);
    expect(InvalidParameter, stat);
    stat = GdipDeletePathIter(NULL);
    expect(InvalidParameter, stat);

    /* valid args */
    stat = GdipCreatePathIter(&iter, path);
    expect(Ok, stat);

    GdipDeletePathIter(iter);
    GdipDeletePath(path);
}
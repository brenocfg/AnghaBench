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
typedef  int INT ;
typedef  int GpStatus ;
typedef  int /*<<< orphan*/  GpPathIterator ;
typedef  int /*<<< orphan*/  GpPath ;
typedef  int BOOL ;

/* Variables and functions */
 int /*<<< orphan*/  FillModeAlternate ; 
 int /*<<< orphan*/  GdipCreatePath (int /*<<< orphan*/ ,int /*<<< orphan*/ **) ; 
 int /*<<< orphan*/  GdipCreatePathIter (int /*<<< orphan*/ **,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  GdipDeletePath (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  GdipDeletePathIter (int /*<<< orphan*/ *) ; 
 int GdipPathIterNextSubpath (int /*<<< orphan*/ *,int*,int*,int*,int*) ; 
 int Ok ; 
 int TRUE ; 
 int /*<<< orphan*/  expect (int,int) ; 

__attribute__((used)) static void test_nextsubpath(void)
{
    GpPath *path;
    GpPathIterator *iter;
    GpStatus stat;
    INT start, end, result;
    BOOL closed;

    /* empty path */
    GdipCreatePath(FillModeAlternate, &path);
    GdipCreatePathIter(&iter, path);

    result = -2;
    closed = TRUE;
    stat = GdipPathIterNextSubpath(iter, &result, &start, &end, &closed);
    expect(Ok, stat);
    expect(0, result);
    expect(TRUE, closed);

    GdipDeletePathIter(iter);
    GdipDeletePath(path);
}
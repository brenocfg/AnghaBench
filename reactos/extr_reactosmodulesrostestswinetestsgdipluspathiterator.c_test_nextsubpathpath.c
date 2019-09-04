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
 int FALSE ; 
 int /*<<< orphan*/  FillModeAlternate ; 
 int /*<<< orphan*/  GdipAddPathLine (int /*<<< orphan*/ *,double,double,double,double) ; 
 int /*<<< orphan*/  GdipClosePathFigure (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  GdipCreatePath (int /*<<< orphan*/ ,int /*<<< orphan*/ **) ; 
 int /*<<< orphan*/  GdipCreatePathIter (int /*<<< orphan*/ **,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  GdipDeletePath (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  GdipDeletePathIter (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  GdipGetPointCount (int /*<<< orphan*/ *,int*) ; 
 int GdipPathIterNextSubpathPath (int /*<<< orphan*/ *,int*,int /*<<< orphan*/ *,int*) ; 
 int InvalidParameter ; 
 int Ok ; 
 int TRUE ; 
 int /*<<< orphan*/  expect (int,int) ; 

__attribute__((used)) static void test_nextsubpathpath(void)
{
    GpPath *path, *retpath;
    GpPathIterator *iter;
    GpStatus stat;
    BOOL closed;
    INT count, result;

    GdipCreatePath(FillModeAlternate, &path);

    /* NULL args */
    GdipCreatePath(FillModeAlternate, &retpath);
    GdipCreatePathIter(&iter, path);
    stat = GdipPathIterNextSubpathPath(NULL, NULL, NULL, NULL);
    expect(InvalidParameter, stat);
    stat = GdipPathIterNextSubpathPath(iter, NULL, NULL, NULL);
    expect(InvalidParameter, stat);
    stat = GdipPathIterNextSubpathPath(NULL, &result, NULL, NULL);
    expect(InvalidParameter, stat);
    stat = GdipPathIterNextSubpathPath(iter, &result, NULL, &closed);
    expect(Ok, stat);
    stat = GdipPathIterNextSubpathPath(iter, NULL, NULL, &closed);
    expect(InvalidParameter, stat);
    stat = GdipPathIterNextSubpathPath(iter, NULL, retpath, NULL);
    expect(InvalidParameter, stat);
    stat = GdipPathIterNextSubpathPath(iter, &result, retpath, NULL);
    expect(InvalidParameter, stat);
    GdipDeletePathIter(iter);
    GdipDeletePath(retpath);

    /* empty path */
    GdipCreatePath(FillModeAlternate, &retpath);
    GdipCreatePathIter(&iter, path);
    result = -2;
    closed = TRUE;
    stat = GdipPathIterNextSubpathPath(iter, &result, retpath, &closed);
    expect(Ok, stat);
    expect(0, result);
    expect(TRUE, closed);
    count = -1;
    GdipGetPointCount(retpath, &count);
    expect(0, count);
    GdipDeletePathIter(iter);
    GdipDeletePath(retpath);

    /* open figure */
    GdipAddPathLine(path, 5.0, 5.0, 100.0, 50.0);

    GdipCreatePath(FillModeAlternate, &retpath);
    GdipCreatePathIter(&iter, path);
    result = -2;
    closed = TRUE;
    stat = GdipPathIterNextSubpathPath(iter, &result, retpath, &closed);
    expect(Ok, stat);
    expect(2, result);
    expect(FALSE, closed);
    count = -1;
    GdipGetPointCount(retpath, &count);
    expect(2, count);
    /* subsequent call */
    result = -2;
    closed = TRUE;
    stat = GdipPathIterNextSubpathPath(iter, &result, retpath, &closed);
    expect(Ok, stat);
    expect(0, result);
    expect(TRUE, closed);
    count = -1;
    GdipGetPointCount(retpath, &count);
    expect(2, count);
    GdipDeletePathIter(iter);

    /* closed figure, check does it extend retpath or reset it */
    GdipAddPathLine(retpath, 50.0, 55.0, 200.0, 150.0);

    GdipClosePathFigure(path);
    GdipAddPathLine(path, 50.0, 55.0, 200.0, 150.0);
    GdipClosePathFigure(path);

    GdipCreatePathIter(&iter, path);
    result = -2;
    closed = FALSE;
    stat = GdipPathIterNextSubpathPath(iter, &result, retpath, &closed);
    expect(Ok, stat);
    expect(2, result);
    expect(TRUE, closed);
    count = -1;
    GdipGetPointCount(retpath, &count);
    expect(2, count);
    /* subsequent call */
    result = -2;
    closed = FALSE;
    stat = GdipPathIterNextSubpathPath(iter, &result, retpath, &closed);
    expect(Ok, stat);
    expect(2, result);
    expect(TRUE, closed);
    count = -1;
    GdipGetPointCount(retpath, &count);
    expect(2, count);
    result = -2;
    closed = FALSE;
    stat = GdipPathIterNextSubpathPath(iter, &result, retpath, &closed);
    expect(Ok, stat);
    expect(0, result);
    expect(TRUE, closed);
    count = -1;
    GdipGetPointCount(retpath, &count);
    expect(2, count);
    GdipDeletePathIter(iter);

    GdipDeletePath(retpath);
    GdipDeletePath(path);
}
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

/* Variables and functions */
 int /*<<< orphan*/  FillModeAlternate ; 
 int /*<<< orphan*/  GdipAddPathLine (int /*<<< orphan*/ *,double,double,double,double) ; 
 int /*<<< orphan*/  GdipAddPathRectangle (int /*<<< orphan*/ *,double,double,double,double) ; 
 int /*<<< orphan*/  GdipCreatePath (int /*<<< orphan*/ ,int /*<<< orphan*/ **) ; 
 int /*<<< orphan*/  GdipCreatePathIter (int /*<<< orphan*/ **,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  GdipDeletePath (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  GdipDeletePathIter (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  GdipGetPointCount (int /*<<< orphan*/ *,int*) ; 
 int GdipPathIterNextMarkerPath (int /*<<< orphan*/ *,int*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  GdipSetPathMarker (int /*<<< orphan*/ *) ; 
 int InvalidParameter ; 
 int Ok ; 
 int /*<<< orphan*/  expect (int,int) ; 

__attribute__((used)) static void test_nextmarkerpath(void)
{
    GpPath *path, *retpath;
    GpPathIterator *iter;
    GpStatus stat;
    INT result, count;

    GdipCreatePath(FillModeAlternate, &path);

    /* NULL */
    stat = GdipPathIterNextMarkerPath(NULL, NULL, NULL);
    expect(InvalidParameter, stat);
    stat = GdipPathIterNextMarkerPath(NULL, &result, NULL);
    expect(InvalidParameter, stat);
    stat = GdipPathIterNextMarkerPath(NULL, &result, path);
    expect(InvalidParameter, stat);

    GdipAddPathRectangle(path, 5.0, 5.0, 100.0, 50.0);

    /* no markers */
    GdipCreatePath(FillModeAlternate, &retpath);
    GdipCreatePathIter(&iter, path);
    result = -1;
    stat = GdipPathIterNextMarkerPath(iter, &result, retpath);
    expect(Ok, stat);
    expect(4, result);
    count = -1;
    GdipGetPointCount(retpath, &count);
    expect(4, count);
    result = -1;
    stat = GdipPathIterNextMarkerPath(iter, &result, retpath);
    expect(Ok, stat);
    expect(0, result);
    count = -1;
    GdipGetPointCount(retpath, &count);
    expect(4, count);
    GdipDeletePathIter(iter);
    GdipDeletePath(retpath);

    /* one marker */
    GdipSetPathMarker(path);
    GdipCreatePath(FillModeAlternate, &retpath);
    GdipCreatePathIter(&iter, path);
    result = -1;
    stat = GdipPathIterNextMarkerPath(iter, &result, retpath);
    expect(Ok, stat);
    expect(4, result);
    count = -1;
    GdipGetPointCount(retpath, &count);
    expect(4, count);
    result = -1;
    stat = GdipPathIterNextMarkerPath(iter, &result, retpath);
    expect(Ok, stat);
    expect(0, result);
    count = -1;
    GdipGetPointCount(retpath, &count);
    expect(4, count);
    GdipDeletePathIter(iter);
    GdipDeletePath(retpath);

    /* two markers */
    GdipAddPathLine(path, 0.0, 0.0, 10.0, 30.0);
    GdipSetPathMarker(path);
    GdipCreatePath(FillModeAlternate, &retpath);
    GdipCreatePathIter(&iter, path);
    result = -1;
    stat = GdipPathIterNextMarkerPath(iter, &result, retpath);
    expect(Ok, stat);
    expect(4, result);
    result = -1;
    stat = GdipPathIterNextMarkerPath(iter, &result, retpath);
    expect(Ok, stat);
    expect(2, result);
    result = -1;
    stat = GdipPathIterNextMarkerPath(iter, &result, retpath);
    expect(Ok, stat);
    expect(0, result);
    GdipDeletePathIter(iter);
    GdipDeletePath(retpath);

    GdipDeletePath(path);
}
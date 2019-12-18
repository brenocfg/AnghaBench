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
 int GdipPathIterNextMarker (int /*<<< orphan*/ *,int*,int*,int*) ; 
 int /*<<< orphan*/  GdipSetPathMarker (int /*<<< orphan*/ *) ; 
 int InvalidParameter ; 
 int Ok ; 
 int /*<<< orphan*/  expect (int,int) ; 

__attribute__((used)) static void test_nextmarker(void)
{
    GpPath *path;
    GpPathIterator *iter;
    GpStatus stat;
    INT start, end;
    INT result;

    /* NULL args
       BOOL out argument is local in wrapper class method,
       so it always has not-NULL address */
    stat = GdipPathIterNextMarker(NULL, &result, NULL, NULL);
    expect(InvalidParameter, stat);
    stat = GdipPathIterNextMarker(NULL, &result, &start, NULL);
    expect(InvalidParameter, stat);
    stat = GdipPathIterNextMarker(NULL, &result, NULL, &end);
    expect(InvalidParameter, stat);

    GdipCreatePath(FillModeAlternate, &path);
    GdipAddPathRectangle(path, 5.0, 5.0, 100.0, 50.0);

    /* no markers */
    GdipCreatePathIter(&iter, path);
    start = end = result = (INT)0xdeadbeef;
    stat = GdipPathIterNextMarker(iter, &result, &start, &end);
    expect(Ok, stat);
    expect(0, start);
    expect(3, end);
    expect(4, result);
    start = end = result = (INT)0xdeadbeef;
    stat = GdipPathIterNextMarker(iter, &result, &start, &end);
    expect(Ok, stat);
    /* start/end remain unchanged */
    expect((INT)0xdeadbeef, start);
    expect((INT)0xdeadbeef, end);
    expect(0, result);
    GdipDeletePathIter(iter);

    /* one marker */
    GdipSetPathMarker(path);
    GdipCreatePathIter(&iter, path);
    start = end = result = (INT)0xdeadbeef;
    stat = GdipPathIterNextMarker(iter, &result, &start, &end);
    expect(Ok, stat);
    expect(0, start);
    expect(3, end);
    expect(4, result);
    start = end = result = (INT)0xdeadbeef;
    stat = GdipPathIterNextMarker(iter, &result, &start, &end);
    expect(Ok, stat);
    expect((INT)0xdeadbeef, start);
    expect((INT)0xdeadbeef, end);
    expect(0, result);
    GdipDeletePathIter(iter);

    /* two markers */
    GdipAddPathLine(path, 0.0, 0.0, 10.0, 30.0);
    GdipSetPathMarker(path);
    GdipCreatePathIter(&iter, path);
    start = end = result = (INT)0xdeadbeef;
    stat = GdipPathIterNextMarker(iter, &result, &start, &end);
    expect(Ok, stat);
    expect(0, start);
    expect(3, end);
    expect(4, result);
    start = end = result = (INT)0xdeadbeef;
    stat = GdipPathIterNextMarker(iter, &result, &start, &end);
    expect(Ok, stat);
    expect(4, start);
    expect(5, end);
    expect(2, result);
    start = end = result = (INT)0xdeadbeef;
    stat = GdipPathIterNextMarker(iter, &result, &start, &end);
    expect(Ok, stat);
    expect((INT)0xdeadbeef, start);
    expect((INT)0xdeadbeef, end);
    expect(0, result);
    GdipDeletePathIter(iter);

    GdipDeletePath(path);
}
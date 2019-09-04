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
typedef  int /*<<< orphan*/  INT ;
typedef  int /*<<< orphan*/  GpStatus ;
typedef  int /*<<< orphan*/  GpPathIterator ;
typedef  int /*<<< orphan*/  GpPath ;
typedef  int /*<<< orphan*/  BOOL ;

/* Variables and functions */
 int /*<<< orphan*/  FALSE ; 
 int /*<<< orphan*/  FillModeAlternate ; 
 int /*<<< orphan*/  GdipAddPathLine (int /*<<< orphan*/ *,double,double,double,double) ; 
 int /*<<< orphan*/  GdipCreatePath (int /*<<< orphan*/ ,int /*<<< orphan*/ **) ; 
 int /*<<< orphan*/  GdipCreatePathIter (int /*<<< orphan*/ **,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  GdipDeletePath (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  GdipDeletePathIter (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  GdipPathIterIsValid (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  GdipPathIterNextMarker (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  InvalidParameter ; 
 int /*<<< orphan*/  Ok ; 
 int /*<<< orphan*/  TRUE ; 
 int /*<<< orphan*/  expect (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void test_isvalid(void)
{
    GpPath *path;
    GpPathIterator *iter;
    GpStatus stat;
    BOOL isvalid;
    INT start, end, result;

    GdipCreatePath(FillModeAlternate, &path);

    /* NULL args */
    GdipCreatePathIter(&iter, path);
    stat = GdipPathIterIsValid(NULL, NULL);
    expect(InvalidParameter, stat);
    stat = GdipPathIterIsValid(iter, NULL);
    expect(InvalidParameter, stat);
    stat = GdipPathIterIsValid(NULL, &isvalid);
    expect(InvalidParameter, stat);
    GdipDeletePathIter(iter);

    /* on empty path */
    GdipCreatePathIter(&iter, path);
    isvalid = FALSE;
    stat = GdipPathIterIsValid(iter, &isvalid);
    expect(Ok, stat);
    expect(TRUE, isvalid);
    GdipDeletePathIter(iter);

    /* no markers */
    stat = GdipAddPathLine(path, 50.0, 50.0, 110.0, 40.0);
    expect(Ok, stat);
    stat = GdipCreatePathIter(&iter, path);
    expect(Ok, stat);
    stat = GdipPathIterNextMarker(iter, &result, &start, &end);
    expect(Ok, stat);
    isvalid = FALSE;
    stat = GdipPathIterIsValid(iter, &isvalid);
    expect(Ok, stat);
    expect(TRUE, isvalid);
    GdipDeletePathIter(iter);

    GdipDeletePath(path);
}
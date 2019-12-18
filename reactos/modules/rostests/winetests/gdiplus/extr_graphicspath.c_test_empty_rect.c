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
typedef  int /*<<< orphan*/  GpPath ;
typedef  int /*<<< orphan*/  BOOL ;

/* Variables and functions */
 int FALSE ; 
 int /*<<< orphan*/  FillModeAlternate ; 
 int /*<<< orphan*/  GdipAddPathRectangle (int /*<<< orphan*/ *,double,double,double,double) ; 
 int /*<<< orphan*/  GdipCreatePath (int /*<<< orphan*/ ,int /*<<< orphan*/ **) ; 
 int /*<<< orphan*/  GdipDeletePath (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  GdipGetPointCount (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  GdipIsVisiblePathPoint (int /*<<< orphan*/ *,double,double,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int Ok ; 
 int /*<<< orphan*/  expect (int,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void test_empty_rect(void)
{
    GpPath *path;
    GpStatus status;
    INT count;
    BOOL result;

    status = GdipCreatePath(FillModeAlternate, &path);
    expect(Ok, status);

    status = GdipAddPathRectangle(path, 0.0, 0.0, -5.0, 5.0);
    expect(Ok, status);

    status = GdipGetPointCount(path, &count);
    expect(Ok, status);
    expect(0, count);

    status = GdipIsVisiblePathPoint(path, -2.0, 2.0, NULL, &result);
    expect(Ok, status);
    expect(FALSE, result);

    status = GdipAddPathRectangle(path, 0.0, 0.0, 5.0, -5.0);
    expect(Ok, status);

    status = GdipGetPointCount(path, &count);
    expect(Ok, status);
    expect(0, count);

    status = GdipAddPathRectangle(path, 0.0, 0.0, 0.0, 5.0);
    expect(Ok, status);

    status = GdipGetPointCount(path, &count);
    expect(Ok, status);
    expect(0, count);

    status = GdipAddPathRectangle(path, 0.0, 0.0, 5.0, 0.0);
    expect(Ok, status);

    status = GdipGetPointCount(path, &count);
    expect(Ok, status);
    expect(0, count);

    status = GdipAddPathRectangle(path, 0.0, 0.0, 5.0, 0.1);
    expect(Ok, status);

    status = GdipGetPointCount(path, &count);
    expect(Ok, status);
    expect(4, count);

    GdipDeletePath(path);
}
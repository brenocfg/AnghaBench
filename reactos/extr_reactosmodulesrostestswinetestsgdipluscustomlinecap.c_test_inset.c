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
typedef  scalar_t__ REAL ;
typedef  int /*<<< orphan*/  GpStatus ;
typedef  int /*<<< orphan*/  GpPath ;
typedef  int /*<<< orphan*/  GpCustomLineCap ;

/* Variables and functions */
 int /*<<< orphan*/  FillModeAlternate ; 
 int /*<<< orphan*/  GdipAddPathRectangle (int /*<<< orphan*/ *,double,double,double,double) ; 
 int /*<<< orphan*/  GdipCreateCustomLineCap (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ ,double,int /*<<< orphan*/ **) ; 
 int /*<<< orphan*/  GdipCreatePath (int /*<<< orphan*/ ,int /*<<< orphan*/ **) ; 
 int /*<<< orphan*/  GdipDeleteCustomLineCap (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  GdipDeletePath (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  GdipGetCustomLineCapBaseInset (int /*<<< orphan*/ *,scalar_t__*) ; 
 int /*<<< orphan*/  InvalidParameter ; 
 int /*<<< orphan*/  LineCapFlat ; 
 int /*<<< orphan*/  Ok ; 
 int /*<<< orphan*/  expect (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  expectf (double,scalar_t__) ; 

__attribute__((used)) static void test_inset(void)
{
    GpCustomLineCap *custom;
    GpPath *path;
    REAL inset;
    GpStatus stat;

    stat = GdipCreatePath(FillModeAlternate, &path);
    expect(Ok, stat);
    stat = GdipAddPathRectangle(path, 5.0, 5.0, 10.0, 10.0);
    expect(Ok, stat);

    stat = GdipCreateCustomLineCap(NULL, path, LineCapFlat, 0.0, &custom);
    expect(Ok, stat);

    /* NULL args */
    stat = GdipGetCustomLineCapBaseInset(NULL, NULL);
    expect(InvalidParameter, stat);
    stat = GdipGetCustomLineCapBaseInset(NULL, &inset);
    expect(InvalidParameter, stat);
    stat = GdipGetCustomLineCapBaseInset(custom, NULL);
    expect(InvalidParameter, stat);
    /* valid args */
    inset = (REAL)0xdeadbeef;
    stat = GdipGetCustomLineCapBaseInset(custom, &inset);
    expect(Ok, stat);
    expectf(0.0, inset);

    GdipDeleteCustomLineCap(custom);
    GdipDeletePath(path);
}
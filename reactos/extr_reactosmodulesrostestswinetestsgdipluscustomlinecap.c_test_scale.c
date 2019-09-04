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
 int /*<<< orphan*/  GdipGetCustomLineCapWidthScale (int /*<<< orphan*/ *,scalar_t__*) ; 
 int /*<<< orphan*/  GdipSetCustomLineCapWidthScale (int /*<<< orphan*/ *,double) ; 
 int /*<<< orphan*/  InvalidParameter ; 
 int /*<<< orphan*/  LineCapFlat ; 
 int /*<<< orphan*/  Ok ; 
 int /*<<< orphan*/  expect (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  expectf (double,scalar_t__) ; 

__attribute__((used)) static void test_scale(void)
{
    GpCustomLineCap *custom;
    GpPath *path;
    REAL scale;
    GpStatus stat;

    stat = GdipCreatePath(FillModeAlternate, &path);
    expect(Ok, stat);
    stat = GdipAddPathRectangle(path, 5.0, 5.0, 10.0, 10.0);
    expect(Ok, stat);

    stat = GdipCreateCustomLineCap(NULL, path, LineCapFlat, 0.0, &custom);
    expect(Ok, stat);

    /* NULL args */
    stat = GdipGetCustomLineCapWidthScale(NULL, NULL);
    expect(InvalidParameter, stat);
    stat = GdipGetCustomLineCapWidthScale(NULL, &scale);
    expect(InvalidParameter, stat);
    stat = GdipGetCustomLineCapWidthScale(custom, NULL);
    expect(InvalidParameter, stat);

    stat = GdipSetCustomLineCapWidthScale(NULL, 2.0);
    expect(InvalidParameter, stat);

    /* valid args: read default */
    scale = (REAL)0xdeadbeef;
    stat = GdipGetCustomLineCapWidthScale(custom, &scale);
    expect(Ok, stat);
    expectf(1.0, scale);

    /* set and read back some scale values: there is no limit for the scale */
    stat = GdipSetCustomLineCapWidthScale(custom, 2.5);
    expect(Ok, stat);
    scale = (REAL)0xdeadbeef;
    stat = GdipGetCustomLineCapWidthScale(custom, &scale);
    expect(Ok, stat);
    expectf(2.5, scale);

    stat = GdipSetCustomLineCapWidthScale(custom, 42.0);
    expect(Ok, stat);
    scale = (REAL)0xdeadbeef;
    stat = GdipGetCustomLineCapWidthScale(custom, &scale);
    expect(Ok, stat);
    expectf(42.0, scale);

    stat = GdipSetCustomLineCapWidthScale(custom, 3000.0);
    expect(Ok, stat);
    scale = (REAL)0xdeadbeef;
    stat = GdipGetCustomLineCapWidthScale(custom, &scale);
    expect(Ok, stat);
    expectf(3000.0, scale);

    stat = GdipSetCustomLineCapWidthScale(custom, 0.0);
    expect(Ok, stat);
    scale = (REAL)0xdeadbeef;
    stat = GdipGetCustomLineCapWidthScale(custom, &scale);
    expect(Ok, stat);
    expectf(0.0, scale);

    GdipDeleteCustomLineCap(custom);
    GdipDeletePath(path);
}
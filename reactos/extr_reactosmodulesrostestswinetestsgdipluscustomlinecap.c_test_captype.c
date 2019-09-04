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
typedef  int GpStatus ;
typedef  int /*<<< orphan*/  GpPath ;
typedef  int /*<<< orphan*/  GpCustomLineCap ;
typedef  int /*<<< orphan*/  GpAdjustableArrowCap ;
typedef  int CustomLineCapType ;

/* Variables and functions */
 int CustomLineCapTypeAdjustableArrow ; 
 int CustomLineCapTypeDefault ; 
 int /*<<< orphan*/  FillModeAlternate ; 
 int GdipAddPathRectangle (int /*<<< orphan*/ *,double,double,double,double) ; 
 int GdipCreateAdjustableArrowCap (double,double,int /*<<< orphan*/ ,int /*<<< orphan*/ **) ; 
 int GdipCreateCustomLineCap (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ ,double,int /*<<< orphan*/ **) ; 
 int GdipCreatePath (int /*<<< orphan*/ ,int /*<<< orphan*/ **) ; 
 int /*<<< orphan*/  GdipDeleteCustomLineCap (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  GdipDeletePath (int /*<<< orphan*/ *) ; 
 int GdipGetCustomLineCapType (int /*<<< orphan*/ *,int*) ; 
 int InvalidParameter ; 
 int /*<<< orphan*/  LineCapFlat ; 
 int Ok ; 
 int /*<<< orphan*/  TRUE ; 
 int /*<<< orphan*/  ok (int,char*,int) ; 

__attribute__((used)) static void test_captype(void)
{
    GpAdjustableArrowCap *arrowcap;
    GpCustomLineCap *custom;
    CustomLineCapType type;
    GpStatus stat;
    GpPath *path;

    stat = GdipGetCustomLineCapType(NULL, NULL);
    ok(stat == InvalidParameter, "Unexpected return code, %d\n", stat);

    type = 10;
    stat = GdipGetCustomLineCapType(NULL, &type);
    ok(stat == InvalidParameter, "Unexpected return code, %d\n", stat);
    ok(type == 10, "Unexpected cap type, %d\n", type);

    /* default cap */
    stat = GdipCreatePath(FillModeAlternate, &path);
    ok(stat == Ok, "Failed to create path, %d\n", stat);
    stat = GdipAddPathRectangle(path, 5.0, 5.0, 10.0, 10.0);
    ok(stat == Ok, "AddPathRectangle failed, %d\n", stat);

    stat = GdipCreateCustomLineCap(NULL, path, LineCapFlat, 0.0, &custom);
    ok(stat == Ok, "Failed to create cap, %d\n", stat);
    stat = GdipGetCustomLineCapType(custom, &type);
    ok(stat == Ok, "Failed to get cap type, %d\n", stat);
    ok(type == CustomLineCapTypeDefault, "Unexpected cap type %d\n", stat);
    GdipDeleteCustomLineCap(custom);
    GdipDeletePath(path);

    /* arrow cap */
    stat = GdipCreateAdjustableArrowCap(17.0, 15.0, TRUE, &arrowcap);
    ok(stat == Ok, "Failed to create adjustable cap, %d\n", stat);

    stat = GdipGetCustomLineCapType((GpCustomLineCap*)arrowcap, &type);
    ok(stat == Ok, "Failed to get cap type, %d\n", stat);
    ok(type == CustomLineCapTypeAdjustableArrow, "Unexpected cap type %d\n", stat);

    GdipDeleteCustomLineCap((GpCustomLineCap*)arrowcap);
}
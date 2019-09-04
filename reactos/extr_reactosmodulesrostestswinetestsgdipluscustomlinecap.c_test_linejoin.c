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
typedef  int /*<<< orphan*/  GpPath ;
typedef  int /*<<< orphan*/  GpLineJoin ;
typedef  int /*<<< orphan*/  GpCustomLineCap ;

/* Variables and functions */
 int /*<<< orphan*/  FillModeAlternate ; 
 int /*<<< orphan*/  GdipAddPathRectangle (int /*<<< orphan*/ *,double,double,double,double) ; 
 int /*<<< orphan*/  GdipCreateCustomLineCap (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ ,double,int /*<<< orphan*/ **) ; 
 int /*<<< orphan*/  GdipCreatePath (int /*<<< orphan*/ ,int /*<<< orphan*/ **) ; 
 int /*<<< orphan*/  GdipDeleteCustomLineCap (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  GdipDeletePath (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  GdipGetCustomLineCapStrokeJoin (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  GdipSetCustomLineCapStrokeJoin (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  InvalidParameter ; 
 int /*<<< orphan*/  LineCapFlat ; 
 int /*<<< orphan*/  LineJoinBevel ; 
 int /*<<< orphan*/  LineJoinMiter ; 
 int /*<<< orphan*/  LineJoinMiterClipped ; 
 int /*<<< orphan*/  LineJoinRound ; 
 int /*<<< orphan*/  Ok ; 
 int /*<<< orphan*/  expect (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void test_linejoin(void)
{
    GpCustomLineCap *custom;
    GpPath *path;
    GpLineJoin join;
    GpStatus stat;

    stat = GdipCreatePath(FillModeAlternate, &path);
    expect(Ok, stat);
    stat = GdipAddPathRectangle(path, 5.0, 5.0, 10.0, 10.0);
    expect(Ok, stat);

    stat = GdipCreateCustomLineCap(NULL, path, LineCapFlat, 0.0, &custom);
    expect(Ok, stat);

    /* NULL args */
    stat = GdipGetCustomLineCapStrokeJoin(NULL, NULL);
    expect(InvalidParameter, stat);
    stat = GdipGetCustomLineCapStrokeJoin(custom, NULL);
    expect(InvalidParameter, stat);
    stat = GdipGetCustomLineCapStrokeJoin(NULL, &join);
    expect(InvalidParameter, stat);
    stat = GdipSetCustomLineCapStrokeJoin(NULL, LineJoinBevel);
    expect(InvalidParameter, stat);

    /* LineJoinMiter is default */
    stat = GdipGetCustomLineCapStrokeJoin(custom, &join);
    expect(Ok, stat);
    expect(LineJoinMiter, join);

    /* set/get */
    stat = GdipSetCustomLineCapStrokeJoin(custom, LineJoinBevel);
    expect(Ok, stat);
    stat = GdipGetCustomLineCapStrokeJoin(custom, &join);
    expect(Ok, stat);
    expect(LineJoinBevel, join);
    stat = GdipSetCustomLineCapStrokeJoin(custom, LineJoinRound);
    expect(Ok, stat);
    stat = GdipGetCustomLineCapStrokeJoin(custom, &join);
    expect(Ok, stat);
    expect(LineJoinRound, join);
    stat = GdipSetCustomLineCapStrokeJoin(custom, LineJoinMiterClipped);
    expect(Ok, stat);
    stat = GdipGetCustomLineCapStrokeJoin(custom, &join);
    expect(Ok, stat);
    expect(LineJoinMiterClipped, join);

    GdipDeleteCustomLineCap(custom);
    GdipDeletePath(path);
}
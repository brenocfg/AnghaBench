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
typedef  int /*<<< orphan*/  GpPen ;
typedef  int /*<<< orphan*/  GpCustomLineCap ;
typedef  int /*<<< orphan*/  ARGB ;

/* Variables and functions */
 int /*<<< orphan*/  GdipCreatePen1 (int /*<<< orphan*/ ,float,int /*<<< orphan*/ ,int /*<<< orphan*/ **) ; 
 int /*<<< orphan*/  GdipDeletePen (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  GdipGetPenCustomEndCap (int /*<<< orphan*/ *,int /*<<< orphan*/ **) ; 
 int /*<<< orphan*/  GdipGetPenCustomStartCap (int /*<<< orphan*/ *,int /*<<< orphan*/ **) ; 
 int /*<<< orphan*/  GdipSetPenCustomEndCap (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  GdipSetPenCustomStartCap (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  InvalidParameter ; 
 int /*<<< orphan*/  Ok ; 
 int /*<<< orphan*/  UnitPixel ; 
 int /*<<< orphan*/  expect (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ok (int /*<<< orphan*/ ,char*) ; 

__attribute__((used)) static void test_customcap(void)
{
    GpPen *pen;
    GpStatus status;
    GpCustomLineCap *custom;

    status = GdipCreatePen1((ARGB)0xffff00ff, 10.0f, UnitPixel, &pen);
    expect(Ok, status);

    /* NULL args */
    status = GdipGetPenCustomStartCap(NULL, NULL);
    expect(InvalidParameter, status);
    status = GdipGetPenCustomStartCap(pen, NULL);
    expect(InvalidParameter, status);
    status = GdipGetPenCustomStartCap(NULL, &custom);
    expect(InvalidParameter, status);

    status = GdipGetPenCustomEndCap(NULL, NULL);
    expect(InvalidParameter, status);
    status = GdipGetPenCustomEndCap(pen, NULL);
    expect(InvalidParameter, status);
    status = GdipGetPenCustomEndCap(NULL, &custom);
    expect(InvalidParameter, status);

    /* native crashes on pen == NULL, custom != NULL */
    status = GdipSetPenCustomStartCap(NULL, NULL);
    expect(InvalidParameter, status);
    status = GdipSetPenCustomStartCap(pen, NULL);
    expect(InvalidParameter, status);

    status = GdipSetPenCustomEndCap(NULL, NULL);
    expect(InvalidParameter, status);
    status = GdipSetPenCustomEndCap(pen, NULL);
    expect(InvalidParameter, status);

    /* get without setting previously */
    custom = (GpCustomLineCap*)0xdeadbeef;
    status = GdipGetPenCustomEndCap(pen, &custom);
    expect(Ok, status);
    ok(custom == NULL,"Expect CustomCap == NULL\n");

    custom = (GpCustomLineCap*)0xdeadbeef;
    status = GdipGetPenCustomStartCap(pen, &custom);
    expect(Ok, status);
    ok(custom == NULL,"Expect CustomCap == NULL\n");

    GdipDeletePen(pen);
}
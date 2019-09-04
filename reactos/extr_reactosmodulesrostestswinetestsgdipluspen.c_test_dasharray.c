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
typedef  double REAL ;
typedef  scalar_t__ GpStatus ;
typedef  int /*<<< orphan*/  GpPen ;
typedef  scalar_t__ GpDashStyle ;

/* Variables and functions */
 scalar_t__ DashStyleCustom ; 
 scalar_t__ DashStyleDot ; 
 scalar_t__ DashStyleSolid ; 
 int /*<<< orphan*/  GdipCreatePen1 (int,double,int /*<<< orphan*/ ,int /*<<< orphan*/ **) ; 
 int /*<<< orphan*/  GdipDeletePen (int /*<<< orphan*/ *) ; 
 scalar_t__ GdipGetPenDashArray (int /*<<< orphan*/ *,double*,int) ; 
 int /*<<< orphan*/  GdipGetPenDashStyle (int /*<<< orphan*/ *,scalar_t__*) ; 
 scalar_t__ GdipSetPenDashArray (int /*<<< orphan*/ *,double*,int) ; 
 int /*<<< orphan*/  GdipSetPenDashStyle (int /*<<< orphan*/ *,scalar_t__) ; 
 scalar_t__ InvalidParameter ; 
 scalar_t__ Ok ; 
 scalar_t__ OutOfMemory ; 
 int /*<<< orphan*/  UnitWorld ; 
 int /*<<< orphan*/  expect (scalar_t__,scalar_t__) ; 
 int /*<<< orphan*/  expectf (double,double) ; 
 int /*<<< orphan*/  ok (int,char*,scalar_t__) ; 

__attribute__((used)) static void test_dasharray(void)
{
    GpPen *pen;
    GpDashStyle style;
    GpStatus status;
    REAL dashes[12];

    GdipCreatePen1(0xdeadbeef, 10.0, UnitWorld, &pen);
    dashes[0] = 10.0;
    dashes[1] = 11.0;
    dashes[2] = 12.0;
    dashes[3] = 13.0;
    dashes[4] = 14.0;
    dashes[5] = -100.0;
    dashes[6] = -100.0;
    dashes[7] = dashes[8] = dashes[9] = dashes[10] = dashes[11] = 0.0;

    /* setting the array sets the type to custom */
    GdipGetPenDashStyle(pen, &style);
    expect(DashStyleSolid, style);
    status = GdipSetPenDashArray(pen, dashes, 2);
    expect(Ok, status);
    GdipGetPenDashStyle(pen, &style);
    expect(DashStyleCustom, style);

    /* Getting the array on a non-custom pen returns invalid parameter (unless
     * you are getting 0 elements).*/
    GdipSetPenDashStyle(pen, DashStyleSolid);
    status = GdipGetPenDashArray(pen, &dashes[5], 2);
    expect(InvalidParameter, status);
    status = GdipGetPenDashArray(pen, &dashes[5], 0);
    expect(Ok, status);

    /* What does setting DashStyleCustom do to the array length? */
    GdipSetPenDashArray(pen, dashes, 2);
    GdipSetPenDashStyle(pen, DashStyleCustom);
    status = GdipGetPenDashArray(pen, &dashes[5], 2);
    expect(Ok, status);
    expectf(10.0, dashes[5]);
    expectf(11.0, dashes[6]);

    /* Set the array, then get with different sized buffers. */
    status = GdipSetPenDashArray(pen, dashes, 5);
    expect(Ok, status);
    dashes[5] = -100.0;
    dashes[6] = -100.0;
    status = GdipGetPenDashArray(pen, &dashes[5], 1);
    expect(Ok, status); /* not InsufficientBuffer! */
    expectf(10.0, dashes[5]);
    expectf(-100.0, dashes[6]);
    dashes[5] = -100.0;
    status = GdipGetPenDashArray(pen, &dashes[5], 6);
    expect(InvalidParameter, status); /* not Ok! */
    expectf(-100.0, dashes[5]);
    expectf(-100.0, dashes[6]);

    /* Some invalid array values. */
    status = GdipSetPenDashArray(pen, &dashes[7], 5);
    expect(InvalidParameter, status);
    dashes[9] = -1.0;
    status = GdipSetPenDashArray(pen, &dashes[7], 5);
    expect(InvalidParameter, status);

    /* Try to set with count = 0. */
    GdipSetPenDashStyle(pen, DashStyleDot);
    if (0)  /* corrupts stack on 64-bit Vista */
    {
    status = GdipSetPenDashArray(pen, dashes, 0);
    ok(status == OutOfMemory || status == InvalidParameter,
       "Expected OutOfMemory or InvalidParameter, got %.8x\n", status);
    }
    status = GdipSetPenDashArray(pen, dashes, -1);
    ok(status == OutOfMemory || status == InvalidParameter,
       "Expected OutOfMemory or InvalidParameter, got %.8x\n", status);
    GdipGetPenDashStyle(pen, &style);
    expect(DashStyleDot, style);

    GdipDeletePen(pen);
}
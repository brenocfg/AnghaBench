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
typedef  int /*<<< orphan*/  INT ;
typedef  int /*<<< orphan*/ * HDC ;
typedef  int /*<<< orphan*/  GpStatus ;
typedef  int /*<<< orphan*/  GpGraphics ;
typedef  scalar_t__ BOOL ;

/* Variables and functions */
 int /*<<< orphan*/  CombineModeReplace ; 
 scalar_t__ FALSE ; 
 int /*<<< orphan*/  GdipCreateFromHDC (int /*<<< orphan*/ *,int /*<<< orphan*/ **) ; 
 int /*<<< orphan*/  GdipDeleteGraphics (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  GdipIsVisiblePoint (int /*<<< orphan*/ *,double,double,scalar_t__*) ; 
 int /*<<< orphan*/  GdipIsVisiblePointI (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,scalar_t__*) ; 
 int /*<<< orphan*/  GdipSetClipRect (int /*<<< orphan*/ *,int,int,int,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  GdipTranslateWorldTransform (int /*<<< orphan*/ *,int,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * GetDC (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  InvalidParameter ; 
 int /*<<< orphan*/  MatrixOrderAppend ; 
 int /*<<< orphan*/  Ok ; 
 int /*<<< orphan*/  ReleaseDC (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 scalar_t__ TRUE ; 
 int /*<<< orphan*/  expect (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  hwnd ; 
 int /*<<< orphan*/  ok (int,char*,...) ; 

__attribute__((used)) static void test_GdipIsVisiblePoint(void)
{
    GpStatus status;
    GpGraphics *graphics = NULL;
    HDC hdc = GetDC( hwnd );
    REAL x, y;
    BOOL val;

    ok(hdc != NULL, "Expected HDC to be initialized\n");

    status = GdipCreateFromHDC(hdc, &graphics);
    expect(Ok, status);
    ok(graphics != NULL, "Expected graphics to be initialized\n");

    /* null parameters */
    status = GdipIsVisiblePoint(NULL, 0, 0, &val);
    expect(InvalidParameter, status);

    status = GdipIsVisiblePoint(graphics, 0, 0, NULL);
    expect(InvalidParameter, status);

    status = GdipIsVisiblePointI(NULL, 0, 0, &val);
    expect(InvalidParameter, status);

    status = GdipIsVisiblePointI(graphics, 0, 0, NULL);
    expect(InvalidParameter, status);

    x = 0;
    y = 0;
    status = GdipIsVisiblePoint(graphics, x, y, &val);
    expect(Ok, status);
    ok(val == TRUE, "Expected (%.2f, %.2f) to be visible\n", x, y);

    x = -10;
    y = 0;
    status = GdipIsVisiblePoint(graphics, x, y, &val);
    expect(Ok, status);
    ok(val == FALSE, "Expected (%.2f, %.2f) not to be visible\n", x, y);

    x = 0;
    y = -5;
    status = GdipIsVisiblePoint(graphics, x, y, &val);
    expect(Ok, status);
    ok(val == FALSE, "Expected (%.2f, %.2f) not to be visible\n", x, y);

    x = 1;
    y = 1;
    status = GdipIsVisiblePoint(graphics, x, y, &val);
    expect(Ok, status);
    ok(val == TRUE, "Expected (%.2f, %.2f) to be visible\n", x, y);

    status = GdipSetClipRect(graphics, 10, 20, 30, 40, CombineModeReplace);
    expect(Ok, status);

    x = 1;
    y = 1;
    status = GdipIsVisiblePoint(graphics, x, y, &val);
    expect(Ok, status);
    ok(val == FALSE, "After clipping, expected (%.2f, %.2f) not to be visible\n", x, y);

    x = 15.5;
    y = 40.5;
    status = GdipIsVisiblePoint(graphics, x, y, &val);
    expect(Ok, status);
    ok(val == TRUE, "After clipping, expected (%.2f, %.2f) to be visible\n", x, y);

    /* translate into the center of the rect */
    GdipTranslateWorldTransform(graphics, 25, 40, MatrixOrderAppend);

    x = 0;
    y = 0;
    status = GdipIsVisiblePoint(graphics, x, y, &val);
    expect(Ok, status);
    ok(val == TRUE, "Expected (%.2f, %.2f) to be visible\n", x, y);

    x = 25;
    y = 40;
    status = GdipIsVisiblePoint(graphics, x, y, &val);
    expect(Ok, status);
    ok(val == FALSE, "Expected (%.2f, %.2f) not to be visible\n", x, y);

    GdipTranslateWorldTransform(graphics, -25, -40, MatrixOrderAppend);

    /* corner cases */
    x = 9;
    y = 19;
    status = GdipIsVisiblePoint(graphics, x, y, &val);
    expect(Ok, status);
    ok(val == FALSE, "After clipping, expected (%.2f, %.2f) not to be visible\n", x, y);

    x = 9.25;
    y = 19.25;
    status = GdipIsVisiblePoint(graphics, x, y, &val);
    expect(Ok, status);
    ok(val == FALSE, "After clipping, expected (%.2f, %.2f) not to be visible\n", x, y);

    x = 9.5;
    y = 19.5;
    status = GdipIsVisiblePoint(graphics, x, y, &val);
    expect(Ok, status);
    ok(val == TRUE, "After clipping, expected (%.2f, %.2f) to be visible\n", x, y);

    x = 9.75;
    y = 19.75;
    status = GdipIsVisiblePoint(graphics, x, y, &val);
    expect(Ok, status);
    ok(val == TRUE, "After clipping, expected (%.2f, %.2f) to be visible\n", x, y);

    x = 10;
    y = 20;
    status = GdipIsVisiblePoint(graphics, x, y, &val);
    expect(Ok, status);
    ok(val == TRUE, "After clipping, expected (%.2f, %.2f) to be visible\n", x, y);

    x = 40;
    y = 20;
    status = GdipIsVisiblePoint(graphics, x, y, &val);
    expect(Ok, status);
    ok(val == FALSE, "After clipping, expected (%.2f, %.2f) not to be visible\n", x, y);

    x = 39;
    y = 59;
    status = GdipIsVisiblePoint(graphics, x, y, &val);
    expect(Ok, status);
    ok(val == TRUE, "After clipping, expected (%.2f, %.2f) to be visible\n", x, y);

    x = 39.25;
    y = 59.25;
    status = GdipIsVisiblePoint(graphics, x, y, &val);
    expect(Ok, status);
    ok(val == TRUE, "After clipping, expected (%.2f, %.2f) to be visible\n", x, y);

    x = 39.5;
    y = 39.5;
    status = GdipIsVisiblePoint(graphics, x, y, &val);
    expect(Ok, status);
    ok(val == FALSE, "After clipping, expected (%.2f, %.2f) not to be visible\n", x, y);

    x = 39.75;
    y = 59.75;
    status = GdipIsVisiblePoint(graphics, x, y, &val);
    expect(Ok, status);
    ok(val == FALSE, "After clipping, expected (%.2f, %.2f) not to be visible\n", x, y);

    x = 40;
    y = 60;
    status = GdipIsVisiblePoint(graphics, x, y, &val);
    expect(Ok, status);
    ok(val == FALSE, "After clipping, expected (%.2f, %.2f) not to be visible\n", x, y);

    x = 40.15;
    y = 60.15;
    status = GdipIsVisiblePoint(graphics, x, y, &val);
    expect(Ok, status);
    ok(val == FALSE, "After clipping, expected (%.2f, %.2f) not to be visible\n", x, y);

    x = 10;
    y = 60;
    status = GdipIsVisiblePoint(graphics, x, y, &val);
    expect(Ok, status);
    ok(val == FALSE, "After clipping, expected (%.2f, %.2f) not to be visible\n", x, y);

    /* integer version */
    x = 25;
    y = 30;
    status = GdipIsVisiblePointI(graphics, (INT)x, (INT)y, &val);
    expect(Ok, status);
    ok(val == TRUE, "After clipping, expected (%.2f, %.2f) to be visible\n", x, y);

    x = 50;
    y = 100;
    status = GdipIsVisiblePointI(graphics, (INT)x, (INT)y, &val);
    expect(Ok, status);
    ok(val == FALSE, "After clipping, expected (%.2f, %.2f) not to be visible\n", x, y);

    GdipDeleteGraphics(graphics);
    ReleaseDC(hwnd, hdc);
}
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
 int /*<<< orphan*/  GdipIsVisibleRect (int /*<<< orphan*/ *,double,double,double,double,scalar_t__*) ; 
 int /*<<< orphan*/  GdipIsVisibleRectI (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,scalar_t__*) ; 
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

__attribute__((used)) static void test_GdipIsVisibleRect(void)
{
    GpStatus status;
    GpGraphics *graphics = NULL;
    HDC hdc = GetDC( hwnd );
    REAL x, y, width, height;
    BOOL val;

    ok(hdc != NULL, "Expected HDC to be initialized\n");

    status = GdipCreateFromHDC(hdc, &graphics);
    expect(Ok, status);
    ok(graphics != NULL, "Expected graphics to be initialized\n");

    status = GdipIsVisibleRect(NULL, 0, 0, 0, 0, &val);
    expect(InvalidParameter, status);

    status = GdipIsVisibleRect(graphics, 0, 0, 0, 0, NULL);
    expect(InvalidParameter, status);

    status = GdipIsVisibleRectI(NULL, 0, 0, 0, 0, &val);
    expect(InvalidParameter, status);

    status = GdipIsVisibleRectI(graphics, 0, 0, 0, 0, NULL);
    expect(InvalidParameter, status);

    /* entirely within the visible region */
    x = 0; width = 10;
    y = 0; height = 10;
    status = GdipIsVisibleRect(graphics, x, y, width, height, &val);
    expect(Ok, status);
    ok(val == TRUE, "Expected (%.2f, %.2f, %.2f, %.2f) to be visible\n", x, y, width, height);

    /* partially outside */
    x = -10; width = 20;
    y = -10; height = 20;
    status = GdipIsVisibleRect(graphics, x, y, width, height, &val);
    expect(Ok, status);
    ok(val == TRUE, "Expected (%.2f, %.2f, %.2f, %.2f) to be visible\n", x, y, width, height);

    /* entirely outside */
    x = -10; width = 5;
    y = -10; height = 5;
    status = GdipIsVisibleRect(graphics, x, y, width, height, &val);
    expect(Ok, status);
    ok(val == FALSE, "Expected (%.2f, %.2f, %.2f, %.2f) not to be visible\n", x, y, width, height);

    status = GdipSetClipRect(graphics, 10, 20, 30, 40, CombineModeReplace);
    expect(Ok, status);

    /* entirely within the visible region */
    x = 12; width = 10;
    y = 22; height = 10;
    status = GdipIsVisibleRect(graphics, x, y, width, height, &val);
    expect(Ok, status);
    ok(val == TRUE, "Expected (%.2f, %.2f, %.2f, %.2f) to be visible\n", x, y, width, height);

    /* partially outside */
    x = 35; width = 10;
    y = 55; height = 10;
    status = GdipIsVisibleRect(graphics, x, y, width, height, &val);
    expect(Ok, status);
    ok(val == TRUE, "Expected (%.2f, %.2f, %.2f, %.2f) to be visible\n", x, y, width, height);

    /* entirely outside */
    x = 45; width = 5;
    y = 65; height = 5;
    status = GdipIsVisibleRect(graphics, x, y, width, height, &val);
    expect(Ok, status);
    ok(val == FALSE, "Expected (%.2f, %.2f, %.2f, %.2f) not to be visible\n", x, y, width, height);

    /* translate into center of clipping rect */
    GdipTranslateWorldTransform(graphics, 25, 40, MatrixOrderAppend);

    x = 0; width = 10;
    y = 0; height = 10;
    status = GdipIsVisibleRect(graphics, x, y, width, height, &val);
    expect(Ok, status);
    ok(val == TRUE, "Expected (%.2f, %.2f, %.2f, %.2f) to be visible\n", x, y, width, height);

    x = 25; width = 5;
    y = 40; height = 5;
    status = GdipIsVisibleRect(graphics, x, y, width, height, &val);
    expect(Ok, status);
    ok(val == FALSE, "Expected (%.2f, %.2f, %.2f, %.2f) not to be visible\n", x, y, width, height);

    GdipTranslateWorldTransform(graphics, -25, -40, MatrixOrderAppend);

    /* corners entirely outside, but some intersections */
    x = 0; width = 70;
    y = 0; height = 90;
    status = GdipIsVisibleRect(graphics, x, y, width, height, &val);
    expect(Ok, status);
    ok(val == TRUE, "Expected (%.2f, %.2f, %.2f, %.2f) to be visible\n", x, y, width, height);

    x = 0; width = 70;
    y = 0; height = 30;
    status = GdipIsVisibleRect(graphics, x, y, width, height, &val);
    expect(Ok, status);
    ok(val == TRUE, "Expected (%.2f, %.2f, %.2f, %.2f) to be visible\n", x, y, width, height);

    x = 0; width = 30;
    y = 0; height = 90;
    status = GdipIsVisibleRect(graphics, x, y, width, height, &val);
    expect(Ok, status);
    ok(val == TRUE, "Expected (%.2f, %.2f, %.2f, %.2f) to be visible\n", x, y, width, height);

    /* edge cases */
    x = 0; width = 10;
    y = 20; height = 40;
    status = GdipIsVisibleRect(graphics, x, y, width, height, &val);
    expect(Ok, status);
    ok(val == FALSE, "Expected (%.2f, %.2f, %.2f, %.2f) not to be visible\n", x, y, width, height);

    x = 10; width = 30;
    y = 0; height = 20;
    status = GdipIsVisibleRect(graphics, x, y, width, height, &val);
    expect(Ok, status);
    ok(val == FALSE, "Expected (%.2f, %.2f, %.2f, %.2f) not to be visible\n", x, y, width, height);

    x = 40; width = 10;
    y = 20; height = 40;
    status = GdipIsVisibleRect(graphics, x, y, width, height, &val);
    expect(Ok, status);
    ok(val == FALSE, "Expected (%.2f, %.2f, %.2f, %.2f) not to be visible\n", x, y, width, height);

    x = 10; width = 30;
    y = 60; height = 10;
    status = GdipIsVisibleRect(graphics, x, y, width, height, &val);
    expect(Ok, status);
    ok(val == FALSE, "Expected (%.2f, %.2f, %.2f, %.2f) not to be visible\n", x, y, width, height);

    /* rounding tests */
    x = 0.4; width = 10.4;
    y = 20; height = 40;
    status = GdipIsVisibleRect(graphics, x, y, width, height, &val);
    expect(Ok, status);
    ok(val == TRUE, "Expected (%.2f, %.2f, %.2f, %.2f) to be visible\n", x, y, width, height);

    x = 10; width = 30;
    y = 0.4; height = 20.4;
    status = GdipIsVisibleRect(graphics, x, y, width, height, &val);
    expect(Ok, status);
    ok(val == TRUE, "Expected (%.2f, %.2f, %.2f, %.2f) to be visible\n", x, y, width, height);

    /* integer version */
    x = 0; width = 30;
    y = 0; height = 90;
    status = GdipIsVisibleRectI(graphics, (INT)x, (INT)y, (INT)width, (INT)height, &val);
    expect(Ok, status);
    ok(val == TRUE, "Expected (%.2f, %.2f, %.2f, %.2f) to be visible\n", x, y, width, height);

    x = 12; width = 10;
    y = 22; height = 10;
    status = GdipIsVisibleRectI(graphics, (INT)x, (INT)y, (INT)width, (INT)height, &val);
    expect(Ok, status);
    ok(val == TRUE, "Expected (%.2f, %.2f, %.2f, %.2f) to be visible\n", x, y, width, height);

    GdipDeleteGraphics(graphics);
    ReleaseDC(hwnd, hdc);
}
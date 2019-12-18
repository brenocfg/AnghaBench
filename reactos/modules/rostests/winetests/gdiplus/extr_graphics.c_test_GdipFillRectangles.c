#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct TYPE_3__ {int member_0; int member_1; int member_2; int member_3; } ;
typedef  int /*<<< orphan*/ * HDC ;
typedef  int /*<<< orphan*/  GpStatus ;
typedef  int /*<<< orphan*/  GpSolidFill ;
typedef  TYPE_1__ GpRectF ;
typedef  int /*<<< orphan*/  GpGraphics ;
typedef  int /*<<< orphan*/  GpBrush ;
typedef  int /*<<< orphan*/  ARGB ;

/* Variables and functions */
 int /*<<< orphan*/  GdipCreateFromHDC (int /*<<< orphan*/ *,int /*<<< orphan*/ **) ; 
 int /*<<< orphan*/  GdipCreateSolidFill (int /*<<< orphan*/ ,int /*<<< orphan*/ **) ; 
 int /*<<< orphan*/  GdipDeleteBrush (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  GdipDeleteGraphics (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  GdipFillRectangles (int /*<<< orphan*/ *,int /*<<< orphan*/ *,TYPE_1__*,int) ; 
 int /*<<< orphan*/ * GetDC (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  InvalidParameter ; 
 int /*<<< orphan*/  Ok ; 
 int /*<<< orphan*/  ReleaseDC (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  expect (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  hwnd ; 
 int /*<<< orphan*/  ok (int /*<<< orphan*/ ,char*) ; 

__attribute__((used)) static void test_GdipFillRectangles(void)
{
    GpStatus status;
    GpGraphics *graphics = NULL;
    GpBrush *brush = NULL;
    HDC hdc = GetDC( hwnd );
    GpRectF rects[2] = {{0,0,10,10}, {10,10,10,10}};

    ok(hdc != NULL, "Expected HDC to be initialized\n");

    status = GdipCreateFromHDC(hdc, &graphics);
    expect(Ok, status);
    ok(graphics != NULL, "Expected graphics to be initialized\n");

    status = GdipCreateSolidFill((ARGB)0xffff00ff, (GpSolidFill**)&brush);
    expect(Ok, status);
    ok(brush != NULL, "Expected brush to be initialized\n");

    status = GdipFillRectangles(NULL, brush, rects, 2);
    expect(InvalidParameter, status);

    status = GdipFillRectangles(graphics, NULL, rects, 2);
    expect(InvalidParameter, status);

    status = GdipFillRectangles(graphics, brush, NULL, 2);
    expect(InvalidParameter, status);

    status = GdipFillRectangles(graphics, brush, rects, 0);
    expect(InvalidParameter, status);

    status = GdipFillRectangles(graphics, brush, rects, -1);
    expect(InvalidParameter, status);

    status = GdipFillRectangles(graphics, brush, rects, 1);
    expect(Ok, status);

    status = GdipFillRectangles(graphics, brush, rects, 2);
    expect(Ok, status);

    GdipDeleteBrush(brush);
    GdipDeleteGraphics(graphics);

    ReleaseDC(hwnd, hdc);
}
#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct TYPE_5__ {int X; int Y; } ;
typedef  int /*<<< orphan*/ * HDC ;
typedef  int /*<<< orphan*/  GpStatus ;
typedef  int /*<<< orphan*/  GpPointF ;
typedef  TYPE_1__ GpPoint ;
typedef  int /*<<< orphan*/  GpPen ;
typedef  int /*<<< orphan*/  GpGraphics ;
typedef  int /*<<< orphan*/  ARGB ;

/* Variables and functions */
 TYPE_1__* GdipAlloc (int) ; 
 int /*<<< orphan*/  GdipCreateFromHDC (int /*<<< orphan*/ *,int /*<<< orphan*/ **) ; 
 int /*<<< orphan*/  GdipCreatePen1 (int /*<<< orphan*/ ,float,int /*<<< orphan*/ ,int /*<<< orphan*/ **) ; 
 int /*<<< orphan*/  GdipDeleteGraphics (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  GdipDeletePen (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  GdipDrawLinesI (int /*<<< orphan*/ *,int /*<<< orphan*/ *,TYPE_1__*,int) ; 
 int /*<<< orphan*/  GdipFree (TYPE_1__*) ; 
 int /*<<< orphan*/ * GetDC (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  InvalidParameter ; 
 int /*<<< orphan*/  Ok ; 
 int /*<<< orphan*/  ReleaseDC (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  UnitPixel ; 
 int /*<<< orphan*/  expect (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  hwnd ; 
 int /*<<< orphan*/  ok (int /*<<< orphan*/ ,char*) ; 

__attribute__((used)) static void test_GdipDrawLinesI(void)
{
    GpStatus status;
    GpGraphics *graphics = NULL;
    GpPen *pen = NULL;
    GpPoint *ptf = NULL;
    HDC hdc = GetDC( hwnd );

    /* make a graphics object and pen object */
    ok(hdc != NULL, "Expected HDC to be initialized\n");

    status = GdipCreateFromHDC(hdc, &graphics);
    expect(Ok, status);
    ok(graphics != NULL, "Expected graphics to be initialized\n");

    status = GdipCreatePen1((ARGB)0xffff00ff, 10.0f, UnitPixel, &pen);
    expect(Ok, status);
    ok(pen != NULL, "Expected pen to be initialized\n");

    /* make some arbitrary valid points*/
    ptf = GdipAlloc(2 * sizeof(GpPointF));

    ptf[0].X = 1;
    ptf[0].Y = 1;

    ptf[1].X = 2;
    ptf[1].Y = 2;

    /* InvalidParameter cases: null graphics, null pen, null points, count < 2*/
    status = GdipDrawLinesI(NULL, NULL, NULL, 0);
    expect(InvalidParameter, status);

    status = GdipDrawLinesI(graphics, pen, ptf, 0);
    expect(InvalidParameter, status);

    status = GdipDrawLinesI(graphics, NULL, ptf, 2);
    expect(InvalidParameter, status);

    status = GdipDrawLinesI(NULL, pen, ptf, 2);
    expect(InvalidParameter, status);

    /* successful case */
    status = GdipDrawLinesI(graphics, pen, ptf, 2);
    expect(Ok, status);

    GdipFree(ptf);
    GdipDeletePen(pen);
    GdipDeleteGraphics(graphics);

    ReleaseDC(hwnd, hdc);
}
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
typedef  int WrapMode ;
struct TYPE_3__ {int member_0; int member_1; int member_2; int member_3; } ;
typedef  int /*<<< orphan*/  GpStatus ;
typedef  TYPE_1__ GpRectF ;
typedef  int /*<<< orphan*/  GpLineGradient ;
typedef  int /*<<< orphan*/  GpBrush ;

/* Variables and functions */
 int /*<<< orphan*/  FALSE ; 
 int /*<<< orphan*/  GdipCreateLineBrushFromRectWithAngle (TYPE_1__*,int,int,int,int /*<<< orphan*/ ,int,int /*<<< orphan*/ **) ; 
 int /*<<< orphan*/  GdipDeleteBrush (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  InvalidParameter ; 
 int /*<<< orphan*/  Ok ; 
 int /*<<< orphan*/  OutOfMemory ; 
 int /*<<< orphan*/  TRUE ; 
 int WrapModeClamp ; 
 int WrapModeTile ; 
 int WrapModeTileFlipX ; 
 int WrapModeTileFlipXY ; 
 int /*<<< orphan*/  expect (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void test_createLineBrushFromRectWithAngle(void)
{
    GpStatus status;
    GpLineGradient *brush;
    GpRectF rect1 = { 1, 3, 1, 2 };
    GpRectF rect2 = { 1, 3, -1, -2 };
    GpRectF rect3 = { 1, 3, 0, 1 };
    GpRectF rect4 = { 1, 3, 1, 0 };

    status = GdipCreateLineBrushFromRectWithAngle(&rect1, 10, 11, 0, TRUE, WrapModeTile, &brush);
    expect(Ok, status);
    GdipDeleteBrush((GpBrush *) brush);

    status = GdipCreateLineBrushFromRectWithAngle(&rect2, 10, 11, 135, TRUE, (WrapMode)(WrapModeTile - 1), &brush);
    expect(Ok, status);
    GdipDeleteBrush((GpBrush *) brush);

    status = GdipCreateLineBrushFromRectWithAngle(&rect2, 10, 11, -225, FALSE, (WrapMode)(WrapModeTile - 1), &brush);
    expect(Ok, status);
    GdipDeleteBrush((GpBrush *) brush);

    status = GdipCreateLineBrushFromRectWithAngle(&rect1, 10, 11, 405, TRUE, (WrapMode)(WrapModeClamp + 1), &brush);
    expect(Ok, status);
    GdipDeleteBrush((GpBrush *) brush);

    status = GdipCreateLineBrushFromRectWithAngle(&rect1, 10, 11, 45, FALSE, (WrapMode)(WrapModeClamp + 1), &brush);
    expect(Ok, status);
    GdipDeleteBrush((GpBrush *) brush);

    status = GdipCreateLineBrushFromRectWithAngle(&rect1, 10, 11, 90, TRUE, WrapModeTileFlipX, &brush);
    expect(Ok, status);

    status = GdipCreateLineBrushFromRectWithAngle(NULL, 10, 11, 90, TRUE, WrapModeTile, &brush);
    expect(InvalidParameter, status);

    status = GdipCreateLineBrushFromRectWithAngle(&rect3, 10, 11, 90, TRUE, WrapModeTileFlipXY, &brush);
    expect(OutOfMemory, status);

    status = GdipCreateLineBrushFromRectWithAngle(&rect4, 10, 11, 90, TRUE, WrapModeTileFlipXY, &brush);
    expect(OutOfMemory, status);

    status = GdipCreateLineBrushFromRectWithAngle(&rect3, 10, 11, 90, TRUE, WrapModeTileFlipXY, NULL);
    expect(InvalidParameter, status);

    status = GdipCreateLineBrushFromRectWithAngle(&rect4, 10, 11, 90, TRUE, WrapModeTileFlipXY, NULL);
    expect(InvalidParameter, status);

    status = GdipCreateLineBrushFromRectWithAngle(&rect3, 10, 11, 90, TRUE, WrapModeClamp, &brush);
    expect(InvalidParameter, status);

    status = GdipCreateLineBrushFromRectWithAngle(&rect4, 10, 11, 90, TRUE, WrapModeClamp, &brush);
    expect(InvalidParameter, status);

    status = GdipCreateLineBrushFromRectWithAngle(&rect1, 10, 11, 90, TRUE, WrapModeClamp, &brush);
    expect(InvalidParameter, status);

    status = GdipCreateLineBrushFromRectWithAngle(&rect1, 10, 11, 90, TRUE, WrapModeTile, NULL);
    expect(InvalidParameter, status);

    GdipDeleteBrush((GpBrush *) brush);
}
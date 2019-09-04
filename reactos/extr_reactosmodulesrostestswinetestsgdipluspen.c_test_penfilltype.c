#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_4__ {double X; double Y; } ;
typedef  int /*<<< orphan*/  GpStatus ;
typedef  int /*<<< orphan*/  GpSolidFill ;
typedef  TYPE_1__ GpPointF ;
typedef  int /*<<< orphan*/  GpPenType ;
typedef  int /*<<< orphan*/  GpPen ;
typedef  int /*<<< orphan*/  GpLineGradient ;
typedef  int /*<<< orphan*/  GpBrush ;
typedef  int /*<<< orphan*/  ARGB ;

/* Variables and functions */
 int /*<<< orphan*/  GdipCreateLineBrush (TYPE_1__*,TYPE_1__*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ **) ; 
 int /*<<< orphan*/  GdipCreatePen1 (int /*<<< orphan*/ ,float,int /*<<< orphan*/ ,int /*<<< orphan*/ **) ; 
 int /*<<< orphan*/  GdipCreatePen2 (int /*<<< orphan*/ *,float,int /*<<< orphan*/ ,int /*<<< orphan*/ **) ; 
 int /*<<< orphan*/  GdipCreateSolidFill (int /*<<< orphan*/ ,int /*<<< orphan*/ **) ; 
 int /*<<< orphan*/  GdipDeleteBrush (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  GdipDeletePen (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  GdipGetPenFillType (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  InvalidParameter ; 
 int /*<<< orphan*/  Ok ; 
 int /*<<< orphan*/  PenTypeLinearGradient ; 
 int /*<<< orphan*/  PenTypeSolidColor ; 
 int /*<<< orphan*/  UnitPixel ; 
 int /*<<< orphan*/  WrapModeTile ; 
 int /*<<< orphan*/  expect (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void test_penfilltype(void)
{
    GpPen *pen;
    GpSolidFill *solid;
    GpLineGradient *line;
    GpPointF a, b;
    GpStatus status;
    GpPenType type;

    /* NULL */
    status = GdipGetPenFillType(NULL, NULL);
    expect(InvalidParameter, status);

    status = GdipCreatePen1((ARGB)0xffff00ff, 10.0f, UnitPixel, &pen);
    expect(Ok, status);
    status = GdipGetPenFillType(pen, NULL);
    expect(InvalidParameter, status);

    /* created with GdipCreatePen1() */
    status = GdipGetPenFillType(pen, &type);
    expect(Ok, status);
    expect(PenTypeSolidColor, type);
    GdipDeletePen(pen);

    /* based on SolidBrush */
    status = GdipCreateSolidFill((ARGB)0xffff00ff, &solid);
    expect(Ok, status);
    status = GdipCreatePen2((GpBrush*)solid, 10.0f, UnitPixel, &pen);
    expect(Ok, status);
    status = GdipGetPenFillType(pen, &type);
    expect(Ok, status);
    expect(PenTypeSolidColor, type);
    GdipDeletePen(pen);
    GdipDeleteBrush((GpBrush*)solid);

    /* based on LinearGradientBrush */
    a.X = a.Y = 0.0;
    b.X = b.Y = 10.0;
    status = GdipCreateLineBrush(&a, &b, (ARGB)0xffff00ff, (ARGB)0xffff0000,
                                 WrapModeTile, &line);
    expect(Ok, status);
    status = GdipCreatePen2((GpBrush*)line, 10.0f, UnitPixel, &pen);
    expect(Ok, status);
    status = GdipGetPenFillType(pen, &type);
    expect(Ok, status);
    expect(PenTypeLinearGradient, type);
    GdipDeletePen(pen);
    GdipDeleteBrush((GpBrush*)line);
}
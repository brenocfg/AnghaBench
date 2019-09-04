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
typedef  scalar_t__ GpStatus ;
typedef  int /*<<< orphan*/  GpSolidFill ;
typedef  int /*<<< orphan*/  GpPen ;
typedef  scalar_t__ GpBrushType ;
typedef  int /*<<< orphan*/  GpBrush ;
typedef  scalar_t__ ARGB ;

/* Variables and functions */
 int BrushTypeSolidColor ; 
 int /*<<< orphan*/  GdipCreatePen1 (int,double,int /*<<< orphan*/ ,int /*<<< orphan*/ **) ; 
 int /*<<< orphan*/  GdipCreateSolidFill (int,int /*<<< orphan*/ **) ; 
 int /*<<< orphan*/  GdipDeleteBrush (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  GdipDeletePen (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  GdipGetBrushType (int /*<<< orphan*/ *,scalar_t__*) ; 
 scalar_t__ GdipGetPenBrushFill (int /*<<< orphan*/ *,int /*<<< orphan*/ **) ; 
 int /*<<< orphan*/  GdipGetPenColor (int /*<<< orphan*/ *,scalar_t__*) ; 
 int /*<<< orphan*/  GdipGetSolidFillColor (int /*<<< orphan*/ *,scalar_t__*) ; 
 scalar_t__ GdipSetPenBrushFill (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  GdipSetSolidFillColor (int /*<<< orphan*/ *,int) ; 
 int InvalidParameter ; 
 int Ok ; 
 int /*<<< orphan*/  UnitWorld ; 
 int /*<<< orphan*/  expect (int,scalar_t__) ; 
 int /*<<< orphan*/  ok (int,char*) ; 

__attribute__((used)) static void test_brushfill(void)
{
    GpStatus status;
    GpPen *pen;
    GpBrush *brush, *brush2;
    GpBrushType type;
    ARGB color = 0;

    /* default solid */
    GdipCreatePen1(0xdeadbeef, 4.5, UnitWorld, &pen);
    status = GdipGetPenBrushFill(pen, &brush);
    expect(Ok, status);
    GdipGetBrushType(brush, &type);
    expect(BrushTypeSolidColor, type);
    GdipGetPenColor(pen, &color);
    expect(0xdeadbeef, color);
    GdipDeleteBrush(brush);

    /* color controlled by brush */
    GdipCreateSolidFill(0xabaddeed, (GpSolidFill**)&brush);
    status = GdipSetPenBrushFill(pen, brush);
    expect(Ok, status);
    GdipGetPenColor(pen, &color);
    expect(0xabaddeed, color);
    GdipDeleteBrush(brush);
    color = 0;

    /* get returns a clone, not a reference */
    GdipGetPenBrushFill(pen, &brush);
    GdipSetSolidFillColor((GpSolidFill*)brush, 0xbeadfeed);
    GdipGetPenBrushFill(pen, &brush2);
    ok(brush != brush2, "Expected to get a clone, not a copy of the reference\n");
    GdipGetSolidFillColor((GpSolidFill*)brush2, &color);
    expect(0xabaddeed, color);
    GdipDeleteBrush(brush);
    GdipDeleteBrush(brush2);

    /* brush cannot be NULL */
    status = GdipSetPenBrushFill(pen, NULL);
    expect(InvalidParameter, status);

    GdipDeletePen(pen);
}
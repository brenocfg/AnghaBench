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
typedef  int /*<<< orphan*/  Unit ;
typedef  int REAL ;
typedef  int /*<<< orphan*/  GpStatus ;
typedef  int /*<<< orphan*/  GpFontFamily ;
typedef  int /*<<< orphan*/  GpFont ;

/* Variables and functions */
 int /*<<< orphan*/  FontStyleRegular ; 
 int /*<<< orphan*/  GdipCreateFont (int /*<<< orphan*/ *,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ **) ; 
 int /*<<< orphan*/  GdipCreateFontFamilyFromName (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ **) ; 
 int /*<<< orphan*/  GdipDeleteFont (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  GdipDeleteFontFamily (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  GdipGetFontHeightGivenDPI (int /*<<< orphan*/ *,int,int*) ; 
 int /*<<< orphan*/  GdipGetFontUnit (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  InvalidParameter ; 
 int /*<<< orphan*/  Ok ; 
 int /*<<< orphan*/  Tahoma ; 
 int /*<<< orphan*/  UnitDocument ; 
 int /*<<< orphan*/  UnitInch ; 
 int /*<<< orphan*/  UnitMillimeter ; 
 int /*<<< orphan*/  UnitPixel ; 
 int /*<<< orphan*/  UnitPoint ; 
 int /*<<< orphan*/  UnitWorld ; 
 int /*<<< orphan*/  expect (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  expectf (double,int) ; 

__attribute__((used)) static void test_heightgivendpi(void)
{
    GpStatus stat;
    GpFont* font = NULL;
    GpFontFamily* fontfamily = NULL;
    REAL height;
    Unit unit;

    stat = GdipCreateFontFamilyFromName(Tahoma, NULL, &fontfamily);
    expect(Ok, stat);

    stat = GdipCreateFont(fontfamily, 30, FontStyleRegular, UnitPixel, &font);
    expect(Ok, stat);

    stat = GdipGetFontHeightGivenDPI(NULL, 96, &height);
    expect(InvalidParameter, stat);

    stat = GdipGetFontHeightGivenDPI(font, 96, NULL);
    expect(InvalidParameter, stat);

    stat = GdipGetFontHeightGivenDPI(font, 96, &height);
    expect(Ok, stat);
    expectf(36.210938, height);
    GdipDeleteFont(font);

    height = 12345;
    stat = GdipCreateFont(fontfamily, 30, FontStyleRegular, UnitWorld, &font);
    expect(Ok, stat);

    stat = GdipGetFontUnit(font, &unit);
    expect(Ok, stat);
    expect(UnitWorld, unit);

    stat = GdipGetFontHeightGivenDPI(font, 96, &height);
    expect(Ok, stat);
    expectf(36.210938, height);
    GdipDeleteFont(font);

    height = 12345;
    stat = GdipCreateFont(fontfamily, 30, FontStyleRegular, UnitPoint, &font);
    expect(Ok, stat);
    stat = GdipGetFontHeightGivenDPI(font, 96, &height);
    expect(Ok, stat);
    expectf(48.281250, height);
    GdipDeleteFont(font);

    height = 12345;
    stat = GdipCreateFont(fontfamily, 30, FontStyleRegular, UnitInch, &font);
    expect(Ok, stat);

    stat = GdipGetFontUnit(font, &unit);
    expect(Ok, stat);
    expect(UnitInch, unit);

    stat = GdipGetFontHeightGivenDPI(font, 96, &height);
    expect(Ok, stat);
    expectf(3476.250000, height);
    GdipDeleteFont(font);

    height = 12345;
    stat = GdipCreateFont(fontfamily, 30, FontStyleRegular, UnitDocument, &font);
    expect(Ok, stat);

    stat = GdipGetFontUnit(font, &unit);
    expect(Ok, stat);
    expect(UnitDocument, unit);

    stat = GdipGetFontHeightGivenDPI(font, 96, &height);
    expect(Ok, stat);
    expectf(11.587500, height);
    GdipDeleteFont(font);

    height = 12345;
    stat = GdipCreateFont(fontfamily, 30, FontStyleRegular, UnitMillimeter, &font);
    expect(Ok, stat);

    stat = GdipGetFontUnit(font, &unit);
    expect(Ok, stat);
    expect(UnitMillimeter, unit);

    stat = GdipGetFontHeightGivenDPI(font, 96, &height);
    expect(Ok, stat);
    expectf(136.860245, height);
    GdipDeleteFont(font);

    GdipDeleteFontFamily(fontfamily);
}
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
typedef  int /*<<< orphan*/  WCHAR ;
typedef  scalar_t__ Unit ;
typedef  scalar_t__ UINT ;
typedef  int REAL ;
typedef  scalar_t__ GpStatus ;
typedef  int /*<<< orphan*/  GpFontFamily ;
typedef  int /*<<< orphan*/  GpFont ;

/* Variables and functions */
 scalar_t__ FontFamilyNotFound ; 
 int /*<<< orphan*/  FontStyleRegular ; 
 scalar_t__ GdipCreateFont (int /*<<< orphan*/ *,int,int /*<<< orphan*/ ,scalar_t__,int /*<<< orphan*/ **) ; 
 scalar_t__ GdipCreateFontFamilyFromName (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ **) ; 
 scalar_t__ GdipDeleteFont (int /*<<< orphan*/ *) ; 
 scalar_t__ GdipDeleteFontFamily (int /*<<< orphan*/ *) ; 
 scalar_t__ GdipGetFamily (int /*<<< orphan*/ *,int /*<<< orphan*/ **) ; 
 scalar_t__ GdipGetFamilyName (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  GdipGetFontSize (int /*<<< orphan*/ *,int*) ; 
 scalar_t__ GdipGetFontUnit (int /*<<< orphan*/ *,scalar_t__*) ; 
 scalar_t__ InvalidParameter ; 
 int LF_FACESIZE ; 
 scalar_t__ Ok ; 
 int /*<<< orphan*/  Tahoma ; 
 scalar_t__ UnitDisplay ; 
 scalar_t__ UnitMillimeter ; 
 scalar_t__ UnitPoint ; 
 scalar_t__ UnitWorld ; 
 int /*<<< orphan*/  expect (scalar_t__,scalar_t__) ; 
 scalar_t__ lstrcmpiW (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  nonexistent ; 
 int /*<<< orphan*/  ok (int,char*,scalar_t__,...) ; 
 scalar_t__ wine_dbgstr_w (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void test_createfont(void)
{
    GpFontFamily* fontfamily = NULL, *fontfamily2;
    GpFont* font = NULL;
    GpStatus stat;
    Unit unit;
    UINT i;
    REAL size;
    WCHAR familyname[LF_FACESIZE];

    stat = GdipCreateFontFamilyFromName(nonexistent, NULL, &fontfamily);
    expect (FontFamilyNotFound, stat);
    stat = GdipDeleteFont(font);
    expect (InvalidParameter, stat);
    stat = GdipCreateFontFamilyFromName(Tahoma, NULL, &fontfamily);
    expect (Ok, stat);
    stat = GdipCreateFont(fontfamily, 12, FontStyleRegular, UnitPoint, &font);
    expect (Ok, stat);
    stat = GdipGetFontUnit (font, &unit);
    expect (Ok, stat);
    expect (UnitPoint, unit);

    stat = GdipGetFamily(font, &fontfamily2);
    expect(Ok, stat);
    stat = GdipGetFamilyName(fontfamily2, familyname, 0);
    expect(Ok, stat);
    ok (lstrcmpiW(Tahoma, familyname) == 0, "Expected Tahoma, got %s\n",
            wine_dbgstr_w(familyname));
    stat = GdipDeleteFontFamily(fontfamily2);
    expect(Ok, stat);

    /* Test to see if returned size is based on unit (it's not) */
    GdipGetFontSize(font, &size);
    ok (size == 12, "Expected 12, got %f\n", size);
    GdipDeleteFont(font);

    /* Make sure everything is converted correctly for all Units */
    for (i = UnitWorld; i <=UnitMillimeter; i++)
    {
        if (i == UnitDisplay) continue; /* Crashes WindowsXP, wtf? */
        stat = GdipCreateFont(fontfamily, 24, FontStyleRegular, i, &font);
        expect(Ok, stat);
        GdipGetFontSize (font, &size);
        ok (size == 24, "Expected 24, got %f (with unit: %d)\n", size, i);
        stat = GdipGetFontUnit (font, &unit);
        ok (stat == Ok, "Failed to get font unit, %d.\n", stat);
        expect (i, unit);
        GdipDeleteFont(font);
    }

    GdipDeleteFontFamily(fontfamily);
}
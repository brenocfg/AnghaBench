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
typedef  int UINT16 ;
typedef  scalar_t__ GpStatus ;
typedef  int /*<<< orphan*/  GpFontFamily ;

/* Variables and functions */
 scalar_t__ FontFamilyNotFound ; 
 int /*<<< orphan*/  FontStyleRegular ; 
 scalar_t__ GdipCreateFontFamilyFromName (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ **) ; 
 int /*<<< orphan*/  GdipDeleteFontFamily (int /*<<< orphan*/ *) ; 
 scalar_t__ GdipGetCellAscent (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int*) ; 
 scalar_t__ GdipGetCellDescent (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int*) ; 
 scalar_t__ GdipGetEmHeight (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int*) ; 
 scalar_t__ GdipGetLineSpacing (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int*) ; 
 int /*<<< orphan*/  Ok ; 
 int /*<<< orphan*/  Tahoma ; 
 int /*<<< orphan*/  TimesNewRoman ; 
 int /*<<< orphan*/  expect (int /*<<< orphan*/ ,scalar_t__) ; 
 int /*<<< orphan*/  ok (int,char*,int) ; 
 int /*<<< orphan*/  skip (char*) ; 

__attribute__((used)) static void test_fontfamily_properties (void)
{
    GpFontFamily* FontFamily = NULL;
    GpStatus stat;
    UINT16 result = 0;

    stat = GdipCreateFontFamilyFromName(Tahoma, NULL, &FontFamily);
    expect(Ok, stat);

    stat = GdipGetLineSpacing(FontFamily, FontStyleRegular, &result);
    expect(Ok, stat);
    ok (result == 2472, "Expected 2472, got %d\n", result);
    result = 0;
    stat = GdipGetEmHeight(FontFamily, FontStyleRegular, &result);
    expect(Ok, stat);
    ok(result == 2048, "Expected 2048, got %d\n", result);
    result = 0;
    stat = GdipGetCellAscent(FontFamily, FontStyleRegular, &result);
    expect(Ok, stat);
    ok(result == 2049, "Expected 2049, got %d\n", result);
    result = 0;
    stat = GdipGetCellDescent(FontFamily, FontStyleRegular, &result);
    expect(Ok, stat);
    ok(result == 423, "Expected 423, got %d\n", result);
    GdipDeleteFontFamily(FontFamily);

    stat = GdipCreateFontFamilyFromName(TimesNewRoman, NULL, &FontFamily);
    if(stat == FontFamilyNotFound)
        skip("Times New Roman not installed\n");
    else
    {
        result = 0;
        stat = GdipGetLineSpacing(FontFamily, FontStyleRegular, &result);
        expect(Ok, stat);
        ok(result == 2355, "Expected 2355, got %d\n", result);
        result = 0;
        stat = GdipGetEmHeight(FontFamily, FontStyleRegular, &result);
        expect(Ok, stat);
        ok(result == 2048, "Expected 2048, got %d\n", result);
        result = 0;
        stat = GdipGetCellAscent(FontFamily, FontStyleRegular, &result);
        expect(Ok, stat);
        ok(result == 1825, "Expected 1825, got %d\n", result);
        result = 0;
        stat = GdipGetCellDescent(FontFamily, FontStyleRegular, &result);
        expect(Ok, stat);
        ok(result == 443, "Expected 443 got %d\n", result);
        GdipDeleteFontFamily(FontFamily);
    }
}
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
typedef  scalar_t__ WCHAR ;
typedef  scalar_t__ GpStatus ;
typedef  int /*<<< orphan*/  GpFontFamily ;
typedef  int /*<<< orphan*/  GpFont ;

/* Variables and functions */
 int /*<<< orphan*/  FontStyleRegular ; 
 scalar_t__ GdipCreateFont (int /*<<< orphan*/ *,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ **) ; 
 scalar_t__ GdipDeleteFont (int /*<<< orphan*/ *) ; 
 scalar_t__ GdipDeleteFontFamily (int /*<<< orphan*/ *) ; 
 scalar_t__ GdipGetFamilyName (int /*<<< orphan*/ *,scalar_t__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  LANG_NEUTRAL ; 
 scalar_t__ Ok ; 
 int /*<<< orphan*/  UnitPixel ; 
 int /*<<< orphan*/  ok (int,char*,char const*,scalar_t__) ; 

__attribute__((used)) static void check_family(const char* context, GpFontFamily *family, WCHAR *name)
{
    GpStatus stat;
    GpFont* font;

    *name = 0;
    stat = GdipGetFamilyName(family, name, LANG_NEUTRAL);
    ok(stat == Ok, "could not get the %s family name: %.8x\n", context, stat);

    stat = GdipCreateFont(family, 12, FontStyleRegular, UnitPixel, &font);
    ok(stat == Ok, "could not create a font for the %s family: %.8x\n", context, stat);
    if (stat == Ok)
    {
        stat = GdipDeleteFont(font);
        ok(stat == Ok, "could not delete the %s family font: %.8x\n", context, stat);
    }

    stat = GdipDeleteFontFamily(family);
    ok(stat == Ok, "could not delete the %s family: %.8x\n", context, stat);
}
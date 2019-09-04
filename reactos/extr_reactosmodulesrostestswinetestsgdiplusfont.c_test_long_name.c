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
typedef  char WCHAR ;
typedef  int INT ;
typedef  int GpStatus ;
typedef  int /*<<< orphan*/  GpFontFamily ;
typedef  int /*<<< orphan*/  GpFontCollection ;
typedef  int /*<<< orphan*/  GpFont ;

/* Variables and functions */
 int /*<<< orphan*/  DELETE_FONTFILE (char*) ; 
 int /*<<< orphan*/  FontStyleRegular ; 
 int GdipCreateFont (int /*<<< orphan*/ *,double,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ **) ; 
 int GdipDeleteFont (int /*<<< orphan*/ *) ; 
 int GdipDeletePrivateFontCollection (int /*<<< orphan*/ **) ; 
 int GdipGetFamilyName (int /*<<< orphan*/ *,char*,int /*<<< orphan*/ ) ; 
 int GdipGetFontCollectionFamilyCount (int /*<<< orphan*/ *,int*) ; 
 int GdipGetFontCollectionFamilyList (int /*<<< orphan*/ *,int,int /*<<< orphan*/ **,int*) ; 
 int GdipNewPrivateFontCollection (int /*<<< orphan*/ **) ; 
 int GdipPrivateAddFontFile (int /*<<< orphan*/ *,char*) ; 
 int /*<<< orphan*/  LANG_NEUTRAL ; 
 int LF_FACESIZE ; 
 int MAX_PATH ; 
 int Ok ; 
 int /*<<< orphan*/  UnitPixel ; 
 int /*<<< orphan*/  create_testfontfile (char const*,int,char*) ; 
 int /*<<< orphan*/  ok (int,char*,int) ; 

__attribute__((used)) static void test_long_name(void)
{
    WCHAR path[MAX_PATH];
    static const WCHAR path_longname[] = {'w','i','n','e','_','l','o','n','g','n','a','m','e','.','t','t','f',0};
    GpStatus stat;
    GpFontCollection *fonts;
    INT num_families;
    GpFontFamily *family;
    WCHAR family_name[LF_FACESIZE];
    GpFont *font;

    stat = GdipNewPrivateFontCollection(&fonts);
    ok(stat == Ok, "GdipNewPrivateFontCollection failed: %d\n", stat);

    create_testfontfile(path_longname, 1, path);

    stat = GdipPrivateAddFontFile(fonts, path);
    ok(stat == Ok, "GdipPrivateAddFontFile failed: %d\n", stat);

    stat = GdipGetFontCollectionFamilyCount(fonts, &num_families);
    ok(stat == Ok, "GdipGetFontCollectionFamilyCount failed: %d\n", stat);

    ok(num_families == 1, "expected num_families to be 1, got %d\n", num_families);

    stat = GdipGetFontCollectionFamilyList(fonts, num_families, &family, &num_families);
    ok(stat == Ok, "GdipGetFontCollectionFamilyList failed: %d\n", stat);

    stat = GdipGetFamilyName(family, family_name, LANG_NEUTRAL);
    ok(stat == Ok, "GdipGetFamilyName failed: %d\n", stat);

    stat = GdipCreateFont(family, 256.0, FontStyleRegular, UnitPixel, &font);
    ok(stat == Ok, "GdipCreateFont failed: %d\n", stat);

    /* Cleanup */

    stat = GdipDeleteFont(font);
    ok(stat == Ok, "GdipDeleteFont failed: %d\n", stat);

    stat = GdipDeletePrivateFontCollection(&fonts);
    ok(stat == Ok, "GdipDeletePrivateFontCollection failed: %d\n", stat);

    DELETE_FONTFILE(path);
}
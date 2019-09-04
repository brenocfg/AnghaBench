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
typedef  scalar_t__ GpStatus ;
typedef  int /*<<< orphan*/  GpFontFamily ;

/* Variables and functions */
 scalar_t__ FontFamilyNotFound ; 
 scalar_t__ GdipGetGenericFontFamilyMonospace (int /*<<< orphan*/ **) ; 
 scalar_t__ GdipGetGenericFontFamilySansSerif (int /*<<< orphan*/ **) ; 
 scalar_t__ GdipGetGenericFontFamilySerif (int /*<<< orphan*/ **) ; 
 int LF_FACESIZE ; 
 int /*<<< orphan*/  Ok ; 
 int /*<<< orphan*/  check_family (char*,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  expect (int /*<<< orphan*/ ,scalar_t__) ; 
 scalar_t__ lstrcmpiW (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  ok (int,char*,int /*<<< orphan*/ ) ; 
 scalar_t__ strcmp (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  trace (char*) ; 
 int /*<<< orphan*/  wine_dbgstr_w (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  winetest_platform ; 

__attribute__((used)) static void test_getgenerics (void)
{
    GpStatus stat;
    GpFontFamily *family;
    WCHAR sansname[LF_FACESIZE], serifname[LF_FACESIZE], mononame[LF_FACESIZE];
    int missingfonts = 0;

    stat = GdipGetGenericFontFamilySansSerif(&family);
    expect (Ok, stat);
    if (stat == FontFamilyNotFound)
        missingfonts = 1;
    else
        check_family("Sans Serif", family, sansname);

    stat = GdipGetGenericFontFamilySerif(&family);
    expect (Ok, stat);
    if (stat == FontFamilyNotFound)
        missingfonts = 1;
    else
        check_family("Serif", family, serifname);

    stat = GdipGetGenericFontFamilyMonospace(&family);
    expect (Ok, stat);
    if (stat == FontFamilyNotFound)
        missingfonts = 1;
    else
        check_family("Monospace", family, mononame);

    if (missingfonts && strcmp(winetest_platform, "wine") == 0)
        trace("You may need to install either the Microsoft Web Fonts or the Liberation Fonts\n");

    /* Check that the family names are all different */
    ok(lstrcmpiW(sansname, serifname) != 0, "Sans Serif and Serif families should be different: %s\n", wine_dbgstr_w(sansname));
    ok(lstrcmpiW(sansname, mononame) != 0, "Sans Serif and Monospace families should be different: %s\n", wine_dbgstr_w(sansname));
    ok(lstrcmpiW(serifname, mononame) != 0, "Serif and Monospace families should be different: %s\n", wine_dbgstr_w(serifname));
}
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
typedef  int /*<<< orphan*/  itsName ;
typedef  int /*<<< orphan*/  WCHAR ;
typedef  scalar_t__ GpStatus ;
typedef  int /*<<< orphan*/  GpFontFamily ;

/* Variables and functions */
 scalar_t__ FontFamilyNotFound ; 
 scalar_t__ GdipCloneFontFamily (int /*<<< orphan*/ *,int /*<<< orphan*/ **) ; 
 scalar_t__ GdipCreateFontFamilyFromName (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ **) ; 
 int /*<<< orphan*/  GdipDeleteFontFamily (int /*<<< orphan*/ *) ; 
 scalar_t__ GdipGetFamilyName (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 scalar_t__ InvalidParameter ; 
 int /*<<< orphan*/  LANG_NEUTRAL ; 
 int LF_FACESIZE ; 
 int /*<<< orphan*/  MSSansSerif ; 
 scalar_t__ Ok ; 
 int /*<<< orphan*/  Tahoma ; 
 int /*<<< orphan*/  ZeroMemory (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  expect (scalar_t__,scalar_t__) ; 
 scalar_t__ lstrcmpiW (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  nonexistent ; 

__attribute__((used)) static void test_fontfamily (void)
{
    GpFontFamily *family, *clonedFontFamily;
    WCHAR itsName[LF_FACESIZE];
    GpStatus stat;

    /* FontFamily cannot be NULL */
    stat = GdipCreateFontFamilyFromName (Tahoma , NULL, NULL);
    expect (InvalidParameter, stat);

    /* FontFamily must be able to actually find the family.
     * If it can't, any subsequent calls should fail.
     */
    stat = GdipCreateFontFamilyFromName (nonexistent, NULL, &family);
    expect (FontFamilyNotFound, stat);

    /* Bitmap fonts are not found */
    stat = GdipCreateFontFamilyFromName (MSSansSerif, NULL, &family);
    expect (FontFamilyNotFound, stat);
    if(stat == Ok) GdipDeleteFontFamily(family);

    stat = GdipCreateFontFamilyFromName (Tahoma, NULL, &family);
    expect (Ok, stat);

    stat = GdipGetFamilyName (family, itsName, LANG_NEUTRAL);
    expect (Ok, stat);
    expect (0, lstrcmpiW(itsName, Tahoma));

    if (0)
    {
        /* Crashes on Windows XP SP2, Vista, and so Wine as well */
        stat = GdipGetFamilyName (family, NULL, LANG_NEUTRAL);
        expect (Ok, stat);
    }

    /* Make sure we don't read old data */
    ZeroMemory (itsName, sizeof(itsName));
    stat = GdipCloneFontFamily(family, &clonedFontFamily);
    expect (Ok, stat);
    GdipDeleteFontFamily(family);
    stat = GdipGetFamilyName(clonedFontFamily, itsName, LANG_NEUTRAL);
    expect(Ok, stat);
    expect(0, lstrcmpiW(itsName, Tahoma));

    GdipDeleteFontFamily(clonedFontFamily);
}
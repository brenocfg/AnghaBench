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

/* Variables and functions */
 int /*<<< orphan*/  CreateCurves () ; 
 int /*<<< orphan*/  DbgThread () ; 
 int /*<<< orphan*/  INTENT_ABSOLUTE_COLORIMETRIC ; 
 int /*<<< orphan*/  INTENT_PERCEPTUAL ; 
 int /*<<< orphan*/  INTENT_RELATIVE_COLORIMETRIC ; 
 int /*<<< orphan*/  SpeedTest16bits (char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  SpeedTest16bitsCMYK (char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  SpeedTest16bitsGray (char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  SpeedTest32bits (char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  SpeedTest32bitsCMYK (char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  SpeedTest32bitsGray (char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  SpeedTest8bits (char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  SpeedTest8bitsCMYK (char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  SpeedTest8bitsGray (char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  cmsOpenProfileFromFile (int /*<<< orphan*/ ,char*,char*) ; 
 int /*<<< orphan*/  fflush (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  printf (char*) ; 
 int /*<<< orphan*/  stdout ; 

__attribute__((used)) static
void SpeedTest(void)
{
    printf("\n\nP E R F O R M A N C E   T E S T S\n");
    printf(    "=================================\n\n");
    fflush(stdout);

    SpeedTest8bits("8 bits on CLUT profiles",
        cmsOpenProfileFromFile(DbgThread(), "test5.icc", "r"),
        cmsOpenProfileFromFile(DbgThread(), "test3.icc", "r"),
        INTENT_PERCEPTUAL);

    SpeedTest16bits("16 bits on CLUT profiles",
        cmsOpenProfileFromFile(DbgThread(), "test5.icc", "r"),
        cmsOpenProfileFromFile(DbgThread(), "test3.icc", "r"), INTENT_PERCEPTUAL);

    SpeedTest32bits("32 bits on CLUT profiles",
        cmsOpenProfileFromFile(DbgThread(), "test5.icc", "r"),
        cmsOpenProfileFromFile(DbgThread(), "test3.icc", "r"), INTENT_PERCEPTUAL);

    printf("\n");

    // - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

    SpeedTest8bits("8 bits on Matrix-Shaper profiles",
        cmsOpenProfileFromFile(DbgThread(), "test5.icc", "r"),
        cmsOpenProfileFromFile(DbgThread(), "aRGBlcms2.icc", "r"),
        INTENT_PERCEPTUAL);

    SpeedTest16bits("16 bits on Matrix-Shaper profiles",
       cmsOpenProfileFromFile(DbgThread(), "test5.icc", "r"),
        cmsOpenProfileFromFile(DbgThread(), "aRGBlcms2.icc", "r"),
        INTENT_PERCEPTUAL);

    SpeedTest32bits("32 bits on Matrix-Shaper profiles",
       cmsOpenProfileFromFile(DbgThread(), "test5.icc", "r"),
        cmsOpenProfileFromFile(DbgThread(), "aRGBlcms2.icc", "r"),
        INTENT_PERCEPTUAL);

    printf("\n");

    // - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

    SpeedTest8bits("8 bits on SAME Matrix-Shaper profiles",
        cmsOpenProfileFromFile(DbgThread(), "test5.icc", "r"),
        cmsOpenProfileFromFile(DbgThread(), "test5.icc", "r"),
        INTENT_PERCEPTUAL);

    SpeedTest16bits("16 bits on SAME Matrix-Shaper profiles",
        cmsOpenProfileFromFile(DbgThread(), "aRGBlcms2.icc", "r"),
        cmsOpenProfileFromFile(DbgThread(), "aRGBlcms2.icc", "r"),
        INTENT_PERCEPTUAL);

    SpeedTest32bits("32 bits on SAME Matrix-Shaper profiles",
        cmsOpenProfileFromFile(DbgThread(), "aRGBlcms2.icc", "r"),
        cmsOpenProfileFromFile(DbgThread(), "aRGBlcms2.icc", "r"),
        INTENT_PERCEPTUAL);

    printf("\n");

    // - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

    SpeedTest8bits("8 bits on Matrix-Shaper profiles (AbsCol)",
       cmsOpenProfileFromFile(DbgThread(), "test5.icc", "r"),
       cmsOpenProfileFromFile(DbgThread(), "aRGBlcms2.icc", "r"),
        INTENT_ABSOLUTE_COLORIMETRIC);

    SpeedTest16bits("16 bits on Matrix-Shaper profiles (AbsCol)",
       cmsOpenProfileFromFile(DbgThread(), "test5.icc", "r"),
       cmsOpenProfileFromFile(DbgThread(), "aRGBlcms2.icc", "r"),
        INTENT_ABSOLUTE_COLORIMETRIC);

    SpeedTest32bits("32 bits on Matrix-Shaper profiles (AbsCol)",
       cmsOpenProfileFromFile(DbgThread(), "test5.icc", "r"),
       cmsOpenProfileFromFile(DbgThread(), "aRGBlcms2.icc", "r"),
        INTENT_ABSOLUTE_COLORIMETRIC);

    printf("\n");

    // - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

    SpeedTest8bits("8 bits on curves",
        CreateCurves(),
        CreateCurves(),
        INTENT_PERCEPTUAL);

    SpeedTest16bits("16 bits on curves",
        CreateCurves(),
        CreateCurves(),
        INTENT_PERCEPTUAL);

    SpeedTest32bits("32 bits on curves",
        CreateCurves(),
        CreateCurves(),
        INTENT_PERCEPTUAL);

    printf("\n");

    // - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

    SpeedTest8bitsCMYK("8 bits on CMYK profiles",
        cmsOpenProfileFromFile(DbgThread(), "test1.icc", "r"),
        cmsOpenProfileFromFile(DbgThread(), "test2.icc", "r"));

    SpeedTest16bitsCMYK("16 bits on CMYK profiles",
        cmsOpenProfileFromFile(DbgThread(), "test1.icc", "r"),
        cmsOpenProfileFromFile(DbgThread(), "test2.icc", "r"));

    SpeedTest32bitsCMYK("32 bits on CMYK profiles",
        cmsOpenProfileFromFile(DbgThread(), "test1.icc", "r"),
        cmsOpenProfileFromFile(DbgThread(), "test2.icc", "r"));

    printf("\n");

    // - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

    SpeedTest8bitsGray("8 bits on gray-to gray",
        cmsOpenProfileFromFile(DbgThread(), "gray3lcms2.icc", "r"),
        cmsOpenProfileFromFile(DbgThread(), "graylcms2.icc", "r"), INTENT_RELATIVE_COLORIMETRIC);

    SpeedTest16bitsGray("16 bits on gray-to gray",
        cmsOpenProfileFromFile(DbgThread(), "gray3lcms2.icc", "r"),
        cmsOpenProfileFromFile(DbgThread(), "graylcms2.icc", "r"), INTENT_RELATIVE_COLORIMETRIC);

    SpeedTest32bitsGray("32 bits on gray-to gray",
        cmsOpenProfileFromFile(DbgThread(), "gray3lcms2.icc", "r"),
        cmsOpenProfileFromFile(DbgThread(), "graylcms2.icc", "r"), INTENT_RELATIVE_COLORIMETRIC);

    printf("\n");

    // - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

    SpeedTest8bitsGray("8 bits on gray-to-lab gray",
        cmsOpenProfileFromFile(DbgThread(), "graylcms2.icc", "r"),
        cmsOpenProfileFromFile(DbgThread(), "glablcms2.icc", "r"), INTENT_RELATIVE_COLORIMETRIC);

    SpeedTest16bitsGray("16 bits on gray-to-lab gray",
        cmsOpenProfileFromFile(DbgThread(), "graylcms2.icc", "r"),
        cmsOpenProfileFromFile(DbgThread(), "glablcms2.icc", "r"), INTENT_RELATIVE_COLORIMETRIC);

    SpeedTest32bitsGray("32 bits on gray-to-lab gray",
        cmsOpenProfileFromFile(DbgThread(), "graylcms2.icc", "r"),
        cmsOpenProfileFromFile(DbgThread(), "glablcms2.icc", "r"), INTENT_RELATIVE_COLORIMETRIC);

    printf("\n");

    // - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

    SpeedTest8bitsGray("8 bits on SAME gray-to-gray",
        cmsOpenProfileFromFile(DbgThread(), "graylcms2.icc", "r"),
        cmsOpenProfileFromFile(DbgThread(), "graylcms2.icc", "r"), INTENT_PERCEPTUAL);

    SpeedTest16bitsGray("16 bits on SAME gray-to-gray",
        cmsOpenProfileFromFile(DbgThread(), "graylcms2.icc", "r"),
        cmsOpenProfileFromFile(DbgThread(), "graylcms2.icc", "r"), INTENT_PERCEPTUAL);

    SpeedTest32bitsGray("32 bits on SAME gray-to-gray",
        cmsOpenProfileFromFile(DbgThread(), "graylcms2.icc", "r"),
        cmsOpenProfileFromFile(DbgThread(), "graylcms2.icc", "r"), INTENT_PERCEPTUAL);

    printf("\n");
}
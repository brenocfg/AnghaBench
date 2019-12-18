#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_3__ ;
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  cmsHPROFILE ;
struct TYPE_7__ {int /*<<< orphan*/  y; int /*<<< orphan*/  x; } ;
struct TYPE_5__ {TYPE_3__ Blue; TYPE_3__ Green; TYPE_3__ Red; } ;
typedef  TYPE_1__ cmsCIExyYTRIPLE ;
struct TYPE_6__ {int /*<<< orphan*/  Blue; int /*<<< orphan*/  Green; int /*<<< orphan*/  Red; } ;
typedef  TYPE_2__ cmsCIEXYZTRIPLE ;
typedef  int /*<<< orphan*/  cmsBool ;

/* Variables and functions */
 int /*<<< orphan*/  DbgThread () ; 
 int FALSE ; 
 int /*<<< orphan*/  Fail (char*) ; 
 int /*<<< orphan*/  GetProfileRGBPrimaries (int /*<<< orphan*/ ,TYPE_2__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  INTENT_ABSOLUTE_COLORIMETRIC ; 
 int /*<<< orphan*/  IsGoodFixed15_16 (char*,int /*<<< orphan*/ ,double) ; 
 int TRUE ; 
 int /*<<< orphan*/  cmsCloseProfile (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  cmsCreate_sRGBProfile (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  cmsSetAdaptationState (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  cmsXYZ2xyY (int /*<<< orphan*/ ,TYPE_3__*,int /*<<< orphan*/ *) ; 

__attribute__((used)) static
int CheckRGBPrimaries(void)
{
    cmsHPROFILE hsRGB;
    cmsCIEXYZTRIPLE tripXYZ;
    cmsCIExyYTRIPLE tripxyY;
    cmsBool result;

    cmsSetAdaptationState(DbgThread(), 0);
    hsRGB = cmsCreate_sRGBProfile(DbgThread());
    if (!hsRGB) return 0;

    result = GetProfileRGBPrimaries(hsRGB, &tripXYZ,
        INTENT_ABSOLUTE_COLORIMETRIC);

    cmsCloseProfile(DbgThread(), hsRGB);
    if (!result) return 0;

    cmsXYZ2xyY(DbgThread(), &tripxyY.Red, &tripXYZ.Red);
    cmsXYZ2xyY(DbgThread(), &tripxyY.Green, &tripXYZ.Green);
    cmsXYZ2xyY(DbgThread(), &tripxyY.Blue, &tripXYZ.Blue);

    /* valus were taken from
    http://en.wikipedia.org/wiki/RGB_color_spaces#Specifications */

    if (!IsGoodFixed15_16("xRed", tripxyY.Red.x, 0.64) ||
        !IsGoodFixed15_16("yRed", tripxyY.Red.y, 0.33) ||
        !IsGoodFixed15_16("xGreen", tripxyY.Green.x, 0.30) ||
        !IsGoodFixed15_16("yGreen", tripxyY.Green.y, 0.60) ||
        !IsGoodFixed15_16("xBlue", tripxyY.Blue.x, 0.15) ||
        !IsGoodFixed15_16("yBlue", tripxyY.Blue.y, 0.06)) {
            Fail("One or more primaries are wrong.");
            return FALSE;
    }

    return TRUE;
}
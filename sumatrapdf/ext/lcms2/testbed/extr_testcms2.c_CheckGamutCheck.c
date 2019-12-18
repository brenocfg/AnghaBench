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
typedef  int cmsUInt16Number ;
typedef  int /*<<< orphan*/  cmsInt32Number ;
typedef  int /*<<< orphan*/  cmsHTRANSFORM ;
typedef  int /*<<< orphan*/ * cmsHPROFILE ;

/* Variables and functions */
 int /*<<< orphan*/  Check16linearXFORM (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  CheckFloatlinearXFORM (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/ * Create_AboveRGB () ; 
 int /*<<< orphan*/  DbgThread () ; 
 int /*<<< orphan*/  Fail (char*) ; 
 int /*<<< orphan*/  INTENT_RELATIVE_COLORIMETRIC ; 
 int /*<<< orphan*/  SubTest (char*) ; 
 int /*<<< orphan*/  TYPE_RGB_16 ; 
 int /*<<< orphan*/  TYPE_RGB_FLT ; 
 int /*<<< orphan*/  cmsCloseProfile (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  cmsCreateProofingTransform (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * cmsCreate_sRGBProfile (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  cmsDeleteTransform (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  cmsFLAGS_GAMUTCHECK ; 
 int /*<<< orphan*/  cmsSetAlarmCodes (int /*<<< orphan*/ ,int*) ; 

__attribute__((used)) static
cmsInt32Number CheckGamutCheck(void)
{
        cmsHPROFILE hSRGB, hAbove;
        cmsHTRANSFORM xform;
        cmsInt32Number rc;
        cmsUInt16Number Alarm[16] = { 0xDEAD, 0xBABE, 0xFACE };

        // Set alarm codes to fancy values so we could check the out of gamut condition
        cmsSetAlarmCodes(DbgThread(), Alarm);

        // Create the profiles
        hSRGB  = cmsCreate_sRGBProfile(DbgThread());
        hAbove = Create_AboveRGB();

        if (hSRGB == NULL || hAbove == NULL) return 0;  // Failed

        SubTest("Gamut check on floating point");

        // Create a gamut checker in the same space. No value should be out of gamut
        xform = cmsCreateProofingTransform(DbgThread(), hAbove, TYPE_RGB_FLT, hAbove, TYPE_RGB_FLT, hAbove,
                                INTENT_RELATIVE_COLORIMETRIC, INTENT_RELATIVE_COLORIMETRIC, cmsFLAGS_GAMUTCHECK);


        if (!CheckFloatlinearXFORM(xform, 3)) {
            cmsCloseProfile(DbgThread(), hSRGB);
            cmsCloseProfile(DbgThread(), hAbove);
            cmsDeleteTransform(DbgThread(), xform);
            Fail("Gamut check on same profile failed");
            return 0;
        }

        cmsDeleteTransform(DbgThread(), xform);

        SubTest("Gamut check on 16 bits");

        xform = cmsCreateProofingTransform(DbgThread(), hAbove, TYPE_RGB_16, hAbove, TYPE_RGB_16, hSRGB,
                                INTENT_RELATIVE_COLORIMETRIC, INTENT_RELATIVE_COLORIMETRIC, cmsFLAGS_GAMUTCHECK);

        cmsCloseProfile(DbgThread(), hSRGB);
        cmsCloseProfile(DbgThread(), hAbove);

        rc = Check16linearXFORM(xform, 3);

        cmsDeleteTransform(DbgThread(), xform);

        return rc;
}
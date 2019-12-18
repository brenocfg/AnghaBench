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
typedef  int /*<<< orphan*/ * cmsHTRANSFORM ;
typedef  int /*<<< orphan*/  cmsHPROFILE ;

/* Variables and functions */
 int /*<<< orphan*/  Create_AboveRGB () ; 
 int /*<<< orphan*/  DbgThread () ; 
 int /*<<< orphan*/  INTENT_ABSOLUTE_COLORIMETRIC ; 
 int /*<<< orphan*/  TYPE_GRAY_FLT ; 
 int /*<<< orphan*/  TYPE_RGB_FLT ; 
 int /*<<< orphan*/  cmsCloseProfile (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  cmsCreateNULLProfile (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * cmsCreateProofingTransform (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  cmsCreate_sRGBProfile (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  cmsDeleteTransform (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int cmsFLAGS_GAMUTCHECK ; 
 int cmsFLAGS_SOFTPROOFING ; 

__attribute__((used)) static
int CheckProofingIntersection(void)
{
    cmsHPROFILE profile_null, hnd1, hnd2;
    cmsHTRANSFORM transform;

    hnd1 = cmsCreate_sRGBProfile(DbgThread());
    hnd2 = Create_AboveRGB();

    profile_null = cmsCreateNULLProfile(DbgThread());
    transform = cmsCreateProofingTransform(DbgThread(),
        hnd1,
        TYPE_RGB_FLT,
        profile_null,
        TYPE_GRAY_FLT,
        hnd2,
        INTENT_ABSOLUTE_COLORIMETRIC,
        INTENT_ABSOLUTE_COLORIMETRIC,
        cmsFLAGS_GAMUTCHECK |
        cmsFLAGS_SOFTPROOFING);

    cmsCloseProfile(DbgThread(), hnd1);
    cmsCloseProfile(DbgThread(), hnd2);
    cmsCloseProfile(DbgThread(), profile_null);

    // Failed?
    if (transform == NULL) return 0;

    cmsDeleteTransform(DbgThread(), transform);
    return 1;
}
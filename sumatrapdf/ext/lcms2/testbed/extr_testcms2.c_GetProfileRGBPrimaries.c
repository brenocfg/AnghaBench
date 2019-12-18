#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  cmsUInt32Number ;
typedef  int /*<<< orphan*/ * cmsHTRANSFORM ;
typedef  int /*<<< orphan*/ * cmsHPROFILE ;
struct TYPE_3__ {int member_0; int member_1; int member_2; } ;
typedef  TYPE_1__ cmsFloat64Number ;
typedef  int /*<<< orphan*/  cmsCIEXYZTRIPLE ;
typedef  int /*<<< orphan*/  cmsBool ;

/* Variables and functions */
 int /*<<< orphan*/  DbgThread () ; 
 int /*<<< orphan*/  FALSE ; 
 int /*<<< orphan*/  TRUE ; 
 int /*<<< orphan*/  TYPE_RGB_DBL ; 
 int /*<<< orphan*/  TYPE_XYZ_DBL ; 
 int /*<<< orphan*/  cmsCloseProfile (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * cmsCreateTransform (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/ * cmsCreateXYZProfile (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  cmsDeleteTransform (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  cmsDoTransform (int /*<<< orphan*/ ,int /*<<< orphan*/ *,TYPE_1__**,int /*<<< orphan*/ *,int) ; 
 int cmsFLAGS_NOCACHE ; 
 int cmsFLAGS_NOOPTIMIZE ; 

__attribute__((used)) static
cmsBool GetProfileRGBPrimaries(cmsHPROFILE hProfile,
                                cmsCIEXYZTRIPLE *result,
                                cmsUInt32Number intent)
{
    cmsHPROFILE hXYZ;
    cmsHTRANSFORM hTransform;
    cmsFloat64Number rgb[3][3] = {{1., 0., 0.},
    {0., 1., 0.},
    {0., 0., 1.}};

    hXYZ = cmsCreateXYZProfile(DbgThread());
    if (hXYZ == NULL) return FALSE;

    hTransform = cmsCreateTransform(DbgThread(), hProfile, TYPE_RGB_DBL, hXYZ, TYPE_XYZ_DBL,
        intent, cmsFLAGS_NOCACHE | cmsFLAGS_NOOPTIMIZE);
    cmsCloseProfile(DbgThread(), hXYZ);
    if (hTransform == NULL) return FALSE;

    cmsDoTransform(DbgThread(), hTransform, rgb, result, 3);
    cmsDeleteTransform(DbgThread(), hTransform);
    return TRUE;
}
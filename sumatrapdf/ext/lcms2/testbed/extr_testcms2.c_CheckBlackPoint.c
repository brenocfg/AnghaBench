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
typedef  int cmsInt32Number ;
typedef  int /*<<< orphan*/  cmsHPROFILE ;
typedef  int /*<<< orphan*/  cmsCIEXYZ ;
typedef  int /*<<< orphan*/  cmsCIELab ;

/* Variables and functions */
 int /*<<< orphan*/  DbgThread () ; 
 int /*<<< orphan*/  INTENT_PERCEPTUAL ; 
 int /*<<< orphan*/  INTENT_RELATIVE_COLORIMETRIC ; 
 int /*<<< orphan*/  cmsCloseProfile (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  cmsDetectDestinationBlackPoint (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  cmsOpenProfileFromFile (int /*<<< orphan*/ ,char*,char*) ; 
 int /*<<< orphan*/  cmsXYZ2Lab (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 

__attribute__((used)) static
cmsInt32Number CheckBlackPoint(void)
{
    cmsHPROFILE hProfile;
    cmsCIEXYZ Black;
    cmsCIELab Lab;

    hProfile  = cmsOpenProfileFromFile(DbgThread(), "test5.icc", "r");
    cmsDetectDestinationBlackPoint(DbgThread(), &Black, hProfile, INTENT_RELATIVE_COLORIMETRIC, 0);
    cmsCloseProfile(DbgThread(), hProfile);


    hProfile = cmsOpenProfileFromFile(DbgThread(), "test1.icc", "r");
    cmsDetectDestinationBlackPoint(DbgThread(), &Black, hProfile, INTENT_RELATIVE_COLORIMETRIC, 0);
    cmsXYZ2Lab(DbgThread(), NULL, &Lab, &Black);
    cmsCloseProfile(DbgThread(), hProfile);

    hProfile = cmsOpenProfileFromFile(DbgThread(), "lcms2cmyk.icc", "r");
    cmsDetectDestinationBlackPoint(DbgThread(), &Black, hProfile, INTENT_RELATIVE_COLORIMETRIC, 0);
    cmsXYZ2Lab(DbgThread(), NULL, &Lab, &Black);
    cmsCloseProfile(DbgThread(), hProfile);

    hProfile = cmsOpenProfileFromFile(DbgThread(), "test2.icc", "r");
    cmsDetectDestinationBlackPoint(DbgThread(), &Black, hProfile, INTENT_RELATIVE_COLORIMETRIC, 0);
    cmsXYZ2Lab(DbgThread(), NULL, &Lab, &Black);
    cmsCloseProfile(DbgThread(), hProfile);

    hProfile = cmsOpenProfileFromFile(DbgThread(), "test1.icc", "r");
    cmsDetectDestinationBlackPoint(DbgThread(), &Black, hProfile, INTENT_PERCEPTUAL, 0);
    cmsXYZ2Lab(DbgThread(), NULL, &Lab, &Black);
    cmsCloseProfile(DbgThread(), hProfile);

    return 1;
}
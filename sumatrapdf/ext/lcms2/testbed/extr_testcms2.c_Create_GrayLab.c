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
typedef  int /*<<< orphan*/  cmsToneCurve ;
typedef  int /*<<< orphan*/ * cmsHPROFILE ;

/* Variables and functions */
 int /*<<< orphan*/  DbgThread () ; 
 int /*<<< orphan*/ * cmsBuildGamma (int /*<<< orphan*/ ,double) ; 
 int /*<<< orphan*/ * cmsCreateGrayProfile (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  cmsD50_xyY (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  cmsFreeToneCurve (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  cmsSetPCS (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  cmsSigLabData ; 

__attribute__((used)) static
cmsHPROFILE Create_GrayLab(void)
{
    cmsHPROFILE hProfile;
    cmsToneCurve* Curve = cmsBuildGamma(DbgThread(), 1.0);
    if (Curve == NULL) return NULL;

    hProfile = cmsCreateGrayProfile(DbgThread(), cmsD50_xyY(DbgThread()), Curve);
    cmsFreeToneCurve(DbgThread(), Curve);

    cmsSetPCS(DbgThread(), hProfile, cmsSigLabData);
    return hProfile;
}
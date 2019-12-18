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
 int /*<<< orphan*/ * cmsCreateLinearizationDeviceLink (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ **) ; 
 int /*<<< orphan*/  cmsFreeToneCurve (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  cmsSigCmykData ; 

__attribute__((used)) static
cmsHPROFILE Create_CMYK_DeviceLink(void)
{
    cmsHPROFILE hProfile;
    cmsToneCurve* Tab[4];
    cmsToneCurve* Curve = cmsBuildGamma(DbgThread(), 3.0);
    if (Curve == NULL) return NULL;

    Tab[0] = Curve;
    Tab[1] = Curve;
    Tab[2] = Curve;
    Tab[3] = Curve;

    hProfile = cmsCreateLinearizationDeviceLink(DbgThread(), cmsSigCmykData, Tab);
    if (hProfile == NULL) return NULL;

    cmsFreeToneCurve(DbgThread(), Curve);

    return hProfile;
}
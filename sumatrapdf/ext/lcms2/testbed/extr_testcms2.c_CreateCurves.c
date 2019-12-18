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
typedef  int /*<<< orphan*/  cmsHPROFILE ;

/* Variables and functions */
 int /*<<< orphan*/  DbgThread () ; 
 int /*<<< orphan*/ * cmsBuildGamma (int /*<<< orphan*/ ,double) ; 
 int /*<<< orphan*/  cmsCreateLinearizationDeviceLink (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ **) ; 
 int /*<<< orphan*/  cmsFreeToneCurve (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  cmsSigRgbData ; 

__attribute__((used)) static
cmsHPROFILE CreateCurves(void)
{
    cmsToneCurve* Gamma = cmsBuildGamma(DbgThread(), 1.1);
    cmsToneCurve* Transfer[3];
    cmsHPROFILE h;

    Transfer[0] = Transfer[1] = Transfer[2] = Gamma;
    h = cmsCreateLinearizationDeviceLink(DbgThread(), cmsSigRgbData, Transfer);

    cmsFreeToneCurve(DbgThread(), Gamma);

    return h;
}
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
typedef  int /*<<< orphan*/  cmsInt32Number ;
typedef  int /*<<< orphan*/  cmsBool ;

/* Variables and functions */
 int /*<<< orphan*/ * Build_sRGBGamma () ; 
 int /*<<< orphan*/ * CombineGammaFloat (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  DbgThread () ; 
 int /*<<< orphan*/  cmsFreeToneCurve (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  cmsIsToneCurveLinear (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * cmsReverseToneCurve (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 

__attribute__((used)) static
cmsInt32Number CheckJointFloatCurves_sRGB(void)
{
    cmsToneCurve *Forward, *Reverse, *Result;
    cmsBool  rc;

    Forward = Build_sRGBGamma();
    Reverse = cmsReverseToneCurve(DbgThread(), Forward);
    Result = CombineGammaFloat(Forward, Reverse);
    cmsFreeToneCurve(DbgThread(), Forward); cmsFreeToneCurve(DbgThread(), Reverse);

    rc = cmsIsToneCurveLinear(DbgThread(), Result);
    cmsFreeToneCurve(DbgThread(), Result);

    return rc;
}
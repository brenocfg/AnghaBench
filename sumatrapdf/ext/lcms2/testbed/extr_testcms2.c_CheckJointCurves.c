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
 int /*<<< orphan*/  DbgThread () ; 
 int /*<<< orphan*/  Fail (char*) ; 
 int /*<<< orphan*/ * cmsBuildGamma (int /*<<< orphan*/ ,double) ; 
 int /*<<< orphan*/  cmsFreeToneCurve (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  cmsIsToneCurveLinear (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * cmsJoinToneCurve (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int) ; 

__attribute__((used)) static
cmsInt32Number CheckJointCurves(void)
{
    cmsToneCurve *Forward, *Reverse, *Result;
    cmsBool  rc;

    Forward = cmsBuildGamma(DbgThread(), 3.0);
    Reverse = cmsBuildGamma(DbgThread(), 3.0);

    Result = cmsJoinToneCurve(DbgThread(), Forward, Reverse, 256);

    cmsFreeToneCurve(DbgThread(), Forward); cmsFreeToneCurve(DbgThread(), Reverse);

    rc = cmsIsToneCurveLinear(DbgThread(), Result);
    cmsFreeToneCurve(DbgThread(), Result);

    if (!rc)
        Fail("Joining same curve twice does not result in a linear ramp");

    return rc;
}
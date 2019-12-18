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
typedef  double cmsFloat64Number ;

/* Variables and functions */
 int /*<<< orphan*/  DbgThread () ; 
 int /*<<< orphan*/ * cmsBuildParametricToneCurve (int /*<<< orphan*/ ,int,double*) ; 
 int /*<<< orphan*/  cmsFreeToneCurve (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  cmsIsToneCurveLinear (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * cmsJoinToneCurve (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/ * cmsReverseToneCurve (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 

__attribute__((used)) static
cmsInt32Number CheckJointCurvesSShaped(void)
{
    cmsFloat64Number p = 3.2;
    cmsToneCurve *Forward, *Reverse, *Result;
    cmsInt32Number rc;

    Forward = cmsBuildParametricToneCurve(DbgThread(), 108, &p);
    Reverse = cmsReverseToneCurve(DbgThread(), Forward);
    Result = cmsJoinToneCurve(DbgThread(), Forward, Forward, 4096);

    cmsFreeToneCurve(DbgThread(), Forward);
    cmsFreeToneCurve(DbgThread(), Reverse);

    rc = cmsIsToneCurveLinear(DbgThread(), Result);
    cmsFreeToneCurve(DbgThread(), Result);
    return rc;
}
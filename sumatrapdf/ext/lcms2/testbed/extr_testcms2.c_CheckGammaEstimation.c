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
typedef  int cmsInt32Number ;
typedef  scalar_t__ cmsFloat64Number ;

/* Variables and functions */
 int /*<<< orphan*/  DbgThread () ; 
 int /*<<< orphan*/  SubTest (char*) ; 
 scalar_t__ cmsEstimateGamma (int /*<<< orphan*/ ,int /*<<< orphan*/ *,double) ; 
 double fabs (scalar_t__) ; 

__attribute__((used)) static
cmsInt32Number CheckGammaEstimation(cmsToneCurve* c, cmsFloat64Number g)
{
    cmsFloat64Number est = cmsEstimateGamma(DbgThread(), c, 0.001);

    SubTest("Gamma estimation");
    if (fabs(est - g) > 0.001) return 0;
    return 1;
}
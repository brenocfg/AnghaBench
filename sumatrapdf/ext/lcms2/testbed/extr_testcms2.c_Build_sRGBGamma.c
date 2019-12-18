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
typedef  double cmsFloat64Number ;

/* Variables and functions */
 int /*<<< orphan*/  DbgThread () ; 
 int /*<<< orphan*/ * cmsBuildParametricToneCurve (int /*<<< orphan*/ ,int,double*) ; 

__attribute__((used)) static
cmsToneCurve* Build_sRGBGamma(void)
{
    cmsFloat64Number Parameters[5];

    Parameters[0] = 2.4;
    Parameters[1] = 1. / 1.055;
    Parameters[2] = 0.055 / 1.055;
    Parameters[3] = 1. / 12.92;
    Parameters[4] = 0.04045;    // d

    return cmsBuildParametricToneCurve(DbgThread(), 4, Parameters);
}
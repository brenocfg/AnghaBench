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
typedef  int cmsFloat32Number ;

/* Variables and functions */
 int /*<<< orphan*/  DbgThread () ; 
 int StraightLine (int) ; 
 int /*<<< orphan*/  TestCurve (char*,int /*<<< orphan*/ *,int (*) (int)) ; 
 int /*<<< orphan*/ * cmsBuildTabulatedToneCurveFloat (int /*<<< orphan*/ *,int,int*) ; 
 int /*<<< orphan*/  cmsFreeToneCurve (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int kNumPoints ; 

__attribute__((used)) static
cmsInt32Number CheckFloatSamples(void)
{
    cmsFloat32Number y[kNumPoints];
    int i;
    cmsToneCurve *curve;
    cmsInt32Number ok;

    for (i = 0; i < kNumPoints; i++) {
        cmsFloat32Number x = (cmsFloat32Number)i / (kNumPoints-1);

        y[i] = StraightLine(x);
    }

    curve = cmsBuildTabulatedToneCurveFloat(NULL, kNumPoints, y);
    ok = TestCurve( "Float Samples", curve, StraightLine);
    cmsFreeToneCurve(DbgThread(), curve);

    return ok;
}
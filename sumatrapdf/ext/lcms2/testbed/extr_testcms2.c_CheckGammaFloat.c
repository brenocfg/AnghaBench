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
typedef  double cmsFloat64Number ;
typedef  double cmsFloat32Number ;

/* Variables and functions */
 int /*<<< orphan*/  CheckGammaEstimation (int /*<<< orphan*/ *,double) ; 
 int /*<<< orphan*/  DbgThread () ; 
 double MaxErr ; 
 int /*<<< orphan*/ * cmsBuildGamma (int /*<<< orphan*/ ,double) ; 
 double cmsEvalToneCurveFloat (int /*<<< orphan*/ ,int /*<<< orphan*/ *,double) ; 
 int /*<<< orphan*/  cmsFreeToneCurve (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 double fabs (double) ; 
 double pow (double,double) ; 
 int /*<<< orphan*/  printf (char*,double) ; 

__attribute__((used)) static
cmsInt32Number CheckGammaFloat(cmsFloat64Number g)
{
    cmsToneCurve* Curve = cmsBuildGamma(DbgThread(), g);
    cmsInt32Number i;
    cmsFloat32Number in, out;
    cmsFloat64Number val, Err;

    MaxErr = 0.0;
    for (i=0; i < 0xffff; i++) {

        in = (cmsFloat32Number) (i / 65535.0);
        out = cmsEvalToneCurveFloat(DbgThread(), Curve, in);
        val = pow((cmsFloat64Number) in, g);

        Err = fabs( val - out);
        if (Err > MaxErr) MaxErr = Err;
    }

    if (MaxErr > 0) printf("|Err|<%lf ", MaxErr * 65535.0);

    if (!CheckGammaEstimation(Curve, g)) return 0;

    cmsFreeToneCurve(DbgThread(), Curve);
    return 1;
}
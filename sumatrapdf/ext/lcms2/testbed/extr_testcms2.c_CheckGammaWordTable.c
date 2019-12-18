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
typedef  scalar_t__ cmsUInt16Number ;
typedef  int /*<<< orphan*/  cmsToneCurve ;
typedef  int cmsInt32Number ;
typedef  double cmsFloat64Number ;
typedef  scalar_t__ cmsFloat32Number ;

/* Variables and functions */
 int /*<<< orphan*/  CheckGammaEstimation (int /*<<< orphan*/ *,double) ; 
 int /*<<< orphan*/  DbgThread () ; 
 double MaxErr ; 
 int /*<<< orphan*/ * cmsBuildTabulatedToneCurve16 (int /*<<< orphan*/ ,int,scalar_t__*) ; 
 scalar_t__ cmsEvalToneCurveFloat (int /*<<< orphan*/ ,int /*<<< orphan*/ *,scalar_t__) ; 
 int /*<<< orphan*/  cmsFreeToneCurve (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 double fabs (scalar_t__) ; 
 scalar_t__ floor (double) ; 
 double pow (scalar_t__,double) ; 
 int /*<<< orphan*/  printf (char*,double) ; 

__attribute__((used)) static
cmsInt32Number CheckGammaWordTable(cmsFloat64Number g)
{
    cmsUInt16Number Values[1025];
    cmsToneCurve* Curve;
    cmsInt32Number i;
    cmsFloat32Number in, out;
    cmsFloat64Number val, Err;

    for (i=0; i <= 1024; i++) {

        in = (cmsFloat32Number) (i / 1024.0);
        Values[i] = (cmsUInt16Number) floor(pow(in, g) * 65535.0 + 0.5);
    }

    Curve = cmsBuildTabulatedToneCurve16(DbgThread(), 1025, Values);

    MaxErr = 0.0;
    for (i=0; i <= 0xffff; i++) {

        in = (cmsFloat32Number) (i / 65535.0);
        out = cmsEvalToneCurveFloat(DbgThread(), Curve, in);
        val = pow(in, g);

        Err = fabs(val - out);
        if (Err > MaxErr) MaxErr = Err;
    }

    if (MaxErr > 0) printf("|Err|<%lf ", MaxErr * 65535.0);

    if (!CheckGammaEstimation(Curve, g)) return 0;

    cmsFreeToneCurve(DbgThread(), Curve);
    return 1;
}
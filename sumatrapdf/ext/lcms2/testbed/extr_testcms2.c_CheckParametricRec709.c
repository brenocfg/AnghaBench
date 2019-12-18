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
typedef  float cmsFloat32Number ;

/* Variables and functions */
 int /*<<< orphan*/  DbgThread () ; 
 double Rec709 (double) ; 
 int /*<<< orphan*/ * cmsBuildParametricToneCurve (int /*<<< orphan*/ *,int,double*) ; 
 double cmsEvalToneCurveFloat (int /*<<< orphan*/ ,int /*<<< orphan*/ *,float) ; 
 int /*<<< orphan*/  cmsFreeToneCurve (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  floor (double) ; 
 double pow (double,double) ; 

__attribute__((used)) static
cmsInt32Number CheckParametricRec709(void)
{
    cmsFloat64Number params[7];
    cmsToneCurve* t;
    int i;

    params[0] = 0.45; /* y */
    params[1] = pow(1.099, 1.0 / 0.45); /* a */
    params[2] = 0.0; /* b */
    params[3] = 4.5; /* c */
    params[4] = 0.018; /* d */
    params[5] = -0.099; /* e */
    params[6] = 0.0; /* f */

    t = cmsBuildParametricToneCurve (NULL, 5, params);


    for (i=0; i < 256; i++)
    {
        cmsFloat32Number n = (cmsFloat32Number) i / 255.0F;
        cmsUInt16Number f1 = (cmsUInt16Number) floor(255.0 * cmsEvalToneCurveFloat(DbgThread(), t, n) + 0.5);
        cmsUInt16Number f2 = (cmsUInt16Number) floor(255.0*Rec709((double) i / 255.0) + 0.5);

        if (f1 != f2)
        {
            cmsFreeToneCurve(DbgThread(), t);
            return 0;
        }
    }

    cmsFreeToneCurve(DbgThread(), t);
    return 1;
}
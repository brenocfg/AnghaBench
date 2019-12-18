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
typedef  float cmsFloat32Number ;

/* Variables and functions */
 int /*<<< orphan*/  DbgThread () ; 
 int /*<<< orphan*/ * cmsBuildTabulatedToneCurve16 (int /*<<< orphan*/ ,int,scalar_t__*) ; 
 float cmsEvalToneCurveFloat (int /*<<< orphan*/ ,int /*<<< orphan*/ *,float) ; 
 scalar_t__ floor (float) ; 

__attribute__((used)) static
cmsToneCurve* CombineGammaFloat(cmsToneCurve* g1, cmsToneCurve* g2)
{
    cmsUInt16Number Tab[256];
    cmsFloat32Number f;
    cmsInt32Number i;

    for (i=0; i < 256; i++) {

        f = (cmsFloat32Number) i / 255.0F;
        f = cmsEvalToneCurveFloat(DbgThread(), g2, cmsEvalToneCurveFloat(DbgThread(), g1, f));

        Tab[i] = (cmsUInt16Number) floor(f * 65535.0 + 0.5);
    }

    return  cmsBuildTabulatedToneCurve16(DbgThread(), 256, Tab);
}
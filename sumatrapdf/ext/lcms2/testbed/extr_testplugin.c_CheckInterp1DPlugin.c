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
typedef  float cmsFloat32Number ;
typedef  int /*<<< orphan*/ * cmsContext ;

/* Variables and functions */
 int /*<<< orphan*/ * DupContext (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  Fail (char*) ; 
 int /*<<< orphan*/  InterpPluginSample ; 
 int /*<<< orphan*/  IsGoodVal (char*,int /*<<< orphan*/ ,double,double) ; 
 int /*<<< orphan*/ * WatchDogContext (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * cmsBuildTabulatedToneCurveFloat (int /*<<< orphan*/ *,int,float const*) ; 
 int /*<<< orphan*/  cmsDeleteContext (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  cmsEvalToneCurveFloat (int /*<<< orphan*/ *,int /*<<< orphan*/ *,float) ; 
 int /*<<< orphan*/  cmsFreeToneCurve (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  cmsPlugin (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 

cmsInt32Number CheckInterp1DPlugin(void)
{
    cmsToneCurve* Sampled1D = NULL;
    cmsContext ctx = NULL;
    cmsContext cpy = NULL;
    const cmsFloat32Number tab[] = { 0.0f, 0.10f, 0.20f, 0.30f, 0.40f, 0.50f, 0.60f, 0.70f, 0.80f, 0.90f, 1.00f };  // A straight line

    // 1st level context
    ctx = WatchDogContext(NULL);
    if (ctx == NULL) {
        Fail("Cannot create context");
        goto Error;
    }

    cmsPlugin(ctx, &InterpPluginSample);

    cpy = DupContext(ctx, NULL);
     if (cpy == NULL) {
        Fail("Cannot create context (2)");
        goto Error;
    }

    Sampled1D = cmsBuildTabulatedToneCurveFloat(cpy, 11, tab);
    if (Sampled1D == NULL) {
        Fail("Cannot create tone curve (1)");
        goto Error;
    }

    // Do some interpolations with the plugin
    if (!IsGoodVal("0.10", cmsEvalToneCurveFloat(cpy, Sampled1D, 0.10f), 0.10, 0.01)) goto Error;
    if (!IsGoodVal("0.13", cmsEvalToneCurveFloat(cpy, Sampled1D, 0.13f), 0.10, 0.01)) goto Error;
    if (!IsGoodVal("0.55", cmsEvalToneCurveFloat(cpy, Sampled1D, 0.55f), 0.50, 0.01)) goto Error;
    if (!IsGoodVal("0.9999", cmsEvalToneCurveFloat(cpy, Sampled1D, 0.9999f), 0.90, 0.01)) goto Error;

    cmsFreeToneCurve(cpy, Sampled1D);
    cmsDeleteContext(ctx);
    cmsDeleteContext(cpy);

    // Now in global context
    Sampled1D = cmsBuildTabulatedToneCurveFloat(NULL, 11, tab);
    if (Sampled1D == NULL) {
        Fail("Cannot create tone curve (2)");
        goto Error;
    }

    // Now without the plug-in
    if (!IsGoodVal("0.10", cmsEvalToneCurveFloat(NULL, Sampled1D, 0.10f), 0.10, 0.001)) goto Error;
    if (!IsGoodVal("0.13", cmsEvalToneCurveFloat(NULL, Sampled1D, 0.13f), 0.13, 0.001)) goto Error;
    if (!IsGoodVal("0.55", cmsEvalToneCurveFloat(NULL, Sampled1D, 0.55f), 0.55, 0.001)) goto Error;
    if (!IsGoodVal("0.9999", cmsEvalToneCurveFloat(NULL, Sampled1D, 0.9999f), 0.9999, 0.001)) goto Error;

    cmsFreeToneCurve(NULL, Sampled1D);
    return 1;

Error:
    if (ctx != NULL) cmsDeleteContext(ctx);
     if (cpy != NULL) cmsDeleteContext(ctx);
    if (Sampled1D != NULL) cmsFreeToneCurve(NULL, Sampled1D);
    return 0;

}
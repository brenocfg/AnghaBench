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
typedef  int /*<<< orphan*/ * cmsContext ;

/* Variables and functions */
 int /*<<< orphan*/  CurvePluginSample ; 
 int /*<<< orphan*/  CurvePluginSample2 ; 
 int /*<<< orphan*/ * DupContext (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  IsGoodVal (char*,int /*<<< orphan*/ ,double,double) ; 
 double M_PI ; 
 int /*<<< orphan*/  TYPE_COS ; 
 int /*<<< orphan*/  TYPE_SIN ; 
 int /*<<< orphan*/  TYPE_TAN ; 
 int /*<<< orphan*/ * WatchDogContext (int /*<<< orphan*/ *) ; 
 double acos (double) ; 
 double asin (double) ; 
 int /*<<< orphan*/ * cmsBuildParametricToneCurve (int /*<<< orphan*/ *,int /*<<< orphan*/ ,double*) ; 
 int /*<<< orphan*/  cmsDeleteContext (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  cmsEvalToneCurveFloat (int /*<<< orphan*/ *,int /*<<< orphan*/ *,float) ; 
 int /*<<< orphan*/  cmsFreeToneCurve (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  cmsPlugin (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * cmsReverseToneCurve (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 double cos (double) ; 
 double sin (double) ; 
 double tan (double) ; 

cmsInt32Number CheckParametricCurvePlugin(void)
{
    cmsContext ctx = NULL;
    cmsContext cpy = NULL;
    cmsToneCurve* sinus;
    cmsToneCurve* cosinus;
    cmsToneCurve* tangent;
    cmsToneCurve* reverse_sinus;
    cmsToneCurve* reverse_cosinus;
    cmsFloat64Number scale = 1.0;

    ctx = WatchDogContext(NULL);

    cmsPlugin(ctx, &CurvePluginSample);

    cpy = DupContext(ctx, NULL);

    cmsPlugin(cpy, &CurvePluginSample2);

    sinus = cmsBuildParametricToneCurve(cpy, TYPE_SIN, &scale);
    cosinus = cmsBuildParametricToneCurve(cpy, TYPE_COS, &scale);
    tangent = cmsBuildParametricToneCurve(cpy, TYPE_TAN, &scale);
    reverse_sinus = cmsReverseToneCurve(cpy, sinus);
    reverse_cosinus = cmsReverseToneCurve(cpy, cosinus);


     if (!IsGoodVal("0.10", cmsEvalToneCurveFloat(cpy, sinus, 0.10f), sin(0.10 * M_PI) , 0.001)) goto Error;
     if (!IsGoodVal("0.60", cmsEvalToneCurveFloat(cpy, sinus, 0.60f), sin(0.60* M_PI), 0.001)) goto Error;
     if (!IsGoodVal("0.90", cmsEvalToneCurveFloat(cpy, sinus, 0.90f), sin(0.90* M_PI), 0.001)) goto Error;

     if (!IsGoodVal("0.10", cmsEvalToneCurveFloat(cpy, cosinus, 0.10f), cos(0.10* M_PI), 0.001)) goto Error;
     if (!IsGoodVal("0.60", cmsEvalToneCurveFloat(cpy, cosinus, 0.60f), cos(0.60* M_PI), 0.001)) goto Error;
     if (!IsGoodVal("0.90", cmsEvalToneCurveFloat(cpy, cosinus, 0.90f), cos(0.90* M_PI), 0.001)) goto Error;

     if (!IsGoodVal("0.10", cmsEvalToneCurveFloat(cpy, tangent, 0.10f), tan(0.10* M_PI), 0.001)) goto Error;
     if (!IsGoodVal("0.60", cmsEvalToneCurveFloat(cpy, tangent, 0.60f), tan(0.60* M_PI), 0.001)) goto Error;
     if (!IsGoodVal("0.90", cmsEvalToneCurveFloat(cpy, tangent, 0.90f), tan(0.90* M_PI), 0.001)) goto Error;


     if (!IsGoodVal("0.10", cmsEvalToneCurveFloat(cpy, reverse_sinus, 0.10f), asin(0.10)/M_PI, 0.001)) goto Error;
     if (!IsGoodVal("0.60", cmsEvalToneCurveFloat(cpy, reverse_sinus, 0.60f), asin(0.60)/M_PI, 0.001)) goto Error;
     if (!IsGoodVal("0.90", cmsEvalToneCurveFloat(cpy, reverse_sinus, 0.90f), asin(0.90)/M_PI, 0.001)) goto Error;

     if (!IsGoodVal("0.10", cmsEvalToneCurveFloat(cpy, reverse_cosinus, 0.10f), acos(0.10)/M_PI, 0.001)) goto Error;
     if (!IsGoodVal("0.60", cmsEvalToneCurveFloat(cpy, reverse_cosinus, 0.60f), acos(0.60)/M_PI, 0.001)) goto Error;
     if (!IsGoodVal("0.90", cmsEvalToneCurveFloat(cpy, reverse_cosinus, 0.90f), acos(0.90)/M_PI, 0.001)) goto Error;

     cmsFreeToneCurve(cpy, sinus);
     cmsFreeToneCurve(cpy, cosinus);
     cmsFreeToneCurve(cpy, tangent);
     cmsFreeToneCurve(cpy, reverse_sinus);
     cmsFreeToneCurve(cpy, reverse_cosinus);

     cmsDeleteContext(ctx);
     cmsDeleteContext(cpy);

     return 1;

Error:

     cmsFreeToneCurve(cpy, sinus);
     cmsFreeToneCurve(cpy, reverse_sinus);
     cmsFreeToneCurve(cpy, cosinus);
     cmsFreeToneCurve(cpy, reverse_cosinus);

     if (ctx != NULL) cmsDeleteContext(ctx);
     if (cpy != NULL) cmsDeleteContext(cpy);
     return 0;
}
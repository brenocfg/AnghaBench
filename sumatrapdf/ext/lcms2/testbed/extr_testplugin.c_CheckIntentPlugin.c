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
typedef  int cmsUInt8Number ;
typedef  int /*<<< orphan*/  cmsToneCurve ;
typedef  int cmsInt32Number ;
typedef  int /*<<< orphan*/  cmsHTRANSFORM ;
typedef  int /*<<< orphan*/  cmsHPROFILE ;
typedef  int /*<<< orphan*/  cmsContext ;

/* Variables and functions */
 int /*<<< orphan*/  DupContext (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  INTENT_DECEPTIVE ; 
 int /*<<< orphan*/  IntentPluginSample ; 
 int /*<<< orphan*/  TYPE_GRAY_8 ; 
 int /*<<< orphan*/  WatchDogContext (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * cmsBuildGamma (int /*<<< orphan*/ ,double) ; 
 int /*<<< orphan*/  cmsCloseProfile (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  cmsCreateLinearizationDeviceLink (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ **) ; 
 int /*<<< orphan*/  cmsCreateTransform (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  cmsDeleteContext (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  cmsDeleteTransform (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  cmsDoTransform (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int*,int*,int) ; 
 int /*<<< orphan*/  cmsFreeToneCurve (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  cmsPlugin (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  cmsSigGrayData ; 

cmsInt32Number CheckIntentPlugin(void)
{
    cmsContext ctx = WatchDogContext(NULL);
    cmsContext cpy;
    cmsHTRANSFORM xform;
    cmsHPROFILE h1, h2;
    cmsToneCurve* Linear1;
    cmsToneCurve* Linear2;
    cmsUInt8Number In[]= { 10, 20, 30, 40 };
    cmsUInt8Number Out[4];
    int i;

    cmsPlugin(ctx, &IntentPluginSample);

    cpy  = DupContext(ctx, NULL);

    Linear1 = cmsBuildGamma(cpy, 3.0);
    Linear2 = cmsBuildGamma(cpy, 0.1);
    h1 = cmsCreateLinearizationDeviceLink(cpy, cmsSigGrayData, &Linear1);
    h2 = cmsCreateLinearizationDeviceLink(cpy, cmsSigGrayData, &Linear2);

    cmsFreeToneCurve(cpy, Linear1);
    cmsFreeToneCurve(cpy, Linear2);

    xform = cmsCreateTransform(cpy, h1, TYPE_GRAY_8, h2, TYPE_GRAY_8, INTENT_DECEPTIVE, 0);
    cmsCloseProfile(cpy,h1); cmsCloseProfile(cpy, h2);

    cmsDoTransform(cpy, xform, In, Out, 4);

    cmsDeleteTransform(cpy, xform);
    cmsDeleteContext(cpy);
    cmsDeleteContext(ctx);

    for (i=0; i < 4; i++)
        if (Out[i] != In[i]) return 0;

    return 1;
}
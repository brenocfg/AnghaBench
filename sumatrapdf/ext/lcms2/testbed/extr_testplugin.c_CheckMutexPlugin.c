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
 int /*<<< orphan*/  INTENT_PERCEPTUAL ; 
 int /*<<< orphan*/  MutexPluginSample ; 
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

cmsInt32Number CheckMutexPlugin(void)
{
    cmsContext ctx = WatchDogContext(NULL);
    cmsContext cpy;
    cmsHTRANSFORM xform;
    cmsUInt8Number In[]= { 10, 20, 30, 40 };
    cmsUInt8Number Out[4];
    cmsToneCurve* Linear;
    cmsHPROFILE h;
    int i;


    cmsPlugin(ctx, &MutexPluginSample);

    cpy  = DupContext(ctx, NULL);

    Linear = cmsBuildGamma(cpy, 1.0);
    h = cmsCreateLinearizationDeviceLink(cpy, cmsSigGrayData, &Linear);
    cmsFreeToneCurve(cpy, Linear);

    xform = cmsCreateTransform(cpy, h, TYPE_GRAY_8, h, TYPE_GRAY_8, INTENT_PERCEPTUAL, 0);
    cmsCloseProfile(cpy, h);

    cmsDoTransform(cpy, xform, In, Out, 4);

    cmsDeleteTransform(cpy, xform);
    cmsDeleteContext(ctx);
    cmsDeleteContext(cpy);

    for (i=0; i < 4; i++)
        if (Out[i] != In[i]) return 0;

    return 1;
}
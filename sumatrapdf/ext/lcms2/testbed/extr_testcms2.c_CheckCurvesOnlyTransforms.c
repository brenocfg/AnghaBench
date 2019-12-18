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
typedef  int /*<<< orphan*/  cmsHTRANSFORM ;
typedef  int /*<<< orphan*/ * cmsHPROFILE ;

/* Variables and functions */
 int Check16linearXFORM (int /*<<< orphan*/ ,int) ; 
 int Check8linearXFORM (int /*<<< orphan*/ ,int) ; 
 int CheckFloatlinearXFORM (int /*<<< orphan*/ ,int) ; 
 int Compare16bitXFORM (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int Compare8bitXFORM (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int CompareFloatXFORM (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  DbgThread () ; 
 int /*<<< orphan*/  INTENT_PERCEPTUAL ; 
 int /*<<< orphan*/  SubTest (char*) ; 
 int /*<<< orphan*/  TYPE_GRAY_16 ; 
 int /*<<< orphan*/  TYPE_GRAY_8 ; 
 int /*<<< orphan*/  TYPE_GRAY_FLT ; 
 int /*<<< orphan*/ * cmsBuildGamma (int /*<<< orphan*/ ,double) ; 
 int /*<<< orphan*/  cmsCloseProfile (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * cmsCreateLinearizationDeviceLink (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ **) ; 
 int /*<<< orphan*/  cmsCreateTransform (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  cmsDeleteTransform (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  cmsFreeToneCurve (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  cmsSigGrayData ; 

__attribute__((used)) static
cmsInt32Number CheckCurvesOnlyTransforms(void)
{

    cmsHTRANSFORM xform1, xform2;
    cmsHPROFILE h1, h2, h3;
    cmsToneCurve* c1, *c2, *c3;
    cmsInt32Number rc = 1;


    c1 = cmsBuildGamma(DbgThread(), 2.2);
    c2 = cmsBuildGamma(DbgThread(), 1/2.2);
    c3 = cmsBuildGamma(DbgThread(), 4.84);

    h1 = cmsCreateLinearizationDeviceLink(DbgThread(), cmsSigGrayData, &c1);
    h2 = cmsCreateLinearizationDeviceLink(DbgThread(), cmsSigGrayData, &c2);
    h3 = cmsCreateLinearizationDeviceLink(DbgThread(), cmsSigGrayData, &c3);

    SubTest("Gray float optimizeable transform");
    xform1 = cmsCreateTransform(DbgThread(), h1, TYPE_GRAY_FLT, h2, TYPE_GRAY_FLT, INTENT_PERCEPTUAL, 0);
    rc &= CheckFloatlinearXFORM(xform1, 1);
    cmsDeleteTransform(DbgThread(), xform1);
    if (rc == 0) goto Error;

    SubTest("Gray 8 optimizeable transform");
    xform1 = cmsCreateTransform(DbgThread(), h1, TYPE_GRAY_8, h2, TYPE_GRAY_8, INTENT_PERCEPTUAL, 0);
    rc &= Check8linearXFORM(xform1, 1);
    cmsDeleteTransform(DbgThread(), xform1);
    if (rc == 0) goto Error;

    SubTest("Gray 16 optimizeable transform");
    xform1 = cmsCreateTransform(DbgThread(), h1, TYPE_GRAY_16, h2, TYPE_GRAY_16, INTENT_PERCEPTUAL, 0);
    rc &= Check16linearXFORM(xform1, 1);
    cmsDeleteTransform(DbgThread(), xform1);
    if (rc == 0) goto Error;

    SubTest("Gray float non-optimizeable transform");
    xform1 = cmsCreateTransform(DbgThread(), h1, TYPE_GRAY_FLT, h1, TYPE_GRAY_FLT, INTENT_PERCEPTUAL, 0);
    xform2 = cmsCreateTransform(DbgThread(), h3, TYPE_GRAY_FLT, NULL, TYPE_GRAY_FLT, INTENT_PERCEPTUAL, 0);

    rc &= CompareFloatXFORM(xform1, xform2, 1);
    cmsDeleteTransform(DbgThread(), xform1);
    cmsDeleteTransform(DbgThread(), xform2);
    if (rc == 0) goto Error;

    SubTest("Gray 8 non-optimizeable transform");
    xform1 = cmsCreateTransform(DbgThread(), h1, TYPE_GRAY_8, h1, TYPE_GRAY_8, INTENT_PERCEPTUAL, 0);
    xform2 = cmsCreateTransform(DbgThread(), h3, TYPE_GRAY_8, NULL, TYPE_GRAY_8, INTENT_PERCEPTUAL, 0);

    rc &= Compare8bitXFORM(xform1, xform2, 1);
    cmsDeleteTransform(DbgThread(), xform1);
    cmsDeleteTransform(DbgThread(), xform2);
    if (rc == 0) goto Error;


    SubTest("Gray 16 non-optimizeable transform");
    xform1 = cmsCreateTransform(DbgThread(), h1, TYPE_GRAY_16, h1, TYPE_GRAY_16, INTENT_PERCEPTUAL, 0);
    xform2 = cmsCreateTransform(DbgThread(), h3, TYPE_GRAY_16, NULL, TYPE_GRAY_16, INTENT_PERCEPTUAL, 0);

    rc &= Compare16bitXFORM(xform1, xform2, 1);
    cmsDeleteTransform(DbgThread(), xform1);
    cmsDeleteTransform(DbgThread(), xform2);
    if (rc == 0) goto Error;

Error:

    cmsCloseProfile(DbgThread(), h1); cmsCloseProfile(DbgThread(), h2); cmsCloseProfile(DbgThread(), h3);
    cmsFreeToneCurve(DbgThread(), c1); cmsFreeToneCurve(DbgThread(), c2); cmsFreeToneCurve(DbgThread(), c3);

    return rc;
}
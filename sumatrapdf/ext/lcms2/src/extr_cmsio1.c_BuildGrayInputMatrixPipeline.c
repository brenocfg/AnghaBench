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
typedef  int cmsUInt16Number ;
typedef  int /*<<< orphan*/  cmsToneCurve ;
typedef  int /*<<< orphan*/  cmsPipeline ;
typedef  int /*<<< orphan*/  cmsHPROFILE ;
typedef  int /*<<< orphan*/  cmsContext ;

/* Variables and functions */
 int /*<<< orphan*/  GrayInputMatrix ; 
 int /*<<< orphan*/  OneToThreeInputMatrix ; 
 int /*<<< orphan*/  cmsAT_END ; 
 int /*<<< orphan*/ * cmsBuildTabulatedToneCurve16 (int /*<<< orphan*/ ,int,int*) ; 
 int /*<<< orphan*/  cmsFreeToneCurve (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 scalar_t__ cmsGetPCS (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * cmsPipelineAlloc (int /*<<< orphan*/ ,int,int) ; 
 int /*<<< orphan*/  cmsPipelineFree (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  cmsPipelineInsertStage (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ cmsReadTag (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  cmsSigGrayTRCTag ; 
 scalar_t__ cmsSigLabData ; 
 int /*<<< orphan*/  cmsStageAllocMatrix (int /*<<< orphan*/ ,int,int,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  cmsStageAllocToneCurves (int /*<<< orphan*/ ,int,int /*<<< orphan*/ **) ; 

__attribute__((used)) static
cmsPipeline* BuildGrayInputMatrixPipeline(cmsContext ContextID, cmsHPROFILE hProfile)
{
    cmsToneCurve *GrayTRC;
    cmsPipeline* Lut;

    GrayTRC = (cmsToneCurve *) cmsReadTag(ContextID, hProfile, cmsSigGrayTRCTag);
    if (GrayTRC == NULL) return NULL;

    Lut = cmsPipelineAlloc(ContextID, 1, 3);
    if (Lut == NULL)
        goto Error;

    if (cmsGetPCS(ContextID, hProfile) == cmsSigLabData) {

        // In this case we implement the profile as an  identity matrix plus 3 tone curves
        cmsUInt16Number Zero[2] = { 0x8080, 0x8080 };
        cmsToneCurve* EmptyTab;
        cmsToneCurve* LabCurves[3];

        EmptyTab = cmsBuildTabulatedToneCurve16(ContextID, 2, Zero);

        if (EmptyTab == NULL)
            goto Error;

        LabCurves[0] = GrayTRC;
        LabCurves[1] = EmptyTab;
        LabCurves[2] = EmptyTab;

        if (!cmsPipelineInsertStage(ContextID, Lut, cmsAT_END, cmsStageAllocMatrix(ContextID, 3,  1, OneToThreeInputMatrix, NULL)) ||
            !cmsPipelineInsertStage(ContextID, Lut, cmsAT_END, cmsStageAllocToneCurves(ContextID, 3, LabCurves))) {
                cmsFreeToneCurve(ContextID, EmptyTab);
                goto Error;
        }

        cmsFreeToneCurve(ContextID, EmptyTab);

    }
    else  {

        if (!cmsPipelineInsertStage(ContextID, Lut, cmsAT_END, cmsStageAllocToneCurves(ContextID, 1, &GrayTRC)) ||
            !cmsPipelineInsertStage(ContextID, Lut, cmsAT_END, cmsStageAllocMatrix(ContextID, 3,  1, GrayInputMatrix, NULL)))
            goto Error;
    }

    return Lut;

Error:
    cmsPipelineFree(ContextID, Lut);
    return NULL;
}
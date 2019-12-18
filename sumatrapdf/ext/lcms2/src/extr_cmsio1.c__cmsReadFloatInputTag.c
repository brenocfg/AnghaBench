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
typedef  int /*<<< orphan*/  cmsTagSignature ;
typedef  int /*<<< orphan*/  cmsPipeline ;
typedef  int /*<<< orphan*/  cmsHPROFILE ;
typedef  int /*<<< orphan*/  cmsContext ;
typedef  scalar_t__ cmsColorSpaceSignature ;

/* Variables and functions */
 int /*<<< orphan*/  _cmsStageNormalizeFromLabFloat (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  _cmsStageNormalizeFromXyzFloat (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  _cmsStageNormalizeToLabFloat (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  _cmsStageNormalizeToXyzFloat (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  cmsAT_BEGIN ; 
 int /*<<< orphan*/  cmsAT_END ; 
 scalar_t__ cmsGetColorSpace (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ cmsGetPCS (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * cmsPipelineDup (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  cmsPipelineFree (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  cmsPipelineInsertStage (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ cmsReadTag (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ cmsSigLabData ; 
 scalar_t__ cmsSigXYZData ; 

__attribute__((used)) static
cmsPipeline* _cmsReadFloatInputTag(cmsContext ContextID, cmsHPROFILE hProfile, cmsTagSignature tagFloat)
{
    cmsPipeline* Lut           = cmsPipelineDup(ContextID, (cmsPipeline*) cmsReadTag(ContextID, hProfile, tagFloat));
    cmsColorSpaceSignature spc = cmsGetColorSpace(ContextID, hProfile);
    cmsColorSpaceSignature PCS = cmsGetPCS(ContextID, hProfile);

    if (Lut == NULL) return NULL;

    // input and output of transform are in lcms 0..1 encoding.  If XYZ or Lab spaces are used,
    //  these need to be normalized into the appropriate ranges (Lab = 100,0,0, XYZ=1.0,1.0,1.0)
    if ( spc == cmsSigLabData)
    {
        if (!cmsPipelineInsertStage(ContextID, Lut, cmsAT_BEGIN, _cmsStageNormalizeToLabFloat(ContextID)))
            goto Error;
    }
    else if (spc == cmsSigXYZData)
    {
        if (!cmsPipelineInsertStage(ContextID, Lut, cmsAT_BEGIN, _cmsStageNormalizeToXyzFloat(ContextID)))
            goto Error;
    }

    if ( PCS == cmsSigLabData)
    {
        if (!cmsPipelineInsertStage(ContextID, Lut, cmsAT_END, _cmsStageNormalizeFromLabFloat(ContextID)))
            goto Error;
    }
    else if( PCS == cmsSigXYZData)
    {
        if (!cmsPipelineInsertStage(ContextID, Lut, cmsAT_END, _cmsStageNormalizeFromXyzFloat(ContextID)))
            goto Error;
    }

    return Lut;

Error:
    cmsPipelineFree(ContextID, Lut);
    return NULL;
}
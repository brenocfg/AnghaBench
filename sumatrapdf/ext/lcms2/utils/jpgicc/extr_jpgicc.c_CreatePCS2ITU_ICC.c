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
typedef  int /*<<< orphan*/  cmsStage ;
typedef  int /*<<< orphan*/  cmsPipeline ;
typedef  int /*<<< orphan*/ * cmsHPROFILE ;

/* Variables and functions */
 int /*<<< orphan*/  GRID_POINTS ; 
 int /*<<< orphan*/  PCS2ITU ; 
 int /*<<< orphan*/  cmsAT_BEGIN ; 
 int /*<<< orphan*/ * cmsCreateProfilePlaceholder (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * cmsPipelineAlloc (int /*<<< orphan*/ ,int,int) ; 
 int /*<<< orphan*/  cmsPipelineFree (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  cmsPipelineInsertStage (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  cmsSetColorSpace (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  cmsSetDeviceClass (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  cmsSetPCS (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  cmsSigBToA0Tag ; 
 int /*<<< orphan*/  cmsSigColorSpaceClass ; 
 int /*<<< orphan*/  cmsSigLabData ; 
 int /*<<< orphan*/ * cmsStageAllocCLut16bit (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,int,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  cmsStageSampleCLut16bit (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  cmsWriteTag (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 

__attribute__((used)) static
cmsHPROFILE CreatePCS2ITU_ICC(void)
{
    cmsHPROFILE hProfile;
    cmsPipeline* BToA0;
    cmsStage* ColorMap;

    BToA0 = cmsPipelineAlloc(0, 3, 3);
    if (BToA0 == NULL) return NULL;

    ColorMap = cmsStageAllocCLut16bit(0, GRID_POINTS, 3, 3, NULL);
    if (ColorMap == NULL) return NULL;

    cmsPipelineInsertStage(NULL, BToA0, cmsAT_BEGIN, ColorMap);
    cmsStageSampleCLut16bit(NULL, ColorMap, PCS2ITU, NULL, 0);

    hProfile = cmsCreateProfilePlaceholder(0);
    if (hProfile == NULL) {
        cmsPipelineFree(NULL, BToA0);
        return NULL;
    }

    cmsWriteTag(NULL, hProfile, cmsSigBToA0Tag, BToA0);
    cmsSetColorSpace(NULL, hProfile, cmsSigLabData);
    cmsSetPCS(NULL, hProfile, cmsSigLabData);
    cmsSetDeviceClass(NULL, hProfile, cmsSigColorSpaceClass);

    cmsPipelineFree(NULL, BToA0);

    return hProfile;
}
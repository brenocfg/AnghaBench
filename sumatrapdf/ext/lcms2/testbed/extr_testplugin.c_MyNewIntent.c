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
typedef  size_t cmsUInt32Number ;
typedef  int /*<<< orphan*/  cmsPipeline ;
typedef  int /*<<< orphan*/  cmsHPROFILE ;
typedef  int /*<<< orphan*/  cmsFloat64Number ;
typedef  int /*<<< orphan*/  cmsContext ;
typedef  int /*<<< orphan*/  cmsBool ;

/* Variables and functions */
 size_t INTENT_DECEPTIVE ; 
 size_t INTENT_PERCEPTUAL ; 
 int /*<<< orphan*/ * _cmsDefaultICCintents (int /*<<< orphan*/ ,size_t,size_t*,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *,size_t) ; 
 int /*<<< orphan*/  cmsAT_BEGIN ; 
 scalar_t__ cmsGetColorSpace (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * cmsPipelineAlloc (int /*<<< orphan*/ ,int,int) ; 
 int /*<<< orphan*/  cmsPipelineInsertStage (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ cmsSigGrayData ; 
 int /*<<< orphan*/  cmsStageAllocIdentity (int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static
cmsPipeline*  MyNewIntent(cmsContext      ContextID,
                          cmsUInt32Number nProfiles,
                          cmsUInt32Number TheIntents[],
                          cmsHPROFILE     hProfiles[],
                          cmsBool         BPC[],
                          cmsFloat64Number AdaptationStates[],
                          cmsUInt32Number dwFlags)
{
    cmsPipeline*    Result;
    cmsUInt32Number ICCIntents[256];
    cmsUInt32Number i;

 for (i=0; i < nProfiles; i++)
        ICCIntents[i] = (TheIntents[i] == INTENT_DECEPTIVE) ? INTENT_PERCEPTUAL :
                                                 TheIntents[i];

 if (cmsGetColorSpace(ContextID, hProfiles[0]) != cmsSigGrayData ||
     cmsGetColorSpace(ContextID, hProfiles[nProfiles-1]) != cmsSigGrayData)
           return _cmsDefaultICCintents(ContextID, nProfiles,
                                   ICCIntents, hProfiles,
                                   BPC, AdaptationStates,
                                   dwFlags);

    Result = cmsPipelineAlloc(ContextID, 1, 1);
    if (Result == NULL) return NULL;

    cmsPipelineInsertStage(ContextID, Result, cmsAT_BEGIN,
                            cmsStageAllocIdentity(ContextID, 1));

    return Result;
}
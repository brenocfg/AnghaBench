#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
typedef  int cmsUInt32Number ;
typedef  int /*<<< orphan*/  cmsStage ;
typedef  int /*<<< orphan*/  cmsPipeline ;
typedef  int /*<<< orphan*/  cmsHPROFILE ;
typedef  int /*<<< orphan*/  cmsFloat64Number ;
typedef  int /*<<< orphan*/  cmsContext ;
typedef  int /*<<< orphan*/  cmsBool ;
typedef  int /*<<< orphan*/  bp ;
struct TYPE_3__ {int /*<<< orphan*/ * KTone; int /*<<< orphan*/ * cmyk2cmyk; } ;
typedef  TYPE_1__ GrayOnlyParams ;

/* Variables and functions */
 int /*<<< orphan*/  BlackPreservingGrayOnlySampler ; 
 int /*<<< orphan*/ * DefaultICCintents (int /*<<< orphan*/ ,int,int*,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int) ; 
 int TranslateNonICCIntents (int) ; 
 int /*<<< orphan*/ * _cmsBuildKToneCurve (int /*<<< orphan*/ ,int,int,int*,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int) ; 
 int _cmsReasonableGridpointsByColorspace (int /*<<< orphan*/ ,scalar_t__,int) ; 
 int /*<<< orphan*/  cmsAT_BEGIN ; 
 int /*<<< orphan*/  cmsFreeToneCurve (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 scalar_t__ cmsGetColorSpace (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * cmsPipelineAlloc (int /*<<< orphan*/ ,int,int) ; 
 int /*<<< orphan*/  cmsPipelineFree (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  cmsPipelineInsertStage (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 scalar_t__ cmsSigCmykData ; 
 int /*<<< orphan*/ * cmsStageAllocCLut16bit (int /*<<< orphan*/ ,int,int,int,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  cmsStageSampleCLut16bit (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ,void*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  memset (TYPE_1__*,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static
cmsPipeline*  BlackPreservingKOnlyIntents(cmsContext     ContextID,
                                          cmsUInt32Number nProfiles,
                                          cmsUInt32Number TheIntents[],
                                          cmsHPROFILE     hProfiles[],
                                          cmsBool         BPC[],
                                          cmsFloat64Number AdaptationStates[],
                                          cmsUInt32Number dwFlags)
{
    GrayOnlyParams  bp;
    cmsPipeline*    Result;
    cmsUInt32Number ICCIntents[256];
    cmsStage*         CLUT;
    cmsUInt32Number i, nGridPoints;


    // Sanity check
    if (nProfiles < 1 || nProfiles > 255) return NULL;

    // Translate black-preserving intents to ICC ones
    for (i=0; i < nProfiles; i++)
        ICCIntents[i] = TranslateNonICCIntents(TheIntents[i]);

    // Check for non-cmyk profiles
    if (cmsGetColorSpace(ContextID, hProfiles[0]) != cmsSigCmykData ||
        cmsGetColorSpace(ContextID, hProfiles[nProfiles-1]) != cmsSigCmykData)
           return DefaultICCintents(ContextID, nProfiles, ICCIntents, hProfiles, BPC, AdaptationStates, dwFlags);

    memset(&bp, 0, sizeof(bp));

    // Allocate an empty LUT for holding the result
    Result = cmsPipelineAlloc(ContextID, 4, 4);
    if (Result == NULL) return NULL;

    // Create a LUT holding normal ICC transform
    bp.cmyk2cmyk = DefaultICCintents(ContextID,
        nProfiles,
        ICCIntents,
        hProfiles,
        BPC,
        AdaptationStates,
        dwFlags);

    if (bp.cmyk2cmyk == NULL) goto Error;

    // Now, compute the tone curve
    bp.KTone = _cmsBuildKToneCurve(ContextID,
        4096,
        nProfiles,
        ICCIntents,
        hProfiles,
        BPC,
        AdaptationStates,
        dwFlags);

    if (bp.KTone == NULL) goto Error;


    // How many gridpoints are we going to use?
    nGridPoints = _cmsReasonableGridpointsByColorspace(ContextID, cmsSigCmykData, dwFlags);

    // Create the CLUT. 16 bits
    CLUT = cmsStageAllocCLut16bit(ContextID, nGridPoints, 4, 4, NULL);
    if (CLUT == NULL) goto Error;

    // This is the one and only MPE in this LUT
    if (!cmsPipelineInsertStage(ContextID, Result, cmsAT_BEGIN, CLUT))
        goto Error;

    // Sample it. We cannot afford pre/post linearization this time.
    if (!cmsStageSampleCLut16bit(ContextID, CLUT, BlackPreservingGrayOnlySampler, (void*) &bp, 0))
        goto Error;

    // Get rid of xform and tone curve
    cmsPipelineFree(ContextID, bp.cmyk2cmyk);
    cmsFreeToneCurve(ContextID, bp.KTone);

    return Result;

Error:

    if (bp.cmyk2cmyk != NULL) cmsPipelineFree(ContextID, bp.cmyk2cmyk);
    if (bp.KTone != NULL)  cmsFreeToneCurve(ContextID, bp.KTone);
    if (Result != NULL) cmsPipelineFree(ContextID, Result);
    return NULL;

}
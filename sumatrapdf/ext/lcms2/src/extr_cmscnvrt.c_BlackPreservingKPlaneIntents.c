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
struct TYPE_3__ {double MaxTAC; int /*<<< orphan*/ * LabK2cmyk; int /*<<< orphan*/ * KTone; int /*<<< orphan*/ * hProofOutput; int /*<<< orphan*/ * cmyk2Lab; int /*<<< orphan*/ * cmyk2cmyk; scalar_t__ MaxError; } ;
typedef  TYPE_1__ PreserveKPlaneParams ;

/* Variables and functions */
 int BYTES_SH (int) ; 
 int /*<<< orphan*/  BlackPreservingSampler ; 
 int CHANNELS_SH (int) ; 
 int /*<<< orphan*/ * DefaultICCintents (int /*<<< orphan*/ ,int,int*,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int) ; 
 int FLOAT_SH (int) ; 
 int /*<<< orphan*/  INTENT_RELATIVE_COLORIMETRIC ; 
 int TYPE_Lab_DBL ; 
 int TranslateNonICCIntents (int) ; 
 int /*<<< orphan*/ * _cmsBuildKToneCurve (int /*<<< orphan*/ ,int,int,int*,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/ * _cmsReadInputLUT (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int _cmsReasonableGridpointsByColorspace (int /*<<< orphan*/ ,scalar_t__,int) ; 
 int /*<<< orphan*/  cmsAT_BEGIN ; 
 int /*<<< orphan*/  cmsCloseProfile (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  cmsCreateLab4Profile (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 void* cmsCreateTransform (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,int /*<<< orphan*/ ,int,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  cmsDeleteTransform (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 double cmsDetectTAC (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int cmsFLAGS_NOCACHE ; 
 int cmsFLAGS_NOOPTIMIZE ; 
 int /*<<< orphan*/  cmsFreeToneCurve (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 scalar_t__ cmsGetColorSpace (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ cmsGetDeviceClass (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * cmsPipelineAlloc (int /*<<< orphan*/ ,int,int) ; 
 int /*<<< orphan*/  cmsPipelineFree (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  cmsPipelineInsertStage (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 scalar_t__ cmsSigCmykData ; 
 scalar_t__ cmsSigOutputClass ; 
 int /*<<< orphan*/ * cmsStageAllocCLut16bit (int /*<<< orphan*/ ,int,int,int,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  cmsStageSampleCLut16bit (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ,void*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  memset (TYPE_1__*,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static
cmsPipeline* BlackPreservingKPlaneIntents(cmsContext     ContextID,
                                          cmsUInt32Number nProfiles,
                                          cmsUInt32Number TheIntents[],
                                          cmsHPROFILE     hProfiles[],
                                          cmsBool         BPC[],
                                          cmsFloat64Number AdaptationStates[],
                                          cmsUInt32Number dwFlags)
{
    PreserveKPlaneParams bp;
    cmsPipeline*    Result = NULL;
    cmsUInt32Number ICCIntents[256];
    cmsStage*         CLUT;
    cmsUInt32Number i, nGridPoints;
    cmsHPROFILE hLab;

    // Sanity check
    if (nProfiles < 1 || nProfiles > 255) return NULL;

    // Translate black-preserving intents to ICC ones
    for (i=0; i < nProfiles; i++)
        ICCIntents[i] = TranslateNonICCIntents(TheIntents[i]);

    // Check for non-cmyk profiles
    if (cmsGetColorSpace(ContextID, hProfiles[0]) != cmsSigCmykData ||
        !(cmsGetColorSpace(ContextID, hProfiles[nProfiles-1]) == cmsSigCmykData ||
        cmsGetDeviceClass(ContextID, hProfiles[nProfiles-1]) == cmsSigOutputClass))
           return  DefaultICCintents(ContextID, nProfiles, ICCIntents, hProfiles, BPC, AdaptationStates, dwFlags);

    // Allocate an empty LUT for holding the result
    Result = cmsPipelineAlloc(ContextID, 4, 4);
    if (Result == NULL) return NULL;


    memset(&bp, 0, sizeof(bp));

    // We need the input LUT of the last profile, assuming this one is responsible of
    // black generation. This LUT will be searched in inverse order.
    bp.LabK2cmyk = _cmsReadInputLUT(ContextID, hProfiles[nProfiles-1], INTENT_RELATIVE_COLORIMETRIC);
    if (bp.LabK2cmyk == NULL) goto Cleanup;

    // Get total area coverage (in 0..1 domain)
    bp.MaxTAC = cmsDetectTAC(ContextID, hProfiles[nProfiles-1]) / 100.0;
    if (bp.MaxTAC <= 0) goto Cleanup;


    // Create a LUT holding normal ICC transform
    bp.cmyk2cmyk = DefaultICCintents(ContextID,
                                         nProfiles,
                                         ICCIntents,
                                         hProfiles,
                                         BPC,
                                         AdaptationStates,
                                         dwFlags);
    if (bp.cmyk2cmyk == NULL) goto Cleanup;

    // Now the tone curve
    bp.KTone = _cmsBuildKToneCurve(ContextID, 4096, nProfiles,
                                   ICCIntents,
                                   hProfiles,
                                   BPC,
                                   AdaptationStates,
                                   dwFlags);
    if (bp.KTone == NULL) goto Cleanup;

    // To measure the output, Last profile to Lab
    hLab = cmsCreateLab4Profile(ContextID, NULL);
    bp.hProofOutput = cmsCreateTransform(ContextID, hProfiles[nProfiles-1],
                                         CHANNELS_SH(4)|BYTES_SH(2), hLab, TYPE_Lab_DBL,
                                         INTENT_RELATIVE_COLORIMETRIC,
                                         cmsFLAGS_NOCACHE|cmsFLAGS_NOOPTIMIZE);
    if ( bp.hProofOutput == NULL) goto Cleanup;

    // Same as anterior, but lab in the 0..1 range
    bp.cmyk2Lab = cmsCreateTransform(ContextID, hProfiles[nProfiles-1],
                                         FLOAT_SH(1)|CHANNELS_SH(4)|BYTES_SH(4), hLab,
                                         FLOAT_SH(1)|CHANNELS_SH(3)|BYTES_SH(4),
                                         INTENT_RELATIVE_COLORIMETRIC,
                                         cmsFLAGS_NOCACHE|cmsFLAGS_NOOPTIMIZE);
    if (bp.cmyk2Lab == NULL) goto Cleanup;
    cmsCloseProfile(ContextID, hLab);

    // Error estimation (for debug only)
    bp.MaxError = 0;

    // How many gridpoints are we going to use?
    nGridPoints = _cmsReasonableGridpointsByColorspace(ContextID, cmsSigCmykData, dwFlags);


    CLUT = cmsStageAllocCLut16bit(ContextID, nGridPoints, 4, 4, NULL);
    if (CLUT == NULL) goto Cleanup;

    if (!cmsPipelineInsertStage(ContextID, Result, cmsAT_BEGIN, CLUT))
        goto Cleanup;

    cmsStageSampleCLut16bit(ContextID, CLUT, BlackPreservingSampler, (void*) &bp, 0);

Cleanup:

    if (bp.cmyk2cmyk) cmsPipelineFree(ContextID, bp.cmyk2cmyk);
    if (bp.cmyk2Lab) cmsDeleteTransform(ContextID, bp.cmyk2Lab);
    if (bp.hProofOutput) cmsDeleteTransform(ContextID, bp.hProofOutput);

    if (bp.KTone) cmsFreeToneCurve(ContextID, bp.KTone);
    if (bp.LabK2cmyk) cmsPipelineFree(ContextID, bp.LabK2cmyk);

    return Result;
}
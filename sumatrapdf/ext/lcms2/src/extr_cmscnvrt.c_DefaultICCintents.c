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
typedef  int /*<<< orphan*/  cmsVEC3 ;
typedef  size_t cmsUInt32Number ;
typedef  int /*<<< orphan*/  cmsStage ;
typedef  scalar_t__ cmsProfileClassSignature ;
typedef  int /*<<< orphan*/  cmsPipeline ;
typedef  int /*<<< orphan*/  cmsMAT3 ;
typedef  int /*<<< orphan*/  cmsHPROFILE ;
typedef  int /*<<< orphan*/  cmsFloat64Number ;
typedef  int /*<<< orphan*/  cmsContext ;
typedef  scalar_t__ cmsColorSpaceSignature ;
typedef  int cmsBool ;

/* Variables and functions */
 int /*<<< orphan*/  AddConversion (int /*<<< orphan*/ ,int /*<<< orphan*/ *,scalar_t__,scalar_t__,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  ColorSpaceIsCompatible (scalar_t__,scalar_t__) ; 
 int /*<<< orphan*/  ComputeConversion (int /*<<< orphan*/ ,size_t,int /*<<< orphan*/ *,size_t,int,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int TRUE ; 
 int /*<<< orphan*/  _cmsMAT3identity (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * _cmsReadDevicelinkLUT (int /*<<< orphan*/ ,int /*<<< orphan*/ ,size_t) ; 
 int /*<<< orphan*/ * _cmsReadInputLUT (int /*<<< orphan*/ ,int /*<<< orphan*/ ,size_t) ; 
 int /*<<< orphan*/ * _cmsReadOutputLUT (int /*<<< orphan*/ ,int /*<<< orphan*/ ,size_t) ; 
 int /*<<< orphan*/ * _cmsStageClipNegatives (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  _cmsVEC3init (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  cmsAT_END ; 
 int /*<<< orphan*/  cmsChannelsOf (int /*<<< orphan*/ ,scalar_t__) ; 
 int /*<<< orphan*/  cmsERROR_COLORSPACE_CHECK ; 
 size_t cmsFLAGS_NONEGATIVES ; 
 scalar_t__ cmsGetColorSpace (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ cmsGetDeviceClass (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ cmsGetPCS (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * cmsPipelineAlloc (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  cmsPipelineCat (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  cmsPipelineFree (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  cmsPipelineInsertStage (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 scalar_t__ cmsSigAbstractClass ; 
 scalar_t__ cmsSigCmykData ; 
 scalar_t__ cmsSigGrayData ; 
 scalar_t__ cmsSigLabData ; 
 scalar_t__ cmsSigLinkClass ; 
 scalar_t__ cmsSigNamedColorClass ; 
 scalar_t__ cmsSigRgbData ; 
 scalar_t__ cmsSigXYZData ; 
 int /*<<< orphan*/  cmsSignalError (int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  cmsUNUSED_PARAMETER (size_t) ; 

__attribute__((used)) static
cmsPipeline* DefaultICCintents(cmsContext       ContextID,
                               cmsUInt32Number  nProfiles,
                               cmsUInt32Number  TheIntents[],
                               cmsHPROFILE      hProfiles[],
                               cmsBool          BPC[],
                               cmsFloat64Number AdaptationStates[],
                               cmsUInt32Number  dwFlags)
{
    cmsPipeline* Lut = NULL;
    cmsPipeline* Result;
    cmsHPROFILE hProfile;
    cmsMAT3 m;
    cmsVEC3 off;
    cmsColorSpaceSignature ColorSpaceIn, ColorSpaceOut = cmsSigLabData, CurrentColorSpace;
    cmsProfileClassSignature ClassSig;
    cmsUInt32Number  i, Intent;

    // For safety
    if (nProfiles == 0) return NULL;

    // Allocate an empty LUT for holding the result. 0 as channel count means 'undefined'
    Result = cmsPipelineAlloc(ContextID, 0, 0);
    if (Result == NULL) return NULL;

    CurrentColorSpace = cmsGetColorSpace(ContextID, hProfiles[0]);

    for (i=0; i < nProfiles; i++) {

        cmsBool  lIsDeviceLink, lIsInput;

        hProfile      = hProfiles[i];
        ClassSig      = cmsGetDeviceClass(ContextID, hProfile);
        lIsDeviceLink = (ClassSig == cmsSigLinkClass || ClassSig == cmsSigAbstractClass );

        // First profile is used as input unless devicelink or abstract
        if ((i == 0) && !lIsDeviceLink) {
            lIsInput = TRUE;
        }
        else {
          // Else use profile in the input direction if current space is not PCS
        lIsInput      = (CurrentColorSpace != cmsSigXYZData) &&
                        (CurrentColorSpace != cmsSigLabData);
        }

        Intent        = TheIntents[i];

        if (lIsInput || lIsDeviceLink) {

            ColorSpaceIn    = cmsGetColorSpace(ContextID, hProfile);
            ColorSpaceOut   = cmsGetPCS(ContextID, hProfile);
        }
        else {

            ColorSpaceIn    = cmsGetPCS(ContextID, hProfile);
            ColorSpaceOut   = cmsGetColorSpace(ContextID, hProfile);
        }

        if (!ColorSpaceIsCompatible(ColorSpaceIn, CurrentColorSpace)) {

            cmsSignalError(ContextID, cmsERROR_COLORSPACE_CHECK, "ColorSpace mismatch");
            goto Error;
        }

        // If devicelink is found, then no custom intent is allowed and we can
        // read the LUT to be applied. Settings don't apply here.
        if (lIsDeviceLink || ((ClassSig == cmsSigNamedColorClass) && (nProfiles == 1))) {

            // Get the involved LUT from the profile
            Lut = _cmsReadDevicelinkLUT(ContextID, hProfile, Intent);
            if (Lut == NULL) goto Error;

            // What about abstract profiles?
             if (ClassSig == cmsSigAbstractClass && i > 0) {
                if (!ComputeConversion(ContextID, i, hProfiles, Intent, BPC[i], AdaptationStates[i], &m, &off)) goto Error;
             }
             else {
                _cmsMAT3identity(ContextID, &m);
                _cmsVEC3init(ContextID, &off, 0, 0, 0);
             }


            if (!AddConversion(ContextID, Result, CurrentColorSpace, ColorSpaceIn, &m, &off)) goto Error;

        }
        else {

            if (lIsInput) {
                // Input direction means non-pcs connection, so proceed like devicelinks
                Lut = _cmsReadInputLUT(ContextID, hProfile, Intent);
                if (Lut == NULL) goto Error;
            }
            else {

                // Output direction means PCS connection. Intent may apply here
                Lut = _cmsReadOutputLUT(ContextID, hProfile, Intent);
                if (Lut == NULL) goto Error;


                if (!ComputeConversion(ContextID, i, hProfiles, Intent, BPC[i], AdaptationStates[i], &m, &off)) goto Error;
                if (!AddConversion(ContextID, Result, CurrentColorSpace, ColorSpaceIn, &m, &off)) goto Error;

            }
        }

        // Concatenate to the output LUT
        if (!cmsPipelineCat(ContextID, Result, Lut))
            goto Error;

        cmsPipelineFree(ContextID, Lut);
        Lut = NULL;

        // Update current space
        CurrentColorSpace = ColorSpaceOut;
    }

    // Check for non-negatives clip
    if (dwFlags & cmsFLAGS_NONEGATIVES) {

           if (ColorSpaceOut == cmsSigGrayData ||
                  ColorSpaceOut == cmsSigRgbData ||
                  ColorSpaceOut == cmsSigCmykData) {

                  cmsStage* clip = _cmsStageClipNegatives(ContextID, cmsChannelsOf(ContextID, ColorSpaceOut));
                  if (clip == NULL) goto Error;

                  if (!cmsPipelineInsertStage(ContextID, Result, cmsAT_END, clip))
                         goto Error;
           }

    }

    return Result;

Error:

    if (Lut != NULL) cmsPipelineFree(ContextID, Lut);
    if (Result != NULL) cmsPipelineFree(ContextID, Result);
    return NULL;

    cmsUNUSED_PARAMETER(dwFlags);
}
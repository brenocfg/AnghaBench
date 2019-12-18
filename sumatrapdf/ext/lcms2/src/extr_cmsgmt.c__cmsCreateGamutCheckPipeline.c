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
typedef  int /*<<< orphan*/ * cmsHPROFILE ;
typedef  double cmsFloat64Number ;
typedef  int /*<<< orphan*/  cmsContext ;
typedef  int /*<<< orphan*/  cmsColorSpaceSignature ;
typedef  scalar_t__ cmsBool ;
struct TYPE_3__ {double Thereshold; void* hReverse; void* hForward; void* hInput; } ;
typedef  TYPE_1__ GAMUTCHAIN ;

/* Variables and functions */
 int BYTES_SH (int) ; 
 int CHANNELS_SH (int) ; 
 double ERR_THERESHOLD ; 
 int /*<<< orphan*/  GamutSampler ; 
 int INTENT_RELATIVE_COLORIMETRIC ; 
 int TYPE_Lab_DBL ; 
 int _cmsReasonableGridpointsByColorspace (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  cmsAT_BEGIN ; 
 int cmsChannelsOf (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  cmsCloseProfile (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 void* cmsCreateExtendedTransform (int /*<<< orphan*/ ,int,int /*<<< orphan*/ **,scalar_t__*,int*,double*,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * cmsCreateLab4Profile (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 void* cmsCreateTransform (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int,int /*<<< orphan*/ *,int,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  cmsDeleteTransform (int /*<<< orphan*/ ,void*) ; 
 int /*<<< orphan*/  cmsERROR_RANGE ; 
 int /*<<< orphan*/  cmsFLAGS_HIGHRESPRECALC ; 
 int /*<<< orphan*/  cmsFLAGS_NOCACHE ; 
 int /*<<< orphan*/  cmsGetColorSpace (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 scalar_t__ cmsIsMatrixShaper (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * cmsPipelineAlloc (int /*<<< orphan*/ ,int,int) ; 
 int /*<<< orphan*/  cmsPipelineFree (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  cmsPipelineInsertStage (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  cmsSignalError (int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*,int) ; 
 int /*<<< orphan*/ * cmsStageAllocCLut16bit (int /*<<< orphan*/ ,int,int,int,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  cmsStageSampleCLut16bit (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ,void*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  memset (TYPE_1__*,int /*<<< orphan*/ ,int) ; 

cmsPipeline* _cmsCreateGamutCheckPipeline(cmsContext ContextID,
                                          cmsHPROFILE hProfiles[],
                                          cmsBool  BPC[],
                                          cmsUInt32Number Intents[],
                                          cmsFloat64Number AdaptationStates[],
                                          cmsUInt32Number nGamutPCSposition,
                                          cmsHPROFILE hGamut)
{
    cmsHPROFILE hLab;
    cmsPipeline* Gamut;
    cmsStage* CLUT;
    cmsUInt32Number dwFormat;
    GAMUTCHAIN Chain;
    cmsUInt32Number nChannels, nGridpoints;
    cmsColorSpaceSignature ColorSpace;
    cmsUInt32Number i;
    cmsHPROFILE ProfileList[256];
    cmsBool     BPCList[256];
    cmsFloat64Number AdaptationList[256];
    cmsUInt32Number IntentList[256];

    memset(&Chain, 0, sizeof(GAMUTCHAIN));


    if (nGamutPCSposition <= 0 || nGamutPCSposition > 255) {
        cmsSignalError(ContextID, cmsERROR_RANGE, "Wrong position of PCS. 1..255 expected, %d found.", nGamutPCSposition);
        return NULL;
    }

    hLab = cmsCreateLab4Profile(ContextID, NULL);
    if (hLab == NULL) return NULL;


    // The figure of merit. On matrix-shaper profiles, should be almost zero as
    // the conversion is pretty exact. On LUT based profiles, different resolutions
    // of input and output CLUT may result in differences.

    if (cmsIsMatrixShaper(ContextID, hGamut)) {

        Chain.Thereshold = 1.0;
    }
    else {
        Chain.Thereshold = ERR_THERESHOLD;
    }


    // Create a copy of parameters
    for (i=0; i < nGamutPCSposition; i++) {
        ProfileList[i]    = hProfiles[i];
        BPCList[i]        = BPC[i];
        AdaptationList[i] = AdaptationStates[i];
        IntentList[i]     = Intents[i];
    }

    // Fill Lab identity
    ProfileList[nGamutPCSposition] = hLab;
    BPCList[nGamutPCSposition] = 0;
    AdaptationList[nGamutPCSposition] = 1.0;
    IntentList[nGamutPCSposition] = INTENT_RELATIVE_COLORIMETRIC;


    ColorSpace  = cmsGetColorSpace(ContextID, hGamut);

    nChannels   = cmsChannelsOf(ContextID, ColorSpace);
    nGridpoints = _cmsReasonableGridpointsByColorspace(ContextID, ColorSpace, cmsFLAGS_HIGHRESPRECALC);
    dwFormat    = (CHANNELS_SH(nChannels)|BYTES_SH(2));

    // 16 bits to Lab double
    Chain.hInput = cmsCreateExtendedTransform(ContextID,
        nGamutPCSposition + 1,
        ProfileList,
        BPCList,
        IntentList,
        AdaptationList,
        NULL, 0,
        dwFormat, TYPE_Lab_DBL,
        cmsFLAGS_NOCACHE);


    // Does create the forward step. Lab double to device
    dwFormat    = (CHANNELS_SH(nChannels)|BYTES_SH(2));
    Chain.hForward = cmsCreateTransform(ContextID,
        hLab, TYPE_Lab_DBL,
        hGamut, dwFormat,
        INTENT_RELATIVE_COLORIMETRIC,
        cmsFLAGS_NOCACHE);

    // Does create the backwards step
    Chain.hReverse = cmsCreateTransform(ContextID, hGamut, dwFormat,
        hLab, TYPE_Lab_DBL,
        INTENT_RELATIVE_COLORIMETRIC,
        cmsFLAGS_NOCACHE);


    // All ok?
    if (Chain.hInput && Chain.hForward && Chain.hReverse) {

        // Go on, try to compute gamut LUT from PCS. This consist on a single channel containing
        // dE when doing a transform back and forth on the colorimetric intent.

        Gamut = cmsPipelineAlloc(ContextID, 3, 1);
        if (Gamut != NULL) {

            CLUT = cmsStageAllocCLut16bit(ContextID, nGridpoints, nChannels, 1, NULL);
            if (!cmsPipelineInsertStage(ContextID, Gamut, cmsAT_BEGIN, CLUT)) {
                cmsPipelineFree(ContextID, Gamut);
                Gamut = NULL;
            }
            else {
                cmsStageSampleCLut16bit(ContextID, CLUT, GamutSampler, (void*) &Chain, 0);
            }
        }
    }
    else
        Gamut = NULL;   // Didn't work...

    // Free all needed stuff.
    if (Chain.hInput)   cmsDeleteTransform(ContextID, Chain.hInput);
    if (Chain.hForward) cmsDeleteTransform(ContextID, Chain.hForward);
    if (Chain.hReverse) cmsDeleteTransform(ContextID, Chain.hReverse);
    if (hLab) cmsCloseProfile(ContextID, hLab);

    // And return computed hull
    return Gamut;
}
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
typedef  int /*<<< orphan*/  cmsUInt32Number ;
typedef  int /*<<< orphan*/ * cmsHTRANSFORM ;
typedef  int /*<<< orphan*/ * cmsHPROFILE ;
typedef  int /*<<< orphan*/  TIFF ;

/* Variables and functions */
 scalar_t__ BlackWhiteCompensation ; 
 int /*<<< orphan*/  ComputeOutputFormatDescriptor (int /*<<< orphan*/ ,int,int) ; 
 int /*<<< orphan*/  CopyOtherTags (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  DoEmbedProfile (int /*<<< orphan*/ *,char const*) ; 
 scalar_t__ EmbedProfile ; 
 int /*<<< orphan*/  FatalError (char*,...) ; 
 scalar_t__ GamutCheck ; 
 int /*<<< orphan*/  GetInputPixelType (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * GetTIFFProfile (int /*<<< orphan*/ *) ; 
 double InkLimit ; 
 int /*<<< orphan*/  Intent ; 
 int /*<<< orphan*/  ObserverAdaptationState ; 
 int /*<<< orphan*/ * OpenStockProfile (int /*<<< orphan*/ *,char const*) ; 
 int PT_CMY ; 
 int PT_CMYK ; 
 int PrecalcMode ; 
 int /*<<< orphan*/  ProofingIntent ; 
 int /*<<< orphan*/  StripBasedXform (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int) ; 
 scalar_t__ TIFFIsTiled (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  TIFFWriteDirectory (int /*<<< orphan*/ *) ; 
 int T_CHANNELS (int /*<<< orphan*/ ) ; 
 scalar_t__ T_COLORSPACE (int /*<<< orphan*/ ) ; 
 int T_EXTRA (int /*<<< orphan*/ ) ; 
 scalar_t__ T_PLANAR (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  TileBasedXform (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int) ; 
 int Width ; 
 int /*<<< orphan*/  WriteOutputTags (int /*<<< orphan*/ *,int,int) ; 
 int _cmsLCMScolorSpace (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 char const* cOutProf ; 
 char const* cProofing ; 
 int /*<<< orphan*/  cmsCloseProfile (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * cmsCreateInkLimitingDeviceLink (int /*<<< orphan*/ ,double) ; 
 int /*<<< orphan*/ * cmsCreateMultiprofileTransform (int /*<<< orphan*/ **,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * cmsCreateProofingTransform (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  cmsDeleteTransform (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  cmsFLAGS_BLACKPOINTCOMPENSATION ; 
 int /*<<< orphan*/  cmsFLAGS_GAMUTCHECK ; 
 int /*<<< orphan*/  cmsFLAGS_HIGHRESPRECALC ; 
 int /*<<< orphan*/  cmsFLAGS_LOWRESPRECALC ; 
 int /*<<< orphan*/  cmsFLAGS_NOOPTIMIZE ; 
 int /*<<< orphan*/  cmsFLAGS_SOFTPROOFING ; 
 int /*<<< orphan*/  cmsGetColorSpace (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  cmsGetPCS (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * cmsOpenProfileFromFile (char const*,char*) ; 
 int /*<<< orphan*/  cmsSetAdaptationState (int /*<<< orphan*/ ) ; 
 scalar_t__ lIsDeviceLink ; 

__attribute__((used)) static
int TransformImage(TIFF* in, TIFF* out, const char *cDefInpProf)
{
    cmsHPROFILE hIn, hOut, hProof, hInkLimit = NULL;
    cmsHTRANSFORM xform;
    cmsUInt32Number wInput, wOutput;
    int OutputColorSpace;
    int bps = Width / 8;
    cmsUInt32Number dwFlags = 0;
    int nPlanes;

    // Observer adaptation state (only meaningful on absolute colorimetric intent)

    cmsSetAdaptationState(ObserverAdaptationState);

    if (EmbedProfile && cOutProf)
        DoEmbedProfile(out, cOutProf);

    if (BlackWhiteCompensation)
        dwFlags |= cmsFLAGS_BLACKPOINTCOMPENSATION;


    switch (PrecalcMode) {

       case 0: dwFlags |= cmsFLAGS_NOOPTIMIZE; break;
       case 2: dwFlags |= cmsFLAGS_HIGHRESPRECALC; break;
       case 3: dwFlags |= cmsFLAGS_LOWRESPRECALC; break;
       case 1: break;

       default: FatalError("Unknown precalculation mode '%d'", PrecalcMode);
    }


    if (GamutCheck)
        dwFlags |= cmsFLAGS_GAMUTCHECK;

    hProof = NULL;
    hOut = NULL;

    if (lIsDeviceLink) {

        hIn = cmsOpenProfileFromFile(cDefInpProf, "r");
    }
    else {

        hIn =  GetTIFFProfile(in);

        if (hIn == NULL)
            hIn = OpenStockProfile(NULL, cDefInpProf);

        hOut = OpenStockProfile(NULL, cOutProf);

        if (cProofing != NULL) {

            hProof = OpenStockProfile(NULL, cProofing);
            dwFlags |= cmsFLAGS_SOFTPROOFING;
        }
    }

    // Take input color space

    wInput = GetInputPixelType(in);

    // Assure both, input profile and input TIFF are on same colorspace

    if (_cmsLCMScolorSpace(NULL, cmsGetColorSpace(NULL, hIn)) != (int) T_COLORSPACE(wInput))
        FatalError("Input profile is not operating in proper color space");


    if (!lIsDeviceLink)
        OutputColorSpace = _cmsLCMScolorSpace(NULL, cmsGetColorSpace(NULL, hOut));
    else
        OutputColorSpace = _cmsLCMScolorSpace(NULL, cmsGetPCS(NULL, hIn));

    wOutput  = ComputeOutputFormatDescriptor(wInput, OutputColorSpace, bps);

    WriteOutputTags(out, OutputColorSpace, bps);
    CopyOtherTags(in, out);

    // Ink limit
    if (InkLimit != 400.0 &&
        (OutputColorSpace == PT_CMYK || OutputColorSpace == PT_CMY)) {

            cmsHPROFILE hProfiles[10];
            int nProfiles = 0;


            hInkLimit = cmsCreateInkLimitingDeviceLink(cmsGetColorSpace(NULL, hOut), InkLimit);

            hProfiles[nProfiles++] = hIn;
            if (hProof) {
                hProfiles[nProfiles++] = hProof;
                hProfiles[nProfiles++] = hProof;
            }

            hProfiles[nProfiles++] = hOut;
            hProfiles[nProfiles++] = hInkLimit;

            xform = cmsCreateMultiprofileTransform(hProfiles, nProfiles,
                                                   wInput, wOutput, Intent, dwFlags);

    }
    else {

        xform = cmsCreateProofingTransform(hIn, wInput,
                                           hOut, wOutput,
                                           hProof, Intent,
                                           ProofingIntent,
                                           dwFlags);
    }

    cmsCloseProfile(NULL, hIn);
    cmsCloseProfile(NULL, hOut);

    if (hInkLimit)
        cmsCloseProfile(NULL, hInkLimit);
    if (hProof)
        cmsCloseProfile(NULL, hProof);

    if (xform == NULL) return 0;

    // Planar stuff
    if (T_PLANAR(wInput))
        nPlanes = T_CHANNELS(wInput) + T_EXTRA(wInput);
    else
        nPlanes = 1;


    // Handle tile by tile or strip by strip
    if (TIFFIsTiled(in)) {

        TileBasedXform(xform, in, out, nPlanes);
    }
    else {
        StripBasedXform(xform, in, out, nPlanes);
    }


    cmsDeleteTransform(NULL, xform);

    TIFFWriteDirectory(out);

    return 1;
}
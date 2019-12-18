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
typedef  int cmsUInt32Number ;
typedef  int /*<<< orphan*/ * cmsHTRANSFORM ;
typedef  int /*<<< orphan*/ * cmsHPROFILE ;
typedef  int /*<<< orphan*/ * cmsContext ;
typedef  int /*<<< orphan*/  cmsColorSpaceSignature ;
typedef  int /*<<< orphan*/  Profiles ;

/* Variables and functions */
 scalar_t__ BlackPointCompensation ; 
 int /*<<< orphan*/  FatalError (char*,...) ; 
 int /*<<< orphan*/  HandleSwitches (int,char**) ; 
 int Help (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  InitUtils (int /*<<< orphan*/ *,char*) ; 
 double InkLimit ; 
 int /*<<< orphan*/  Intent ; 
 scalar_t__ KeepLinearization ; 
 double LCMS_VERSION ; 
 int /*<<< orphan*/  NumOfGridPoints ; 
 int /*<<< orphan*/  ObserverAdaptationState ; 
 int /*<<< orphan*/ * OpenStockProfile (int /*<<< orphan*/ *,char*) ; 
 int PrecalcMode ; 
 int /*<<< orphan*/  PrintProfileInformation (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  SetTextTags (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 scalar_t__ TagResult ; 
 int Verbose ; 
 int /*<<< orphan*/  Version ; 
 int /*<<< orphan*/  cOutProf ; 
 int /*<<< orphan*/  cmsCloseProfile (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * cmsCreateInkLimitingDeviceLink (int /*<<< orphan*/ *,int /*<<< orphan*/ ,double) ; 
 int /*<<< orphan*/ * cmsCreateMultiprofileTransform (int /*<<< orphan*/ *,int /*<<< orphan*/ **,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  cmsDeleteTransform (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int cmsFLAGS_8BITS_DEVICELINK ; 
 int cmsFLAGS_BLACKPOINTCOMPENSATION ; 
 int cmsFLAGS_CLUT_POST_LINEARIZATION ; 
 int cmsFLAGS_CLUT_PRE_LINEARIZATION ; 
 int cmsFLAGS_GRIDPOINTS (int /*<<< orphan*/ ) ; 
 int cmsFLAGS_GUESSDEVICECLASS ; 
 int cmsFLAGS_HIGHRESPRECALC ; 
 int cmsFLAGS_KEEP_SEQUENCE ; 
 int cmsFLAGS_LOWRESPRECALC ; 
 int cmsFLAGS_NOOPTIMIZE ; 
 int /*<<< orphan*/  cmsGetColorSpace (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 scalar_t__ cmsSaveProfileToFile (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  cmsSetAdaptationState (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  cmsSetHeaderRenderingIntent (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * cmsTransform2DeviceLink (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  fflush (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  fprintf (int /*<<< orphan*/ ,char*,...) ; 
 scalar_t__ lUse8bits ; 
 int /*<<< orphan*/  memset (int /*<<< orphan*/ **,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  stderr ; 
 int xoptind ; 

int main(int argc, char *argv[])
{
    int i, nargs, rc;
    cmsHPROFILE Profiles[257];
    cmsHPROFILE hProfile;
    cmsUInt32Number dwFlags;
    cmsHTRANSFORM hTransform = NULL;
    cmsContext ContextID = NULL;

    // Here we are
    fprintf(stderr, "little cms ICC device link generator - v2.2 [LittleCMS %2.2f]\n", LCMS_VERSION / 1000.0);
    fflush(stderr);

    // Initialize
    InitUtils(ContextID, "linkicc");
    rc = 0;

    // Get the options
    HandleSwitches(argc, argv);

    // How many profiles to link?
    nargs = (argc - xoptind);
    if (nargs < 1)
        return Help(0);

    if (nargs > 255) {
        FatalError("Holy profile! what are you trying to do with so many profiles!?");
        goto Cleanup;
    }

    // Open all profiles
    memset(Profiles, 0, sizeof(Profiles));
    for (i=0; i < nargs; i++) {

        Profiles[i] = OpenStockProfile(ContextID, argv[i + xoptind]);
        if (Profiles[i] == NULL) goto Cleanup;

        if (Verbose >= 1) {
            PrintProfileInformation(ContextID, Profiles[i]);
        }
    }

    // Ink limiting
    if (InkLimit != 400.0) {
        cmsColorSpaceSignature EndingColorSpace = cmsGetColorSpace(ContextID, Profiles[nargs-1]);
        Profiles[nargs++] = cmsCreateInkLimitingDeviceLink(ContextID, EndingColorSpace, InkLimit);
    }

    // Set the flags
    dwFlags = cmsFLAGS_KEEP_SEQUENCE;
    switch (PrecalcMode) {

        case 0: dwFlags |= cmsFLAGS_LOWRESPRECALC; break;
        case 2: dwFlags |= cmsFLAGS_HIGHRESPRECALC; break;
        case 1:
            if (NumOfGridPoints > 0)
                dwFlags |= cmsFLAGS_GRIDPOINTS(NumOfGridPoints);
            break;

        default:
            {
                FatalError("Unknown precalculation mode '%d'", PrecalcMode);
                goto Cleanup;
            }
    }

    if (BlackPointCompensation)
        dwFlags |= cmsFLAGS_BLACKPOINTCOMPENSATION;

    if (TagResult)
        dwFlags |= cmsFLAGS_GUESSDEVICECLASS;

    if (KeepLinearization)
        dwFlags |= cmsFLAGS_CLUT_PRE_LINEARIZATION|cmsFLAGS_CLUT_POST_LINEARIZATION;

    if (lUse8bits) dwFlags |= cmsFLAGS_8BITS_DEVICELINK;

     cmsSetAdaptationState(ContextID, ObserverAdaptationState);

    // Create the color transform. Specify 0 for the format is safe as the transform
    // is intended to be used only for the devicelink.
    hTransform = cmsCreateMultiprofileTransform(ContextID, Profiles, nargs, 0, 0, Intent, dwFlags|cmsFLAGS_NOOPTIMIZE);
    if (hTransform == NULL) {
        FatalError("Transform creation failed");
        goto Cleanup;
    }

    hProfile =  cmsTransform2DeviceLink(ContextID, hTransform, Version, dwFlags);
    if (hProfile == NULL) {
        FatalError("Devicelink creation failed");
        goto Cleanup;
    }

    SetTextTags(ContextID, hProfile);
    cmsSetHeaderRenderingIntent(ContextID, hProfile, Intent);

    if (cmsSaveProfileToFile(ContextID, hProfile, cOutProf)) {

        if (Verbose > 0)
            fprintf(stderr, "Ok");
    }
    else
        FatalError("Error saving file!");

    cmsCloseProfile(ContextID, hProfile);


Cleanup:

    if (hTransform != NULL) cmsDeleteTransform(ContextID, hTransform);
    for (i=0; i < nargs; i++) {

        if (Profiles[i] != NULL) cmsCloseProfile(ContextID, Profiles[i]);
    }

    return rc;
}
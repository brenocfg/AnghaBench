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
typedef  int cmsUInt16Number ;
typedef  int /*<<< orphan*/  cmsNAMEDCOLORLIST ;
typedef  int /*<<< orphan*/ * cmsHPROFILE ;
typedef  int /*<<< orphan*/  cmsContext ;
typedef  scalar_t__ cmsBool ;

/* Variables and functions */
 scalar_t__ BlackPointCompensation ; 
 int /*<<< orphan*/  ComponentNames (int /*<<< orphan*/ ,int /*<<< orphan*/ ,scalar_t__) ; 
 scalar_t__ FALSE ; 
 int /*<<< orphan*/  FatalError (char*,...) ; 
 scalar_t__ GamutCheck ; 
 int /*<<< orphan*/  InputColorSpace ; 
 int /*<<< orphan*/  InputColorant ; 
 scalar_t__ InputNamedColor ; 
 int InputRange ; 
 int /*<<< orphan*/  Intent ; 
 int /*<<< orphan*/ * OpenStockProfile (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  OutputColorSpace ; 
 int /*<<< orphan*/  OutputColorant ; 
 int OutputRange ; 
 int PrecalcMode ; 
 int /*<<< orphan*/  PrintProfileInformation (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  ProofingIntent ; 
 int /*<<< orphan*/  SW ; 
 int /*<<< orphan*/  SetRange (int,scalar_t__) ; 
 scalar_t__ TRUE ; 
 int /*<<< orphan*/  TYPE_Lab_16 ; 
 int /*<<< orphan*/  TYPE_Lab_DBL ; 
 int /*<<< orphan*/  TYPE_NAMED_COLOR_INDEX ; 
 int /*<<< orphan*/  TYPE_XYZ_16 ; 
 int /*<<< orphan*/  TYPE_XYZ_DBL ; 
 int Verbose ; 
 int /*<<< orphan*/ * cInProf ; 
 int /*<<< orphan*/ * cOutProf ; 
 int /*<<< orphan*/ * cProofing ; 
 int /*<<< orphan*/  cmsCloseProfile (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * cmsCreateLab4Profile (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * cmsCreateProofingTransform (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 void* cmsCreateTransform (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * cmsCreateXYZProfile (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  cmsDupNamedColorList (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  cmsFLAGS_BLACKPOINTCOMPENSATION ; 
 int /*<<< orphan*/  cmsFLAGS_GAMUTCHECK ; 
 int /*<<< orphan*/  cmsFLAGS_HIGHRESPRECALC ; 
 int /*<<< orphan*/  cmsFLAGS_LOWRESPRECALC ; 
 int /*<<< orphan*/  cmsFLAGS_NOCACHE ; 
 int /*<<< orphan*/  cmsFLAGS_NOOPTIMIZE ; 
 int /*<<< orphan*/  cmsFLAGS_SOFTPROOFING ; 
 int /*<<< orphan*/  cmsFormatterForColorspaceOfProfile (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int,scalar_t__) ; 
 int /*<<< orphan*/  cmsFormatterForPCSOfProfile (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int,scalar_t__) ; 
 int /*<<< orphan*/  cmsGetColorSpace (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 scalar_t__ cmsGetDeviceClass (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  cmsGetPCS (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 scalar_t__ cmsIsTag (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int cmsMAXCHANNELS ; 
 int cmsNamedColorCount (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * cmsReadTag (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  cmsSetAlarmCodes (int /*<<< orphan*/ ,int*) ; 
 int /*<<< orphan*/  cmsSigColorantTableOutTag ; 
 int /*<<< orphan*/  cmsSigColorantTableTag ; 
 scalar_t__ cmsSigLinkClass ; 
 scalar_t__ cmsSigNamedColorClass ; 
 int /*<<< orphan*/ * hTrans ; 
 int /*<<< orphan*/ * hTransLab ; 
 int /*<<< orphan*/ * hTransXYZ ; 
 scalar_t__ lIsDeviceLink ; 
 scalar_t__ lIsFloat ; 
 int /*<<< orphan*/  printf (char*) ; 

__attribute__((used)) static
cmsBool OpenTransforms(cmsContext ContextID)
{
    cmsHPROFILE hInput, hOutput, hProof;
    cmsUInt32Number dwIn, dwOut, dwFlags;
    cmsNAMEDCOLORLIST* List;
    int i;

    // We don't need cache
    dwFlags = cmsFLAGS_NOCACHE;

    if (lIsDeviceLink) {

        hInput  = OpenStockProfile(0, cInProf);
        if (hInput == NULL) return FALSE;
        hOutput = NULL;
        hProof  = NULL;

        if (cmsGetDeviceClass(ContextID, hInput) == cmsSigNamedColorClass) {
            OutputColorSpace  = cmsGetColorSpace(ContextID, hInput);
            InputColorSpace = cmsGetPCS(ContextID, hInput);
        }
        else {
            InputColorSpace  = cmsGetColorSpace(ContextID, hInput);
            OutputColorSpace = cmsGetPCS(ContextID, hInput);
        }

        // Read colorant tables if present
        if (cmsIsTag(ContextID, hInput, cmsSigColorantTableTag)) {
            List = cmsReadTag(ContextID, hInput, cmsSigColorantTableTag);
            InputColorant = cmsDupNamedColorList(ContextID, List);
            InputRange = 1;
        }
        else InputColorant = ComponentNames(ContextID, InputColorSpace, TRUE);

        if (cmsIsTag(ContextID, hInput, cmsSigColorantTableOutTag)){

            List = cmsReadTag(ContextID, hInput, cmsSigColorantTableOutTag);
            OutputColorant = cmsDupNamedColorList(ContextID, List);
            OutputRange = 1;
        }
        else OutputColorant = ComponentNames(ContextID, OutputColorSpace, FALSE);

    }
    else {

        hInput  = OpenStockProfile(0, cInProf);
        if (hInput == NULL) return FALSE;

        hOutput = OpenStockProfile(0, cOutProf);
        if (hOutput == NULL) return FALSE;
        hProof  = NULL;


        if (cmsGetDeviceClass(ContextID, hInput) == cmsSigLinkClass ||
            cmsGetDeviceClass(ContextID, hOutput) == cmsSigLinkClass)
            FatalError("Use %cl flag for devicelink profiles!\n", SW);


        InputColorSpace   = cmsGetColorSpace(ContextID, hInput);
        OutputColorSpace  = cmsGetColorSpace(ContextID, hOutput);

        // Read colorant tables if present
        if (cmsIsTag(ContextID, hInput, cmsSigColorantTableTag)) {
            List = cmsReadTag(ContextID, hInput, cmsSigColorantTableTag);
            InputColorant = cmsDupNamedColorList(ContextID, List);
            if (cmsNamedColorCount(ContextID, InputColorant) <= 3)
                SetRange(255, TRUE);
            else
                SetRange(1, TRUE);  // Inks are already divided by 100 in the formatter

        }
        else InputColorant = ComponentNames(ContextID, InputColorSpace, TRUE);

        if (cmsIsTag(ContextID, hOutput, cmsSigColorantTableTag)){

            List = cmsReadTag(ContextID, hOutput, cmsSigColorantTableTag);
            OutputColorant = cmsDupNamedColorList(ContextID, List);
            if (cmsNamedColorCount(ContextID, OutputColorant) <= 3)
                SetRange(255, FALSE);
            else
                SetRange(1, FALSE);  // Inks are already divided by 100 in the formatter
        }
        else OutputColorant = ComponentNames(ContextID, OutputColorSpace, FALSE);


        if (cProofing != NULL) {

            hProof = OpenStockProfile(0, cProofing);
            if (hProof == NULL) return FALSE;
            dwFlags |= cmsFLAGS_SOFTPROOFING;
        }
    }

    // Print information on profiles
    if (Verbose > 2) {

        printf("Profile:\n");
        PrintProfileInformation(ContextID, hInput);

        if (hOutput) {

            printf("Output profile:\n");
            PrintProfileInformation(ContextID, hOutput);
        }

        if (hProof != NULL) {
            printf("Proofing profile:\n");
            PrintProfileInformation(ContextID, hProof);
        }
    }


    // Input is always in floating point
    dwIn  = cmsFormatterForColorspaceOfProfile(ContextID, hInput, 0, TRUE);

    if (lIsDeviceLink) {

        dwOut = cmsFormatterForPCSOfProfile(ContextID, hInput, lIsFloat ? 0 : 2, lIsFloat);
    }
    else {

        // 16 bits or floating point (only on output)
        dwOut = cmsFormatterForColorspaceOfProfile(ContextID, hOutput, lIsFloat ? 0 : 2, lIsFloat);
    }

    // For named color, there is a specialized formatter
    if (cmsGetDeviceClass(ContextID, hInput) == cmsSigNamedColorClass) {

        dwIn = TYPE_NAMED_COLOR_INDEX;
        InputNamedColor = TRUE;
    }

    // Precision mode
    switch (PrecalcMode) {

       case 0: dwFlags |= cmsFLAGS_NOOPTIMIZE; break;
       case 2: dwFlags |= cmsFLAGS_HIGHRESPRECALC; break;
       case 3: dwFlags |= cmsFLAGS_LOWRESPRECALC; break;
       case 1: break;

       default:
           FatalError("Unknown precalculation mode '%d'", PrecalcMode);
    }


    if (BlackPointCompensation)
        dwFlags |= cmsFLAGS_BLACKPOINTCOMPENSATION;


    if (GamutCheck) {

        cmsUInt16Number Alarm[cmsMAXCHANNELS];

        if (hProof == NULL)
            FatalError("I need proofing profile -p for gamut checking!");

        for (i=0; i < cmsMAXCHANNELS; i++)
            Alarm[i] = 0xFFFF;

        cmsSetAlarmCodes(ContextID, Alarm);
        dwFlags |= cmsFLAGS_GAMUTCHECK;
    }


    // The main transform
    hTrans = cmsCreateProofingTransform(ContextID, hInput,  dwIn, hOutput, dwOut, hProof, Intent, ProofingIntent, dwFlags);

    if (hProof) cmsCloseProfile(ContextID, hProof);

    if (hTrans == NULL) return FALSE;


    // PCS Dump if requested
    hTransXYZ = NULL; hTransLab = NULL;

    if (hOutput && Verbose > 1) {

        cmsHPROFILE hXYZ = cmsCreateXYZProfile(ContextID);
        cmsHPROFILE hLab = cmsCreateLab4Profile(ContextID, NULL);

        hTransXYZ = cmsCreateTransform(ContextID, hInput, dwIn, hXYZ,  lIsFloat ? TYPE_XYZ_DBL : TYPE_XYZ_16, Intent, cmsFLAGS_NOCACHE);
        if (hTransXYZ == NULL) return FALSE;

        hTransLab = cmsCreateTransform(ContextID, hInput, dwIn, hLab,  lIsFloat? TYPE_Lab_DBL : TYPE_Lab_16, Intent, cmsFLAGS_NOCACHE);
        if (hTransLab == NULL) return FALSE;

        cmsCloseProfile(ContextID, hXYZ);
        cmsCloseProfile(ContextID, hLab);
    }

    if (hInput) cmsCloseProfile(ContextID, hInput);
    if (hOutput) cmsCloseProfile(ContextID, hOutput);

    return TRUE;
}
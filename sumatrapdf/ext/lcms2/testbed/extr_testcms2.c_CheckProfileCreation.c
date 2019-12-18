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
typedef  int cmsInt32Number ;
typedef  int /*<<< orphan*/ * cmsHPROFILE ;

/* Variables and functions */
 int /*<<< orphan*/  CheckCHAD (int,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  CheckCRDinfo (int,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  CheckChromaticity (int,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  CheckColorantOrder (int,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  CheckData (int,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  CheckDateTime (int,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  CheckDictionary24 (int,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  CheckGamma (int,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  CheckICCViewingConditions (int,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  CheckLUT (int,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  CheckMPE (int,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  CheckMeasurement (int,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  CheckNamedColor (int,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  CheckProfileSequenceIDTag (int,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  CheckProfileSequenceTag (int,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  CheckRAWtags (int,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  CheckScreening (int,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  CheckSignature (int,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  CheckText (int,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  CheckTextSingle (int,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  CheckUcrBg (int,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  CheckVCGT (int,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  CheckXYZ (int,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  DbgThread () ; 
 int /*<<< orphan*/  FALSE ; 
 int /*<<< orphan*/  Fail (char*) ; 
 scalar_t__ INTENT_SATURATION ; 
 int /*<<< orphan*/  SubTest (char*) ; 
 int /*<<< orphan*/  TRUE ; 
 int /*<<< orphan*/  cmsCloseProfile (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * cmsCreateProfilePlaceholder (int /*<<< orphan*/ ) ; 
 scalar_t__ cmsGetColorSpace (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 scalar_t__ cmsGetDeviceClass (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 scalar_t__ cmsGetHeaderRenderingIntent (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 scalar_t__ cmsGetPCS (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 scalar_t__ cmsGetTagCount (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 scalar_t__ cmsIsTag (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * cmsOpenProfileFromFile (int /*<<< orphan*/ ,char*,char*) ; 
 int /*<<< orphan*/  cmsSaveProfileToFile (int /*<<< orphan*/ ,int /*<<< orphan*/ *,char*) ; 
 int /*<<< orphan*/  cmsSetColorSpace (int /*<<< orphan*/ ,int /*<<< orphan*/ *,scalar_t__) ; 
 int /*<<< orphan*/  cmsSetDeviceClass (int /*<<< orphan*/ ,int /*<<< orphan*/ *,scalar_t__) ; 
 int /*<<< orphan*/  cmsSetHeaderRenderingIntent (int /*<<< orphan*/ ,int /*<<< orphan*/ *,scalar_t__) ; 
 int /*<<< orphan*/  cmsSetPCS (int /*<<< orphan*/ ,int /*<<< orphan*/ *,scalar_t__) ; 
 int /*<<< orphan*/  cmsSetProfileVersion (int /*<<< orphan*/ ,int /*<<< orphan*/ *,double) ; 
 int /*<<< orphan*/  cmsSigAToB0Tag ; 
 int /*<<< orphan*/  cmsSigAToB1Tag ; 
 int /*<<< orphan*/  cmsSigAToB2Tag ; 
 int /*<<< orphan*/  cmsSigBToA0Tag ; 
 int /*<<< orphan*/  cmsSigBToA1Tag ; 
 int /*<<< orphan*/  cmsSigBToA2Tag ; 
 int /*<<< orphan*/  cmsSigBToD0Tag ; 
 int /*<<< orphan*/  cmsSigBToD1Tag ; 
 int /*<<< orphan*/  cmsSigBToD2Tag ; 
 int /*<<< orphan*/  cmsSigBToD3Tag ; 
 int /*<<< orphan*/  cmsSigBlueColorantTag ; 
 int /*<<< orphan*/  cmsSigBlueTRCTag ; 
 int /*<<< orphan*/  cmsSigCalibrationDateTimeTag ; 
 int /*<<< orphan*/  cmsSigCharTargetTag ; 
 int /*<<< orphan*/  cmsSigChromaticAdaptationTag ; 
 int /*<<< orphan*/  cmsSigChromaticityTag ; 
 int /*<<< orphan*/  cmsSigColorantOrderTag ; 
 int /*<<< orphan*/  cmsSigColorantTableOutTag ; 
 int /*<<< orphan*/  cmsSigColorantTableTag ; 
 int /*<<< orphan*/  cmsSigColorimetricIntentImageStateTag ; 
 int /*<<< orphan*/  cmsSigCopyrightTag ; 
 int /*<<< orphan*/  cmsSigCrdInfoTag ; 
 int /*<<< orphan*/  cmsSigDToB0Tag ; 
 int /*<<< orphan*/  cmsSigDToB1Tag ; 
 int /*<<< orphan*/  cmsSigDToB2Tag ; 
 int /*<<< orphan*/  cmsSigDToB3Tag ; 
 int /*<<< orphan*/  cmsSigDateTimeTag ; 
 int /*<<< orphan*/  cmsSigDeviceMfgDescTag ; 
 int /*<<< orphan*/  cmsSigDeviceModelDescTag ; 
 scalar_t__ cmsSigDisplayClass ; 
 int /*<<< orphan*/  cmsSigGamutTag ; 
 int /*<<< orphan*/  cmsSigGrayTRCTag ; 
 int /*<<< orphan*/  cmsSigGreenColorantTag ; 
 int /*<<< orphan*/  cmsSigGreenTRCTag ; 
 scalar_t__ cmsSigLabData ; 
 int /*<<< orphan*/  cmsSigLuminanceTag ; 
 int /*<<< orphan*/  cmsSigMeasurementTag ; 
 int /*<<< orphan*/  cmsSigMediaBlackPointTag ; 
 int /*<<< orphan*/  cmsSigMediaWhitePointTag ; 
 int /*<<< orphan*/  cmsSigNamedColor2Tag ; 
 int /*<<< orphan*/  cmsSigPerceptualRenderingIntentGamutTag ; 
 int /*<<< orphan*/  cmsSigPreview0Tag ; 
 int /*<<< orphan*/  cmsSigPreview1Tag ; 
 int /*<<< orphan*/  cmsSigPreview2Tag ; 
 int /*<<< orphan*/  cmsSigProfileDescriptionTag ; 
 int /*<<< orphan*/  cmsSigPs2CRD0Tag ; 
 int /*<<< orphan*/  cmsSigPs2CRD1Tag ; 
 int /*<<< orphan*/  cmsSigPs2CRD2Tag ; 
 int /*<<< orphan*/  cmsSigPs2CRD3Tag ; 
 int /*<<< orphan*/  cmsSigPs2CSATag ; 
 int /*<<< orphan*/  cmsSigPs2RenderingIntentTag ; 
 int /*<<< orphan*/  cmsSigRedColorantTag ; 
 int /*<<< orphan*/  cmsSigRedTRCTag ; 
 scalar_t__ cmsSigRgbData ; 
 int /*<<< orphan*/  cmsSigSaturationRenderingIntentGamutTag ; 
 int /*<<< orphan*/  cmsSigScreeningDescTag ; 
 int /*<<< orphan*/  cmsSigScreeningTag ; 
 int /*<<< orphan*/  cmsSigTechnologyTag ; 
 int /*<<< orphan*/  cmsSigUcrBgTag ; 
 int /*<<< orphan*/  cmsSigViewingCondDescTag ; 
 int /*<<< orphan*/  remove (char*) ; 

__attribute__((used)) static
cmsInt32Number CheckProfileCreation(void)
{
    cmsHPROFILE h;
    cmsInt32Number Pass;

    h = cmsCreateProfilePlaceholder(DbgThread());
    if (h == NULL) return 0;

    cmsSetProfileVersion(DbgThread(), h, 4.3);
    if (cmsGetTagCount(DbgThread(), h) != 0) { Fail("Empty profile with nonzero number of tags"); goto Error; }
    if (cmsIsTag(DbgThread(), h, cmsSigAToB0Tag)) { Fail("Found a tag in an empty profile"); goto Error; }

    cmsSetColorSpace(DbgThread(), h, cmsSigRgbData);
    if (cmsGetColorSpace(DbgThread(), h) !=  cmsSigRgbData) { Fail("Unable to set colorspace"); goto Error; }

    cmsSetPCS(DbgThread(), h, cmsSigLabData);
    if (cmsGetPCS(DbgThread(), h) !=  cmsSigLabData) { Fail("Unable to set colorspace"); goto Error; }

    cmsSetDeviceClass(DbgThread(), h, cmsSigDisplayClass);
    if (cmsGetDeviceClass(DbgThread(), h) != cmsSigDisplayClass) { Fail("Unable to set deviceclass"); goto Error; }

    cmsSetHeaderRenderingIntent(DbgThread(), h, INTENT_SATURATION);
    if (cmsGetHeaderRenderingIntent(DbgThread(), h) != INTENT_SATURATION) { Fail("Unable to set rendering intent"); goto Error; }

    for (Pass = 1; Pass <= 2; Pass++) {

        SubTest("Tags holding XYZ");

        if (!CheckXYZ(Pass, h, cmsSigBlueColorantTag)) goto Error;
        if (!CheckXYZ(Pass, h, cmsSigGreenColorantTag)) goto Error;
        if (!CheckXYZ(Pass, h, cmsSigRedColorantTag)) goto Error;
        if (!CheckXYZ(Pass, h, cmsSigMediaBlackPointTag)) goto Error;
        if (!CheckXYZ(Pass, h, cmsSigMediaWhitePointTag)) goto Error;
        if (!CheckXYZ(Pass, h, cmsSigLuminanceTag)) goto Error;

        SubTest("Tags holding curves");

        if (!CheckGamma(Pass, h, cmsSigBlueTRCTag)) goto Error;
        if (!CheckGamma(Pass, h, cmsSigGrayTRCTag)) goto Error;
        if (!CheckGamma(Pass, h, cmsSigGreenTRCTag)) goto Error;
        if (!CheckGamma(Pass, h, cmsSigRedTRCTag)) goto Error;

        SubTest("Tags holding text");

        if (!CheckTextSingle(Pass, h, cmsSigCharTargetTag)) goto Error;
        if (!CheckTextSingle(Pass, h, cmsSigScreeningDescTag)) goto Error;

        if (!CheckText(Pass, h, cmsSigCopyrightTag)) goto Error;
        if (!CheckText(Pass, h, cmsSigProfileDescriptionTag)) goto Error;
        if (!CheckText(Pass, h, cmsSigDeviceMfgDescTag)) goto Error;
        if (!CheckText(Pass, h, cmsSigDeviceModelDescTag)) goto Error;
        if (!CheckText(Pass, h, cmsSigViewingCondDescTag)) goto Error;



        SubTest("Tags holding cmsICCData");

        if (!CheckData(Pass, h, cmsSigPs2CRD0Tag)) goto Error;
        if (!CheckData(Pass, h, cmsSigPs2CRD1Tag)) goto Error;
        if (!CheckData(Pass, h, cmsSigPs2CRD2Tag)) goto Error;
        if (!CheckData(Pass, h, cmsSigPs2CRD3Tag)) goto Error;
        if (!CheckData(Pass, h, cmsSigPs2CSATag)) goto Error;
        if (!CheckData(Pass, h, cmsSigPs2RenderingIntentTag)) goto Error;

        SubTest("Tags holding signatures");

        if (!CheckSignature(Pass, h, cmsSigColorimetricIntentImageStateTag)) goto Error;
        if (!CheckSignature(Pass, h, cmsSigPerceptualRenderingIntentGamutTag)) goto Error;
        if (!CheckSignature(Pass, h, cmsSigSaturationRenderingIntentGamutTag)) goto Error;
        if (!CheckSignature(Pass, h, cmsSigTechnologyTag)) goto Error;

        SubTest("Tags holding date_time");

        if (!CheckDateTime(Pass, h, cmsSigCalibrationDateTimeTag)) goto Error;
        if (!CheckDateTime(Pass, h, cmsSigDateTimeTag)) goto Error;

        SubTest("Tags holding named color lists");

        if (!CheckNamedColor(Pass, h, cmsSigColorantTableTag, 15, FALSE)) goto Error;
        if (!CheckNamedColor(Pass, h, cmsSigColorantTableOutTag, 15, FALSE)) goto Error;
        if (!CheckNamedColor(Pass, h, cmsSigNamedColor2Tag, 4096, TRUE)) goto Error;

        SubTest("Tags holding LUTs");

        if (!CheckLUT(Pass, h, cmsSigAToB0Tag)) goto Error;
        if (!CheckLUT(Pass, h, cmsSigAToB1Tag)) goto Error;
        if (!CheckLUT(Pass, h, cmsSigAToB2Tag)) goto Error;
        if (!CheckLUT(Pass, h, cmsSigBToA0Tag)) goto Error;
        if (!CheckLUT(Pass, h, cmsSigBToA1Tag)) goto Error;
        if (!CheckLUT(Pass, h, cmsSigBToA2Tag)) goto Error;
        if (!CheckLUT(Pass, h, cmsSigPreview0Tag)) goto Error;
        if (!CheckLUT(Pass, h, cmsSigPreview1Tag)) goto Error;
        if (!CheckLUT(Pass, h, cmsSigPreview2Tag)) goto Error;
        if (!CheckLUT(Pass, h, cmsSigGamutTag)) goto Error;

        SubTest("Tags holding CHAD");
        if (!CheckCHAD(Pass, h, cmsSigChromaticAdaptationTag)) goto Error;

        SubTest("Tags holding Chromaticity");
        if (!CheckChromaticity(Pass, h, cmsSigChromaticityTag)) goto Error;

        SubTest("Tags holding colorant order");
        if (!CheckColorantOrder(Pass, h, cmsSigColorantOrderTag)) goto Error;

        SubTest("Tags holding measurement");
        if (!CheckMeasurement(Pass, h, cmsSigMeasurementTag)) goto Error;

        SubTest("Tags holding CRD info");
        if (!CheckCRDinfo(Pass, h, cmsSigCrdInfoTag)) goto Error;

        SubTest("Tags holding UCR/BG");
        if (!CheckUcrBg(Pass, h, cmsSigUcrBgTag)) goto Error;

        SubTest("Tags holding MPE");
        if (!CheckMPE(Pass, h, cmsSigDToB0Tag)) goto Error;
        if (!CheckMPE(Pass, h, cmsSigDToB1Tag)) goto Error;
        if (!CheckMPE(Pass, h, cmsSigDToB2Tag)) goto Error;
        if (!CheckMPE(Pass, h, cmsSigDToB3Tag)) goto Error;
        if (!CheckMPE(Pass, h, cmsSigBToD0Tag)) goto Error;
        if (!CheckMPE(Pass, h, cmsSigBToD1Tag)) goto Error;
        if (!CheckMPE(Pass, h, cmsSigBToD2Tag)) goto Error;
        if (!CheckMPE(Pass, h, cmsSigBToD3Tag)) goto Error;

        SubTest("Tags using screening");
        if (!CheckScreening(Pass, h, cmsSigScreeningTag)) goto Error;

        SubTest("Tags holding profile sequence description");
        if (!CheckProfileSequenceTag(Pass, h)) goto Error;
        if (!CheckProfileSequenceIDTag(Pass, h)) goto Error;

        SubTest("Tags holding ICC viewing conditions");
        if (!CheckICCViewingConditions(Pass, h)) goto Error;

        SubTest("VCGT tags");
        if (!CheckVCGT(Pass, h)) goto Error;

        SubTest("RAW tags");
        if (!CheckRAWtags(Pass, h)) goto Error;

        SubTest("Dictionary meta tags");
        // if (!CheckDictionary16(Pass, h)) goto Error;
        if (!CheckDictionary24(Pass, h)) goto Error;

        if (Pass == 1) {
            cmsSaveProfileToFile(DbgThread(), h, "alltags.icc");
            cmsCloseProfile(DbgThread(), h);
            h = cmsOpenProfileFromFile(DbgThread(), "alltags.icc", "r");
        }

    }

    /*
    Not implemented (by design):

    cmsSigDataTag                           = 0x64617461,  // 'data'  -- Unused
    cmsSigDeviceSettingsTag                 = 0x64657673,  // 'devs'  -- Unused
    cmsSigNamedColorTag                     = 0x6E636f6C,  // 'ncol'  -- Don't use this one, deprecated by ICC
    cmsSigOutputResponseTag                 = 0x72657370,  // 'resp'  -- Possible patent on this
    */

    cmsCloseProfile(DbgThread(), h);
    remove("alltags.icc");
    return 1;

Error:
    cmsCloseProfile(DbgThread(), h);
    remove("alltags.icc");
    return 0;
}
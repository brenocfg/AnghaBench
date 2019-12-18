#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
typedef  scalar_t__ cmsUInt32Number ;
typedef  int /*<<< orphan*/  cmsPipeline ;
typedef  int /*<<< orphan*/  cmsIOHANDLER ;
typedef  int /*<<< orphan*/ * cmsHTRANSFORM ;
typedef  int /*<<< orphan*/ * cmsHPROFILE ;
typedef  int /*<<< orphan*/  cmsContext ;
typedef  int /*<<< orphan*/  cmsColorSpaceSignature ;
typedef  int /*<<< orphan*/  cmsCIEXYZ ;
typedef  int /*<<< orphan*/  cmsBool ;
struct TYPE_4__ {TYPE_1__* core; } ;
typedef  TYPE_2__ _cmsTRANSFORM ;
struct TYPE_3__ {int /*<<< orphan*/  Lut; } ;

/* Variables and functions */
 int /*<<< orphan*/  EmitIntent (int /*<<< orphan*/ ,int /*<<< orphan*/ *,scalar_t__) ; 
 int /*<<< orphan*/  EmitPQRStage (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  EmitWhiteBlackD50 (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  EmitXYZ2Lab (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  FALSE ; 
 scalar_t__ INTENT_ABSOLUTE_COLORIMETRIC ; 
 scalar_t__ INTENT_RELATIVE_COLORIMETRIC ; 
 scalar_t__ TYPE_Lab_16 ; 
 int /*<<< orphan*/  TYPE_Lab_DBL ; 
 scalar_t__ T_CHANNELS (scalar_t__) ; 
 int /*<<< orphan*/  WriteCLUT (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ,char*,char*,char*,char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  _cmsIOPrintf (int /*<<< orphan*/ ,int /*<<< orphan*/ *,char*,...) ; 
 int /*<<< orphan*/  _cmsOptimizePipeline (int /*<<< orphan*/ ,int /*<<< orphan*/ **,scalar_t__,scalar_t__*,scalar_t__*,scalar_t__*) ; 
 int /*<<< orphan*/  cmsCloseProfile (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * cmsCreateLab4Profile (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * cmsCreateMultiprofileTransform (int /*<<< orphan*/ ,int /*<<< orphan*/ **,int,int /*<<< orphan*/ ,scalar_t__,scalar_t__,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  cmsDeleteTransform (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  cmsDetectBlackPoint (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ *,scalar_t__,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  cmsERROR_COLORSPACE_CHECK ; 
 scalar_t__ cmsFLAGS_BLACKPOINTCOMPENSATION ; 
 scalar_t__ cmsFLAGS_FORCE_CLUT ; 
 scalar_t__ cmsFLAGS_NODEFAULTRESOURCEDEF ; 
 scalar_t__ cmsFLAGS_NOWHITEONWHITEFIXUP ; 
 scalar_t__ cmsFormatterForColorspaceOfProfile (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  cmsGetColorSpace (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * cmsPipelineDup (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  cmsPipelineFree (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  cmsPipelineGetPtrToFirstStage (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  cmsSignalError (int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*) ; 

__attribute__((used)) static
int WriteOutputLUT(cmsContext ContextID, cmsIOHANDLER* m, cmsHPROFILE hProfile, cmsUInt32Number Intent, cmsUInt32Number dwFlags)
{
    cmsHPROFILE hLab;
    cmsHTRANSFORM xform;
    cmsUInt32Number i, nChannels;
    cmsUInt32Number OutputFormat;
    _cmsTRANSFORM* v;
    cmsPipeline* DeviceLink;
    cmsHPROFILE Profiles[3];
    cmsCIEXYZ BlackPointAdaptedToD50;
    cmsBool lDoBPC = (cmsBool) (dwFlags & cmsFLAGS_BLACKPOINTCOMPENSATION);
    cmsBool lFixWhite = (cmsBool) !(dwFlags & cmsFLAGS_NOWHITEONWHITEFIXUP);
    cmsUInt32Number InFrm = TYPE_Lab_16;
    cmsUInt32Number RelativeEncodingIntent;
    cmsColorSpaceSignature ColorSpace;


    hLab = cmsCreateLab4Profile(ContextID, NULL);
    if (hLab == NULL) return 0;

    OutputFormat = cmsFormatterForColorspaceOfProfile(ContextID, hProfile, 2, FALSE);
    nChannels    = T_CHANNELS(OutputFormat);

    ColorSpace = cmsGetColorSpace(ContextID, hProfile);

    // For absolute colorimetric, the LUT is encoded as relative in order to preserve precision.

    RelativeEncodingIntent = Intent;
    if (RelativeEncodingIntent == INTENT_ABSOLUTE_COLORIMETRIC)
        RelativeEncodingIntent = INTENT_RELATIVE_COLORIMETRIC;


    // Use V4 Lab always
    Profiles[0] = hLab;
    Profiles[1] = hProfile;

    xform = cmsCreateMultiprofileTransform(ContextID,
                                              Profiles, 2, TYPE_Lab_DBL,
                                              OutputFormat, RelativeEncodingIntent, 0);
    cmsCloseProfile(ContextID, hLab);

    if (xform == NULL) {

        cmsSignalError(ContextID, cmsERROR_COLORSPACE_CHECK, "Cannot create transform Lab -> Profile in CRD creation");
        return 0;
    }

    // Get a copy of the internal devicelink
    v = (_cmsTRANSFORM*) xform;
    DeviceLink = cmsPipelineDup(ContextID, v ->core->Lut);
    if (DeviceLink == NULL) return 0;


    // We need a CLUT
    dwFlags |= cmsFLAGS_FORCE_CLUT;
    _cmsOptimizePipeline(ContextID, &DeviceLink, RelativeEncodingIntent, &InFrm, &OutputFormat, &dwFlags);

    _cmsIOPrintf(ContextID, m, "<<\n");
    _cmsIOPrintf(ContextID, m, "/ColorRenderingType 1\n");


    cmsDetectBlackPoint(ContextID, &BlackPointAdaptedToD50, hProfile, Intent, 0);

    // Emit headers, etc.
    EmitWhiteBlackD50(ContextID, m, &BlackPointAdaptedToD50);
    EmitPQRStage(ContextID, m, hProfile, lDoBPC, Intent == INTENT_ABSOLUTE_COLORIMETRIC);
    EmitXYZ2Lab(ContextID, m);


    // FIXUP: map Lab (100, 0, 0) to perfect white, because the particular encoding for Lab
    // does map a=b=0 not falling into any specific node. Since range a,b goes -128..127,
    // zero is slightly moved towards right, so assure next node (in L=100 slice) is mapped to
    // zero. This would sacrifice a bit of highlights, but failure to do so would cause
    // scum dot. Ouch.

    if (Intent == INTENT_ABSOLUTE_COLORIMETRIC)
            lFixWhite = FALSE;

    _cmsIOPrintf(ContextID, m, "/RenderTable ");


    WriteCLUT(ContextID, m, cmsPipelineGetPtrToFirstStage(ContextID, DeviceLink), "<", ">\n", "", "", lFixWhite, ColorSpace);

    _cmsIOPrintf(ContextID, m, " %d {} bind ", nChannels);

    for (i=1; i < nChannels; i++)
            _cmsIOPrintf(ContextID, m, "dup ");

    _cmsIOPrintf(ContextID, m, "]\n");


    EmitIntent(ContextID, m, Intent);

    _cmsIOPrintf(ContextID, m, ">>\n");

    if (!(dwFlags & cmsFLAGS_NODEFAULTRESOURCEDEF)) {

        _cmsIOPrintf(ContextID, m, "/Current exch /ColorRendering defineresource pop\n");
    }

    cmsPipelineFree(ContextID, DeviceLink);
    cmsDeleteTransform(ContextID, xform);

    return 1;
}
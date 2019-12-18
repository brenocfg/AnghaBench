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
typedef  int cmsUInt32Number ;
typedef  int /*<<< orphan*/  cmsToneCurve ;
typedef  int /*<<< orphan*/  cmsPipeline ;
typedef  int /*<<< orphan*/  cmsIOHANDLER ;
typedef  int /*<<< orphan*/ * cmsHTRANSFORM ;
typedef  int /*<<< orphan*/  cmsHPROFILE ;
typedef  int /*<<< orphan*/  cmsContext ;
typedef  int /*<<< orphan*/  cmsCIEXYZ ;
struct TYPE_4__ {TYPE_1__* core; } ;
typedef  TYPE_2__ _cmsTRANSFORM ;
struct TYPE_3__ {int /*<<< orphan*/  Lut; } ;

/* Variables and functions */
 int /*<<< orphan*/  EmitCIEBasedA (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int EmitCIEBasedDEF (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * ExtractGray2Y (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  FALSE ; 
 int TYPE_Lab_16 ; 
 int /*<<< orphan*/  TYPE_Lab_DBL ; 
 int T_CHANNELS (int) ; 
 int /*<<< orphan*/  _cmsOptimizePipeline (int /*<<< orphan*/ ,int /*<<< orphan*/ **,int,int*,int*,int*) ; 
 int /*<<< orphan*/  cmsCloseProfile (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  cmsCreateLab4Profile (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * cmsCreateMultiprofileTransform (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int,int,int /*<<< orphan*/ ,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  cmsDeleteTransform (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  cmsDetectBlackPoint (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  cmsERROR_COLORSPACE_CHECK ; 
 int cmsFLAGS_FORCE_CLUT ; 
 int cmsFormatterForColorspaceOfProfile (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  cmsFreeToneCurve (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * cmsPipelineDup (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  cmsPipelineFree (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  cmsSignalError (int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*,...) ; 

__attribute__((used)) static
int WriteInputLUT(cmsContext ContextID, cmsIOHANDLER* m, cmsHPROFILE hProfile, cmsUInt32Number Intent, cmsUInt32Number dwFlags)
{
    cmsHPROFILE hLab;
    cmsHTRANSFORM xform;
    cmsUInt32Number nChannels;
    cmsUInt32Number InputFormat;
    int rc;
    cmsHPROFILE Profiles[2];
    cmsCIEXYZ BlackPointAdaptedToD50;

    // Does create a device-link based transform.
    // The DeviceLink is next dumped as working CSA.

    InputFormat = cmsFormatterForColorspaceOfProfile(ContextID, hProfile, 2, FALSE);
    nChannels   = T_CHANNELS(InputFormat);


    cmsDetectBlackPoint(ContextID, &BlackPointAdaptedToD50, hProfile, Intent, 0);

    // Adjust output to Lab4
    hLab = cmsCreateLab4Profile(ContextID, NULL);

    Profiles[0] = hProfile;
    Profiles[1] = hLab;

    xform = cmsCreateMultiprofileTransform(ContextID, Profiles, 2,  InputFormat, TYPE_Lab_DBL, Intent, 0);
    cmsCloseProfile(ContextID, hLab);

    if (xform == NULL) {

        cmsSignalError(ContextID, cmsERROR_COLORSPACE_CHECK, "Cannot create transform Profile -> Lab");
        return 0;
    }

    // Only 1, 3 and 4 channels are allowed

    switch (nChannels) {

    case 1: {
            cmsToneCurve* Gray2Y = ExtractGray2Y(ContextID, hProfile, Intent);
            EmitCIEBasedA(ContextID, m, Gray2Y, &BlackPointAdaptedToD50);
            cmsFreeToneCurve(ContextID, Gray2Y);
            }
            break;

    case 3:
    case 4: {
            cmsUInt32Number OutFrm = TYPE_Lab_16;
            cmsPipeline* DeviceLink;
            _cmsTRANSFORM* v = (_cmsTRANSFORM*) xform;

            DeviceLink = cmsPipelineDup(ContextID, v ->core->Lut);
            if (DeviceLink == NULL) return 0;

            dwFlags |= cmsFLAGS_FORCE_CLUT;
            _cmsOptimizePipeline(ContextID, &DeviceLink, Intent, &InputFormat, &OutFrm, &dwFlags);

            rc = EmitCIEBasedDEF(ContextID, m, DeviceLink, Intent, &BlackPointAdaptedToD50);
            cmsPipelineFree(ContextID, DeviceLink);
            if (rc == 0) return 0;
            }
            break;

    default:

        cmsSignalError(ContextID, cmsERROR_COLORSPACE_CHECK, "Only 3, 4 channels supported for CSA. This profile has %d channels.", nChannels);
        return 0;
    }


    cmsDeleteTransform(ContextID, xform);

    return 1;
}
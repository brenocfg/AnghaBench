#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  cmsUInt32Number ;
typedef  int /*<<< orphan*/  cmsStage ;
typedef  int /*<<< orphan*/  cmsPipeline ;
struct TYPE_6__ {int /*<<< orphan*/  UsedSpace; } ;
typedef  TYPE_1__ cmsIOHANDLER ;
typedef  int /*<<< orphan*/  cmsHPROFILE ;
typedef  int /*<<< orphan*/  cmsContext ;
typedef  scalar_t__ cmsColorSpaceSignature ;

/* Variables and functions */
 int /*<<< orphan*/  WriteInputLUT (int /*<<< orphan*/ ,TYPE_1__*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  WriteInputMatrixShaper (int /*<<< orphan*/ ,TYPE_1__*,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  WriteNamedColorCSA (int /*<<< orphan*/ ,TYPE_1__*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * _cmsReadInputLUT (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  cmsERROR_COLORSPACE_CHECK ; 
 scalar_t__ cmsGetDeviceClass (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ cmsGetPCS (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ cmsPipelineCheckAndRetreiveStages (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ **,int /*<<< orphan*/ **) ; 
 int /*<<< orphan*/  cmsPipelineFree (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  cmsSigCurveSetElemType ; 
 scalar_t__ cmsSigLabData ; 
 int /*<<< orphan*/  cmsSigMatrixElemType ; 
 scalar_t__ cmsSigNamedColorClass ; 
 scalar_t__ cmsSigXYZData ; 
 int /*<<< orphan*/  cmsSignalError (int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*) ; 

__attribute__((used)) static
cmsUInt32Number GenerateCSA(cmsContext ContextID,
                            cmsHPROFILE hProfile,
                            cmsUInt32Number Intent,
                            cmsUInt32Number dwFlags,
                            cmsIOHANDLER* mem)
{
    cmsUInt32Number dwBytesUsed;
    cmsPipeline* lut = NULL;
    cmsStage* Matrix, *Shaper;


    // Is a named color profile?
    if (cmsGetDeviceClass(ContextID, hProfile) == cmsSigNamedColorClass) {

        if (!WriteNamedColorCSA(ContextID, mem, hProfile, Intent)) goto Error;
    }
    else {


        // Any profile class are allowed (including devicelink), but
        // output (PCS) colorspace must be XYZ or Lab
        cmsColorSpaceSignature ColorSpace = cmsGetPCS(ContextID, hProfile);

        if (ColorSpace != cmsSigXYZData &&
            ColorSpace != cmsSigLabData) {

                cmsSignalError(ContextID, cmsERROR_COLORSPACE_CHECK, "Invalid output color space");
                goto Error;
        }


        // Read the lut with all necessary conversion stages
        lut = _cmsReadInputLUT(ContextID, hProfile, Intent);
        if (lut == NULL) goto Error;


        // Tone curves + matrix can be implemented without any LUT
        if (cmsPipelineCheckAndRetreiveStages(ContextID, lut, 2, cmsSigCurveSetElemType, cmsSigMatrixElemType, &Shaper, &Matrix)) {

            if (!WriteInputMatrixShaper(ContextID, mem, hProfile, Matrix, Shaper)) goto Error;

        }
        else {
           // We need a LUT for the rest
           if (!WriteInputLUT(ContextID, mem, hProfile, Intent, dwFlags)) goto Error;
        }
    }


    // Done, keep memory usage
    dwBytesUsed = mem ->UsedSpace;

    // Get rid of LUT
    if (lut != NULL) cmsPipelineFree(ContextID, lut);

    // Finally, return used byte count
    return dwBytesUsed;

Error:
    if (lut != NULL) cmsPipelineFree(ContextID, lut);
    return 0;
}
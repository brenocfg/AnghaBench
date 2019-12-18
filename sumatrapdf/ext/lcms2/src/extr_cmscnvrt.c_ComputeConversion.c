#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_14__   TYPE_2__ ;
typedef  struct TYPE_13__   TYPE_1__ ;

/* Type definitions */
struct TYPE_13__ {int /*<<< orphan*/ * n; } ;
typedef  TYPE_1__ cmsVEC3 ;
typedef  scalar_t__ cmsUInt32Number ;
typedef  int /*<<< orphan*/  cmsMAT3 ;
typedef  int /*<<< orphan*/  cmsHPROFILE ;
typedef  int /*<<< orphan*/  cmsFloat64Number ;
typedef  int /*<<< orphan*/  cmsContext ;
struct TYPE_14__ {scalar_t__ X; scalar_t__ Y; scalar_t__ Z; } ;
typedef  TYPE_2__ cmsCIEXYZ ;
typedef  scalar_t__ cmsBool ;

/* Variables and functions */
 int /*<<< orphan*/  ComputeAbsoluteIntent (int /*<<< orphan*/ ,int /*<<< orphan*/ ,TYPE_2__*,int /*<<< orphan*/ *,TYPE_2__*,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  ComputeBlackPointCompensation (int /*<<< orphan*/ ,TYPE_2__*,TYPE_2__*,int /*<<< orphan*/ *,TYPE_1__*) ; 
 scalar_t__ FALSE ; 
 scalar_t__ INTENT_ABSOLUTE_COLORIMETRIC ; 
 int /*<<< orphan*/  MAX_ENCODEABLE_XYZ ; 
 scalar_t__ TRUE ; 
 int /*<<< orphan*/  _cmsMAT3identity (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  _cmsReadCHAD (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  _cmsReadMediaWhitePoint (int /*<<< orphan*/ ,TYPE_2__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  _cmsVEC3init (int /*<<< orphan*/ ,TYPE_1__*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  cmsDetectBlackPoint (int /*<<< orphan*/ ,TYPE_2__*,int /*<<< orphan*/ ,scalar_t__,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  cmsDetectDestinationBlackPoint (int /*<<< orphan*/ ,TYPE_2__*,int /*<<< orphan*/ ,scalar_t__,int /*<<< orphan*/ ) ; 

__attribute__((used)) static
cmsBool ComputeConversion(cmsContext ContextID,
                          cmsUInt32Number i,
                          cmsHPROFILE hProfiles[],
                          cmsUInt32Number Intent,
                          cmsBool BPC,
                          cmsFloat64Number AdaptationState,
                          cmsMAT3* m, cmsVEC3* off)
{

    int k;

    // m  and off are set to identity and this is detected latter on
    _cmsMAT3identity(ContextID, m);
    _cmsVEC3init(ContextID, off, 0, 0, 0);

    // If intent is abs. colorimetric,
    if (Intent == INTENT_ABSOLUTE_COLORIMETRIC) {

        cmsCIEXYZ WhitePointIn, WhitePointOut;
        cmsMAT3 ChromaticAdaptationMatrixIn, ChromaticAdaptationMatrixOut;

        _cmsReadMediaWhitePoint(ContextID, &WhitePointIn,  hProfiles[i-1]);
        _cmsReadCHAD(ContextID, &ChromaticAdaptationMatrixIn, hProfiles[i-1]);

        _cmsReadMediaWhitePoint(ContextID, &WhitePointOut,  hProfiles[i]);
        _cmsReadCHAD(ContextID, &ChromaticAdaptationMatrixOut, hProfiles[i]);

        if (!ComputeAbsoluteIntent(ContextID, AdaptationState,
                                  &WhitePointIn,  &ChromaticAdaptationMatrixIn,
                                  &WhitePointOut, &ChromaticAdaptationMatrixOut, m)) return FALSE;

    }
    else {
        // Rest of intents may apply BPC.

        if (BPC) {

            cmsCIEXYZ BlackPointIn, BlackPointOut;

            cmsDetectBlackPoint(ContextID, &BlackPointIn,  hProfiles[i-1], Intent, 0);
            cmsDetectDestinationBlackPoint(ContextID, &BlackPointOut, hProfiles[i], Intent, 0);

            // If black points are equal, then do nothing
            if (BlackPointIn.X != BlackPointOut.X ||
                BlackPointIn.Y != BlackPointOut.Y ||
                BlackPointIn.Z != BlackPointOut.Z)
                    ComputeBlackPointCompensation(ContextID, &BlackPointIn, &BlackPointOut, m, off);
        }
    }

    // Offset should be adjusted because the encoding. We encode XYZ normalized to 0..1.0,
    // to do that, we divide by MAX_ENCODEABLE_XZY. The conversion stage goes XYZ -> XYZ so
    // we have first to convert from encoded to XYZ and then convert back to encoded.
    // y = Mx + Off
    // x = x'c
    // y = M x'c + Off
    // y = y'c; y' = y / c
    // y' = (Mx'c + Off) /c = Mx' + (Off / c)

    for (k=0; k < 3; k++) {
        off ->n[k] /= MAX_ENCODEABLE_XYZ;
    }

    return TRUE;
}
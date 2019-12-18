#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_2__ ;
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
typedef  scalar_t__ cmsUInt32Number ;
typedef  int /*<<< orphan*/  cmsUInt16Number ;
typedef  int /*<<< orphan*/ * cmsHTRANSFORM ;
typedef  int /*<<< orphan*/ * cmsHPROFILE ;
typedef  int /*<<< orphan*/  cmsContext ;
typedef  int /*<<< orphan*/  cmsColorSpaceSignature ;
struct TYPE_7__ {double X; double Y; double Z; } ;
typedef  TYPE_1__ cmsCIEXYZ ;
struct TYPE_8__ {int L; scalar_t__ b; scalar_t__ a; } ;
typedef  TYPE_2__ cmsCIELab ;
typedef  int /*<<< orphan*/  cmsBool ;

/* Variables and functions */
 int /*<<< orphan*/  FALSE ; 
 int /*<<< orphan*/  LCMS_USED_AS_INPUT ; 
 int /*<<< orphan*/  TRUE ; 
 int /*<<< orphan*/  TYPE_Lab_DBL ; 
 scalar_t__ T_CHANNELS (scalar_t__) ; 
 int /*<<< orphan*/  _cmsEndPointsBySpace (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ **,scalar_t__*) ; 
 int /*<<< orphan*/  cmsCloseProfile (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * cmsCreateLab2Profile (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * cmsCreateTransform (int /*<<< orphan*/ ,int /*<<< orphan*/ *,scalar_t__,int /*<<< orphan*/ *,int /*<<< orphan*/ ,scalar_t__,int) ; 
 int /*<<< orphan*/  cmsDeleteTransform (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  cmsDoTransform (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ *,TYPE_2__*,int) ; 
 int cmsFLAGS_NOCACHE ; 
 int cmsFLAGS_NOOPTIMIZE ; 
 scalar_t__ cmsFormatterForColorspaceOfProfile (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  cmsGetColorSpace (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  cmsIsIntentSupported (int /*<<< orphan*/ ,int /*<<< orphan*/ *,scalar_t__,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  cmsLab2XYZ (int /*<<< orphan*/ ,int /*<<< orphan*/ *,TYPE_1__*,TYPE_2__*) ; 
 int /*<<< orphan*/  cmsUNUSED_PARAMETER (scalar_t__) ; 

__attribute__((used)) static
cmsBool  BlackPointAsDarkerColorant(cmsContext ContextID,
                                    cmsHPROFILE hInput,
                                    cmsUInt32Number Intent,
                                    cmsCIEXYZ* BlackPoint,
                                    cmsUInt32Number dwFlags)
{
    cmsUInt16Number *Black;
    cmsHTRANSFORM xform;
    cmsColorSpaceSignature Space;
    cmsUInt32Number nChannels;
    cmsUInt32Number dwFormat;
    cmsHPROFILE hLab;
    cmsCIELab  Lab;
    cmsCIEXYZ  BlackXYZ;

    // If the profile does not support input direction, assume Black point 0
    if (!cmsIsIntentSupported(ContextID, hInput, Intent, LCMS_USED_AS_INPUT)) {

        BlackPoint -> X = BlackPoint ->Y = BlackPoint -> Z = 0.0;
        return FALSE;
    }

    // Create a formatter which has n channels and floating point
    dwFormat = cmsFormatterForColorspaceOfProfile(ContextID, hInput, 2, FALSE);

   // Try to get black by using black colorant
    Space = cmsGetColorSpace(ContextID, hInput);

    // This function returns darker colorant in 16 bits for several spaces
    if (!_cmsEndPointsBySpace(Space, NULL, &Black, &nChannels)) {

        BlackPoint -> X = BlackPoint ->Y = BlackPoint -> Z = 0.0;
        return FALSE;
    }

    if (nChannels != T_CHANNELS(dwFormat)) {
       BlackPoint -> X = BlackPoint ->Y = BlackPoint -> Z = 0.0;
       return FALSE;
    }

    // Lab will be used as the output space, but lab2 will avoid recursion
    hLab = cmsCreateLab2Profile(ContextID, NULL);
    if (hLab == NULL) {
       BlackPoint -> X = BlackPoint ->Y = BlackPoint -> Z = 0.0;
       return FALSE;
    }

    // Create the transform
    xform = cmsCreateTransform(ContextID, hInput, dwFormat,
                                hLab, TYPE_Lab_DBL, Intent, cmsFLAGS_NOOPTIMIZE|cmsFLAGS_NOCACHE);
    cmsCloseProfile(ContextID, hLab);

    if (xform == NULL) {

        // Something went wrong. Get rid of open resources and return zero as black
        BlackPoint -> X = BlackPoint ->Y = BlackPoint -> Z = 0.0;
        return FALSE;
    }

    // Convert black to Lab
    cmsDoTransform(ContextID, xform, Black, &Lab, 1);

    // Force it to be neutral, clip to max. L* of 50
    Lab.a = Lab.b = 0;
    if (Lab.L > 50) Lab.L = 50;

    // Free the resources
    cmsDeleteTransform(ContextID, xform);

    // Convert from Lab (which is now clipped) to XYZ.
    cmsLab2XYZ(ContextID, NULL, &BlackXYZ, &Lab);

    if (BlackPoint != NULL)
        *BlackPoint = BlackXYZ;

    return TRUE;

    cmsUNUSED_PARAMETER(dwFlags);
}
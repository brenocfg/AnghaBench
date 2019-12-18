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
typedef  int /*<<< orphan*/  cmsMAT3 ;
typedef  int /*<<< orphan*/  cmsHPROFILE ;
typedef  int /*<<< orphan*/  cmsContext ;
typedef  int /*<<< orphan*/  cmsCIEXYZ ;
typedef  int /*<<< orphan*/  cmsBool ;

/* Variables and functions */
 int /*<<< orphan*/  TRUE ; 
 int /*<<< orphan*/  _cmsAdaptationMatrix (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  _cmsAssert (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  _cmsMAT3identity (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  cmsD50_XYZ (int /*<<< orphan*/ ) ; 
 scalar_t__ cmsGetDeviceClass (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int cmsGetEncodedICCversion (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ cmsReadTag (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  cmsSigChromaticAdaptationTag ; 
 scalar_t__ cmsSigDisplayClass ; 
 int /*<<< orphan*/  cmsSigMediaWhitePointTag ; 

cmsBool  _cmsReadCHAD(cmsContext ContextID, cmsMAT3* Dest, cmsHPROFILE hProfile)
{
    cmsMAT3* Tag;

    _cmsAssert(Dest != NULL);

    Tag = (cmsMAT3*) cmsReadTag(ContextID, hProfile, cmsSigChromaticAdaptationTag);

    if (Tag != NULL) {
        *Dest = *Tag;
        return TRUE;
    }

    // No CHAD available, default it to identity
    _cmsMAT3identity(ContextID, Dest);

    // V2 display profiles should give D50
    if (cmsGetEncodedICCversion(ContextID, hProfile) < 0x4000000) {

        if (cmsGetDeviceClass(ContextID, hProfile) == cmsSigDisplayClass) {

            cmsCIEXYZ* White = (cmsCIEXYZ*) cmsReadTag(ContextID, hProfile, cmsSigMediaWhitePointTag);

            if (White == NULL) {

                _cmsMAT3identity(ContextID, Dest);
                return TRUE;
            }

            return _cmsAdaptationMatrix(ContextID, Dest, NULL, White, cmsD50_XYZ(ContextID));
        }
    }

    return TRUE;
}
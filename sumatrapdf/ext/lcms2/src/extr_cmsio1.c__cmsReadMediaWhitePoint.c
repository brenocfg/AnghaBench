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
typedef  int /*<<< orphan*/  cmsHPROFILE ;
typedef  int /*<<< orphan*/  cmsContext ;
typedef  int /*<<< orphan*/  cmsCIEXYZ ;
typedef  int /*<<< orphan*/  cmsBool ;

/* Variables and functions */
 int /*<<< orphan*/  TRUE ; 
 int /*<<< orphan*/  _cmsAssert (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * cmsD50_XYZ (int /*<<< orphan*/ ) ; 
 scalar_t__ cmsGetDeviceClass (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int cmsGetEncodedICCversion (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ cmsReadTag (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ cmsSigDisplayClass ; 
 int /*<<< orphan*/  cmsSigMediaWhitePointTag ; 

cmsBool  _cmsReadMediaWhitePoint(cmsContext ContextID, cmsCIEXYZ* Dest, cmsHPROFILE hProfile)
{
    cmsCIEXYZ* Tag;

    _cmsAssert(Dest != NULL);

    Tag = (cmsCIEXYZ*) cmsReadTag(ContextID, hProfile, cmsSigMediaWhitePointTag);

    // If no wp, take D50
    if (Tag == NULL) {
        *Dest = *cmsD50_XYZ(ContextID);
        return TRUE;
    }

    // V2 display profiles should give D50
    if (cmsGetEncodedICCversion(ContextID, hProfile) < 0x4000000) {

        if (cmsGetDeviceClass(ContextID, hProfile) == cmsSigDisplayClass) {
            *Dest = *cmsD50_XYZ(ContextID);
            return TRUE;
        }
    }

    // All seems ok
    *Dest = *Tag;
    return TRUE;
}
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
typedef  int /*<<< orphan*/  cmsToneCurve ;
typedef  int /*<<< orphan*/  cmsHPROFILE ;
typedef  int /*<<< orphan*/  cmsFloat64Number ;
typedef  int /*<<< orphan*/  cmsContext ;
typedef  int /*<<< orphan*/  cmsBool ;

/* Variables and functions */
 int /*<<< orphan*/ * ComputeKToLstar (int /*<<< orphan*/ ,int,int,int const*,int /*<<< orphan*/  const*,int /*<<< orphan*/  const*,int /*<<< orphan*/  const*,int) ; 
 int /*<<< orphan*/  cmsFreeToneCurve (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 scalar_t__ cmsGetColorSpace (int /*<<< orphan*/ ,int /*<<< orphan*/  const) ; 
 scalar_t__ cmsGetDeviceClass (int /*<<< orphan*/ ,int /*<<< orphan*/  const) ; 
 int /*<<< orphan*/  cmsIsToneCurveMonotonic (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * cmsJoinToneCurve (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int) ; 
 scalar_t__ cmsSigCmykData ; 
 scalar_t__ cmsSigOutputClass ; 

cmsToneCurve* _cmsBuildKToneCurve(cmsContext        ContextID,
                                   cmsUInt32Number   nPoints,
                                   cmsUInt32Number   nProfiles,
                                   const cmsUInt32Number Intents[],
                                   const cmsHPROFILE hProfiles[],
                                   const cmsBool     BPC[],
                                   const cmsFloat64Number AdaptationStates[],
                                   cmsUInt32Number   dwFlags)
{
    cmsToneCurve *in, *out, *KTone;

    // Make sure CMYK -> CMYK
    if (cmsGetColorSpace(ContextID, hProfiles[0]) != cmsSigCmykData ||
        cmsGetColorSpace(ContextID, hProfiles[nProfiles-1])!= cmsSigCmykData) return NULL;


    // Make sure last is an output profile
    if (cmsGetDeviceClass(ContextID, hProfiles[nProfiles - 1]) != cmsSigOutputClass) return NULL;

    // Create individual curves. BPC works also as each K to L* is
    // computed as a BPC to zero black point in case of L*
    in  = ComputeKToLstar(ContextID, nPoints, nProfiles - 1, Intents, hProfiles, BPC, AdaptationStates, dwFlags);
    if (in == NULL) return NULL;

    out = ComputeKToLstar(ContextID, nPoints, 1,
                            Intents + (nProfiles - 1),
                            &hProfiles [nProfiles - 1],
                            BPC + (nProfiles - 1),
                            AdaptationStates + (nProfiles - 1),
                            dwFlags);
    if (out == NULL) {
        cmsFreeToneCurve(ContextID, in);
        return NULL;
    }

    // Build the relationship. This effectively limits the maximum accuracy to 16 bits, but
    // since this is used on black-preserving LUTs, we are not losing  accuracy in any case
    KTone = cmsJoinToneCurve(ContextID, in, out, nPoints);

    // Get rid of components
    cmsFreeToneCurve(ContextID, in); cmsFreeToneCurve(ContextID, out);

    // Something went wrong...
    if (KTone == NULL) return NULL;

    // Make sure it is monotonic
    if (!cmsIsToneCurveMonotonic(ContextID, KTone)) {
        cmsFreeToneCurve(ContextID, KTone);
        return NULL;
    }

    return KTone;
}
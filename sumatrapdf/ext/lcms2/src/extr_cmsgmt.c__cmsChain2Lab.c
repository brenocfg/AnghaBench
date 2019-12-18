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
typedef  int /*<<< orphan*/ * cmsHTRANSFORM ;
typedef  int /*<<< orphan*/ * cmsHPROFILE ;
typedef  double cmsFloat64Number ;
typedef  int /*<<< orphan*/  cmsContext ;
typedef  scalar_t__ cmsBool ;

/* Variables and functions */
 int INTENT_RELATIVE_COLORIMETRIC ; 
 int /*<<< orphan*/  cmsCloseProfile (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * cmsCreateExtendedTransform (int /*<<< orphan*/ ,int,int /*<<< orphan*/ **,scalar_t__*,int*,double*,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int,int,int) ; 
 int /*<<< orphan*/ * cmsCreateLab4Profile (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 

cmsHTRANSFORM _cmsChain2Lab(cmsContext            ContextID,
                            cmsUInt32Number        nProfiles,
                            cmsUInt32Number        InputFormat,
                            cmsUInt32Number        OutputFormat,
                            const cmsUInt32Number  Intents[],
                            const cmsHPROFILE      hProfiles[],
                            const cmsBool          BPC[],
                            const cmsFloat64Number AdaptationStates[],
                            cmsUInt32Number        dwFlags)
{
    cmsHTRANSFORM xform;
    cmsHPROFILE   hLab;
    cmsHPROFILE   ProfileList[256];
    cmsBool       BPCList[256];
    cmsFloat64Number AdaptationList[256];
    cmsUInt32Number IntentList[256];
    cmsUInt32Number i;

    // This is a rather big number and there is no need of dynamic memory
    // since we are adding a profile, 254 + 1 = 255 and this is the limit
    if (nProfiles > 254) return NULL;

    // The output space
    hLab = cmsCreateLab4Profile(ContextID, NULL);
    if (hLab == NULL) return NULL;

    // Create a copy of parameters
    for (i=0; i < nProfiles; i++) {

        ProfileList[i]    = hProfiles[i];
        BPCList[i]        = BPC[i];
        AdaptationList[i] = AdaptationStates[i];
        IntentList[i]     = Intents[i];
    }

    // Place Lab identity at chain's end.
    ProfileList[nProfiles]    = hLab;
    BPCList[nProfiles]        = 0;
    AdaptationList[nProfiles] = 1.0;
    IntentList[nProfiles]     = INTENT_RELATIVE_COLORIMETRIC;

    // Create the transform
    xform = cmsCreateExtendedTransform(ContextID, nProfiles + 1, ProfileList,
                                       BPCList,
                                       IntentList,
                                       AdaptationList,
                                       NULL, 0,
                                       InputFormat,
                                       OutputFormat,
                                       dwFlags);

    cmsCloseProfile(ContextID, hLab);

    return xform;
}
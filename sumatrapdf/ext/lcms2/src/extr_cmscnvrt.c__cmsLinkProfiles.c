#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
typedef  scalar_t__ cmsUInt32Number ;
typedef  int /*<<< orphan*/  cmsPipeline ;
struct TYPE_3__ {int /*<<< orphan*/ * (* Link ) (int /*<<< orphan*/ ,scalar_t__,scalar_t__*,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *,scalar_t__) ;} ;
typedef  TYPE_1__ cmsIntentsList ;
typedef  int /*<<< orphan*/  cmsHPROFILE ;
typedef  int /*<<< orphan*/  cmsFloat64Number ;
typedef  int /*<<< orphan*/  cmsContext ;
typedef  int /*<<< orphan*/  cmsBool ;

/* Variables and functions */
 int /*<<< orphan*/  FALSE ; 
 scalar_t__ INTENT_ABSOLUTE_COLORIMETRIC ; 
 scalar_t__ INTENT_PERCEPTUAL ; 
 scalar_t__ INTENT_SATURATION ; 
 TYPE_1__* SearchIntent (int /*<<< orphan*/ ,scalar_t__) ; 
 int /*<<< orphan*/  TRUE ; 
 int /*<<< orphan*/  cmsERROR_RANGE ; 
 int /*<<< orphan*/  cmsERROR_UNKNOWN_EXTENSION ; 
 int cmsGetEncodedICCversion (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  cmsSignalError (int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*,scalar_t__) ; 
 int /*<<< orphan*/ * stub1 (int /*<<< orphan*/ ,scalar_t__,scalar_t__*,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *,scalar_t__) ; 

cmsPipeline* _cmsLinkProfiles(cmsContext     ContextID,
                              cmsUInt32Number nProfiles,
                              cmsUInt32Number TheIntents[],
                              cmsHPROFILE     hProfiles[],
                              cmsBool         BPC[],
                              cmsFloat64Number AdaptationStates[],
                              cmsUInt32Number dwFlags)
{
    cmsUInt32Number i;
    cmsIntentsList* Intent;

    // Make sure a reasonable number of profiles is provided
    if (nProfiles <= 0 || nProfiles > 255) {
         cmsSignalError(ContextID, cmsERROR_RANGE, "Couldn't link '%d' profiles", nProfiles);
        return NULL;
    }

    for (i=0; i < nProfiles; i++) {

        // Check if black point is really needed or allowed. Note that
        // following Adobe's document:
        // BPC does not apply to devicelink profiles, nor to abs colorimetric,
        // and applies always on V4 perceptual and saturation.

        if (TheIntents[i] == INTENT_ABSOLUTE_COLORIMETRIC)
            BPC[i] = FALSE;

        if (TheIntents[i] == INTENT_PERCEPTUAL || TheIntents[i] == INTENT_SATURATION) {

            // Force BPC for V4 profiles in perceptual and saturation
            if (cmsGetEncodedICCversion(ContextID, hProfiles[i]) >= 0x4000000)
                BPC[i] = TRUE;
        }
    }

    // Search for a handler. The first intent in the chain defines the handler. That would
    // prevent using multiple custom intents in a multiintent chain, but the behaviour of
    // this case would present some issues if the custom intent tries to do things like
    // preserve primaries. This solution is not perfect, but works well on most cases.

    Intent = SearchIntent(ContextID, TheIntents[0]);
    if (Intent == NULL) {
        cmsSignalError(ContextID, cmsERROR_UNKNOWN_EXTENSION, "Unsupported intent '%d'", TheIntents[0]);
        return NULL;
    }

    // Call the handler
    return Intent ->Link(ContextID, nProfiles, TheIntents, hProfiles, BPC, AdaptationStates, dwFlags);
}
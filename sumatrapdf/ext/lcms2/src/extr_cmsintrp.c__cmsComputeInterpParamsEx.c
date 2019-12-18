#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
typedef  size_t cmsUInt32Number ;
struct TYPE_5__ {size_t dwFlags; size_t nInputs; size_t nOutputs; size_t* nSamples; size_t* Domain; size_t* opta; void const* Table; } ;
typedef  TYPE_1__ cmsInterpParams ;
typedef  int /*<<< orphan*/  cmsContext ;

/* Variables and functions */
 size_t MAX_INPUT_DIMENSIONS ; 
 int /*<<< orphan*/  _cmsFree (int /*<<< orphan*/ ,TYPE_1__*) ; 
 scalar_t__ _cmsMallocZero (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  _cmsSetInterpolationRoutine (int /*<<< orphan*/ ,TYPE_1__*) ; 
 int /*<<< orphan*/  cmsERROR_RANGE ; 
 int /*<<< orphan*/  cmsERROR_UNKNOWN_EXTENSION ; 
 int /*<<< orphan*/  cmsSignalError (int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*,size_t,size_t) ; 

cmsInterpParams* _cmsComputeInterpParamsEx(cmsContext ContextID,
                                           const cmsUInt32Number nSamples[],
                                           cmsUInt32Number InputChan, cmsUInt32Number OutputChan,
                                           const void *Table,
                                           cmsUInt32Number dwFlags)
{
    cmsInterpParams* p;
    cmsUInt32Number i;

    // Check for maximum inputs
    if (InputChan > MAX_INPUT_DIMENSIONS) {
             cmsSignalError(ContextID, cmsERROR_RANGE, "Too many input channels (%d channels, max=%d)", InputChan, MAX_INPUT_DIMENSIONS);
            return NULL;
    }

    // Creates an empty object
    p = (cmsInterpParams*) _cmsMallocZero(ContextID, sizeof(cmsInterpParams));
    if (p == NULL) return NULL;

    // Keep original parameters
    p -> dwFlags  = dwFlags;
    p -> nInputs  = InputChan;
    p -> nOutputs = OutputChan;
    p ->Table     = Table;

    // Fill samples per input direction and domain (which is number of nodes minus one)
    for (i=0; i < InputChan; i++) {

        p -> nSamples[i] = nSamples[i];
        p -> Domain[i]   = nSamples[i] - 1;
    }

    // Compute factors to apply to each component to index the grid array
    p -> opta[0] = p -> nOutputs;
    for (i=1; i < InputChan; i++)
        p ->opta[i] = p ->opta[i-1] * nSamples[InputChan-i];


    if (!_cmsSetInterpolationRoutine(ContextID, p)) {
         cmsSignalError(ContextID, cmsERROR_UNKNOWN_EXTENSION, "Unsupported interpolation (%d->%d channels)", InputChan, OutputChan);
        _cmsFree(ContextID, p);
        return NULL;
    }

    // All seems ok
    return p;
}
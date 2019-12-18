#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
typedef  size_t cmsUInt32Number ;
typedef  int /*<<< orphan*/  cmsUInt16Number ;
struct TYPE_2__ {size_t nOutputChans; scalar_t__ MaxTAC; int /*<<< orphan*/ * MaxInput; int /*<<< orphan*/  hRoundTrip; } ;
typedef  TYPE_1__ cmsTACestimator ;
typedef  scalar_t__ cmsFloat32Number ;
typedef  int /*<<< orphan*/  cmsContext ;

/* Variables and functions */
 int TRUE ; 
 int /*<<< orphan*/  cmsDoTransform (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/  const*,scalar_t__*,int) ; 
 int cmsMAXCHANNELS ; 
 int /*<<< orphan*/  cmsUNUSED_PARAMETER (int /*<<< orphan*/ *) ; 

__attribute__((used)) static
int EstimateTAC(cmsContext ContextID, register const cmsUInt16Number In[], register cmsUInt16Number Out[], register void * Cargo)
{
    cmsTACestimator* bp = (cmsTACestimator*) Cargo;
    cmsFloat32Number RoundTrip[cmsMAXCHANNELS];
    cmsUInt32Number i;
    cmsFloat32Number Sum;


    // Evaluate the xform
    cmsDoTransform(ContextID, bp->hRoundTrip, In, RoundTrip, 1);

    // All all amounts of ink
    for (Sum=0, i=0; i < bp ->nOutputChans; i++)
            Sum += RoundTrip[i];

    // If above maximum, keep track of input values
    if (Sum > bp ->MaxTAC) {

            bp ->MaxTAC = Sum;

            for (i=0; i < bp ->nOutputChans; i++) {
                bp ->MaxInput[i] = In[i];
            }
    }

    return TRUE;

    cmsUNUSED_PARAMETER(Out);
}
#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
typedef  int cmsUInt32Number ;
struct TYPE_4__ {int /*<<< orphan*/  Lerp16; int /*<<< orphan*/  LerpFloat; } ;
typedef  TYPE_1__ cmsInterpFunction ;
typedef  int /*<<< orphan*/  cmsContext ;
typedef  int cmsBool ;
typedef  int /*<<< orphan*/  Interpolation ;

/* Variables and functions */
 int CMS_LERP_FLAGS_FLOAT ; 
 int /*<<< orphan*/  Fake1Dfloat ; 
 int /*<<< orphan*/  Fake3D16 ; 
 int /*<<< orphan*/  memset (TYPE_1__*,int /*<<< orphan*/ ,int) ; 

cmsInterpFunction my_Interpolators_Factory(cmsContext ContextID, cmsUInt32Number nInputChannels,
                                           cmsUInt32Number nOutputChannels,
                                           cmsUInt32Number dwFlags)
{
    cmsInterpFunction Interpolation;
    cmsBool  IsFloat = (dwFlags & CMS_LERP_FLAGS_FLOAT);

    // Initialize the return to zero as a non-supported mark
    memset(&Interpolation, 0, sizeof(Interpolation));

    // For 1D to 1D and floating point
    if (nInputChannels == 1 && nOutputChannels == 1 && IsFloat) {

        Interpolation.LerpFloat = Fake1Dfloat;
    }
    else
    if (nInputChannels == 3 && nOutputChannels == 3 && !IsFloat) {

        // For 3D to 3D and 16 bits
        Interpolation.Lerp16 = Fake3D16;
    }

    // Here is the interpolation
    return Interpolation;
}
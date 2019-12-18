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
typedef  int /*<<< orphan*/  cmsUInt8Number ;
typedef  int /*<<< orphan*/ * cmsUInt32Number ;
typedef  int /*<<< orphan*/  cmsUInt16Number ;
typedef  int /*<<< orphan*/  cmsContext ;
typedef  int /*<<< orphan*/  _cmsTRANSFORM ;

/* Variables and functions */
 void* FROM_16_TO_8 (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  cmsUNUSED_PARAMETER (int /*<<< orphan*/ *) ; 

__attribute__((used)) static
cmsUInt8Number* Pack6BytesSwap(cmsContext ContextID, register _cmsTRANSFORM* info,
                               register cmsUInt16Number wOut[],
                               register cmsUInt8Number* output,
                               register cmsUInt32Number Stride)
{
    *output++ = FROM_16_TO_8(wOut[5]);
    *output++ = FROM_16_TO_8(wOut[4]);
    *output++ = FROM_16_TO_8(wOut[3]);
    *output++ = FROM_16_TO_8(wOut[2]);
    *output++ = FROM_16_TO_8(wOut[1]);
    *output++ = FROM_16_TO_8(wOut[0]);

    return output;

    cmsUNUSED_PARAMETER(info);
    cmsUNUSED_PARAMETER(Stride);
}
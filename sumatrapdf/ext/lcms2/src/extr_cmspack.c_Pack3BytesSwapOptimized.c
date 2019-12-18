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
typedef  int cmsUInt16Number ;
typedef  int /*<<< orphan*/  cmsContext ;
typedef  int /*<<< orphan*/  _cmsTRANSFORM ;

/* Variables and functions */
 int /*<<< orphan*/  cmsUNUSED_PARAMETER (int /*<<< orphan*/ *) ; 

__attribute__((used)) static
cmsUInt8Number* Pack3BytesSwapOptimized(cmsContext ContextID, register _cmsTRANSFORM* info,
                                        register cmsUInt16Number wOut[],
                                        register cmsUInt8Number* output,
                                        register cmsUInt32Number Stride)
{
    *output++ = (wOut[2] & 0xFFU);
    *output++ = (wOut[1] & 0xFFU);
    *output++ = (wOut[0] & 0xFFU);

    return output;

    cmsUNUSED_PARAMETER(info);
    cmsUNUSED_PARAMETER(Stride);
}
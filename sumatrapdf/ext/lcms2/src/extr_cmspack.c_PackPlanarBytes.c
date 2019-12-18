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
typedef  scalar_t__ cmsUInt8Number ;
typedef  int cmsUInt32Number ;
typedef  int /*<<< orphan*/  cmsUInt16Number ;
typedef  int /*<<< orphan*/  cmsContext ;
struct TYPE_3__ {int /*<<< orphan*/  OutputFormat; } ;
typedef  TYPE_1__ _cmsTRANSFORM ;

/* Variables and functions */
 scalar_t__ FROM_16_TO_8 (int /*<<< orphan*/ ) ; 
 scalar_t__ REVERSE_FLAVOR_8 (scalar_t__) ; 
 int T_CHANNELS (int /*<<< orphan*/ ) ; 
 int T_DOSWAP (int /*<<< orphan*/ ) ; 
 int T_EXTRA (int /*<<< orphan*/ ) ; 
 int T_FLAVOR (int /*<<< orphan*/ ) ; 
 int T_SWAPFIRST (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  cmsUNUSED_PARAMETER (int) ; 

__attribute__((used)) static
cmsUInt8Number* PackPlanarBytes(cmsContext ContextID, register _cmsTRANSFORM* info,
                                register cmsUInt16Number wOut[],
                                register cmsUInt8Number* output,
                                register cmsUInt32Number Stride)
{
    cmsUInt32Number nChan     = T_CHANNELS(info -> OutputFormat);
    cmsUInt32Number DoSwap    = T_DOSWAP(info ->OutputFormat);
    cmsUInt32Number SwapFirst = T_SWAPFIRST(info ->OutputFormat);
    cmsUInt32Number Reverse   = T_FLAVOR(info ->OutputFormat);
    cmsUInt32Number i;
    cmsUInt8Number* Init = output;


    if (DoSwap ^ SwapFirst) {
        output += T_EXTRA(info -> OutputFormat) * Stride;
    }


    for (i=0; i < nChan; i++) {

        cmsUInt32Number index = DoSwap ? (nChan - i - 1) : i;
        cmsUInt8Number v = FROM_16_TO_8(wOut[index]);

        *(cmsUInt8Number*)  output = (cmsUInt8Number) (Reverse ? REVERSE_FLAVOR_8(v) : v);
        output += Stride;
    }

    return (Init + 1);

    cmsUNUSED_PARAMETER(Stride);
}
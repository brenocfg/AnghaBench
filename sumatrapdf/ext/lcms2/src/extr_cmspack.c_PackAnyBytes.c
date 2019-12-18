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
typedef  int /*<<< orphan*/  cmsUInt8Number ;
typedef  scalar_t__ cmsUInt32Number ;
typedef  int /*<<< orphan*/  cmsUInt16Number ;
typedef  int /*<<< orphan*/  cmsContext ;
struct TYPE_3__ {int /*<<< orphan*/  OutputFormat; } ;
typedef  TYPE_1__ _cmsTRANSFORM ;

/* Variables and functions */
 int /*<<< orphan*/  FROM_16_TO_8 (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  REVERSE_FLAVOR_8 (int /*<<< orphan*/ ) ; 
 scalar_t__ T_CHANNELS (int /*<<< orphan*/ ) ; 
 scalar_t__ T_DOSWAP (int /*<<< orphan*/ ) ; 
 scalar_t__ T_EXTRA (int /*<<< orphan*/ ) ; 
 scalar_t__ T_FLAVOR (int /*<<< orphan*/ ) ; 
 scalar_t__ T_SWAPFIRST (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  cmsUNUSED_PARAMETER (scalar_t__) ; 
 int /*<<< orphan*/  memmove (int /*<<< orphan*/ *,int /*<<< orphan*/ *,scalar_t__) ; 

__attribute__((used)) static
cmsUInt8Number* PackAnyBytes(cmsContext ContextID, register _cmsTRANSFORM* info,
                             register cmsUInt16Number wOut[],
                             register cmsUInt8Number* output,
                             register cmsUInt32Number Stride)
{
    cmsUInt32Number nChan  = T_CHANNELS(info -> OutputFormat);
    cmsUInt32Number DoSwap   = T_DOSWAP(info ->OutputFormat);
    cmsUInt32Number Reverse    = T_FLAVOR(info ->OutputFormat);
    cmsUInt32Number Extra   = T_EXTRA(info -> OutputFormat);
    cmsUInt32Number SwapFirst  = T_SWAPFIRST(info -> OutputFormat);
    cmsUInt32Number ExtraFirst = DoSwap ^ SwapFirst;
    cmsUInt8Number* swap1;
    cmsUInt8Number v = 0;
    cmsUInt32Number i;

    swap1 = output;

    if (ExtraFirst) {
        output += Extra;
    }

    for (i=0; i < nChan; i++) {

        cmsUInt32Number index = DoSwap ? (nChan - i - 1) : i;

        v = FROM_16_TO_8(wOut[index]);

        if (Reverse)
            v = REVERSE_FLAVOR_8(v);

        *output++ = v;
    }

    if (!ExtraFirst) {
        output += Extra;
    }

    if (Extra == 0 && SwapFirst) {

        memmove(swap1 + 1, swap1, nChan-1);
        *swap1 = v;
    }


    return output;

    cmsUNUSED_PARAMETER(Stride);
}
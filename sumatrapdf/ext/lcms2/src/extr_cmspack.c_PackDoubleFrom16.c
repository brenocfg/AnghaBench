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
typedef  int cmsUInt32Number ;
typedef  int /*<<< orphan*/  cmsUInt16Number ;
typedef  double cmsFloat64Number ;
typedef  int /*<<< orphan*/  cmsContext ;
struct TYPE_3__ {int /*<<< orphan*/  OutputFormat; } ;
typedef  TYPE_1__ _cmsTRANSFORM ;

/* Variables and functions */
 scalar_t__ IsInkSpace (int /*<<< orphan*/ ) ; 
 int PixelSize (int /*<<< orphan*/ ) ; 
 int T_CHANNELS (int /*<<< orphan*/ ) ; 
 int T_DOSWAP (int /*<<< orphan*/ ) ; 
 int T_EXTRA (int /*<<< orphan*/ ) ; 
 int T_FLAVOR (int /*<<< orphan*/ ) ; 
 int T_PLANAR (int /*<<< orphan*/ ) ; 
 int T_SWAPFIRST (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  memmove (double*,double*,int) ; 

__attribute__((used)) static
cmsUInt8Number* PackDoubleFrom16(cmsContext ContextID, register _cmsTRANSFORM* info,
                                register cmsUInt16Number wOut[],
                                register cmsUInt8Number* output,
                                register cmsUInt32Number Stride)
{
    cmsUInt32Number nChan      = T_CHANNELS(info -> OutputFormat);
    cmsUInt32Number DoSwap     = T_DOSWAP(info ->OutputFormat);
    cmsUInt32Number Reverse    = T_FLAVOR(info ->OutputFormat);
    cmsUInt32Number Extra      = T_EXTRA(info -> OutputFormat);
    cmsUInt32Number SwapFirst  = T_SWAPFIRST(info -> OutputFormat);
    cmsUInt32Number Planar     = T_PLANAR(info -> OutputFormat);
    cmsUInt32Number ExtraFirst = DoSwap ^ SwapFirst;
    cmsFloat64Number maximum = IsInkSpace(info ->OutputFormat) ? 655.35 : 65535.0;
    cmsFloat64Number v = 0;
    cmsFloat64Number* swap1 = (cmsFloat64Number*) output;
    cmsUInt32Number i, start = 0;

    Stride /= PixelSize(info->OutputFormat);

    if (ExtraFirst)
        start = Extra;

    for (i=0; i < nChan; i++) {

        cmsUInt32Number index = DoSwap ? (nChan - i - 1) : i;

        v = (cmsFloat64Number) wOut[index] / maximum;

        if (Reverse)
            v = maximum - v;

        if (Planar)
            ((cmsFloat64Number*) output)[(i + start)  * Stride]= v;
        else
            ((cmsFloat64Number*) output)[i + start] = v;
    }


    if (Extra == 0 && SwapFirst) {

         memmove(swap1 + 1, swap1, (nChan-1)* sizeof(cmsFloat64Number));
        *swap1 = v;
    }

    if (T_PLANAR(info -> OutputFormat))
        return output + sizeof(cmsFloat64Number);
    else
        return output + (nChan + Extra) * sizeof(cmsFloat64Number);

}
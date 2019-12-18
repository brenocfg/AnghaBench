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
typedef  int cmsFloat32Number ;
typedef  int /*<<< orphan*/  cmsContext ;
struct TYPE_3__ {int /*<<< orphan*/  InputFormat; } ;
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
 int /*<<< orphan*/  memmove (int*,int*,int) ; 

__attribute__((used)) static
cmsUInt8Number* UnrollFloatsToFloat(cmsContext ContextID, _cmsTRANSFORM* info,
                                    cmsFloat32Number wIn[],
                                    cmsUInt8Number* accum,
                                    cmsUInt32Number Stride)
{

    cmsUInt32Number nChan  = T_CHANNELS(info -> InputFormat);
    cmsUInt32Number DoSwap   = T_DOSWAP(info ->InputFormat);
    cmsUInt32Number Reverse    = T_FLAVOR(info ->InputFormat);
    cmsUInt32Number SwapFirst  = T_SWAPFIRST(info -> InputFormat);
    cmsUInt32Number Extra   = T_EXTRA(info -> InputFormat);
    cmsUInt32Number ExtraFirst = DoSwap ^ SwapFirst;
    cmsUInt32Number Planar     = T_PLANAR(info -> InputFormat);
    cmsFloat32Number v;
    cmsUInt32Number i, start = 0;
    cmsFloat32Number maximum = IsInkSpace(info ->InputFormat) ? 100.0F : 1.0F;

    Stride /= PixelSize(info->InputFormat);

    if (ExtraFirst)
            start = Extra;

    for (i=0; i < nChan; i++) {

        cmsUInt32Number index = DoSwap ? (nChan - i - 1) : i;

        if (Planar)
            v = (cmsFloat32Number) ((cmsFloat32Number*) accum)[(i + start) * Stride];
        else
            v = (cmsFloat32Number) ((cmsFloat32Number*) accum)[i + start];

        v /= maximum;

        wIn[index] = Reverse ? 1 - v : v;
    }


    if (Extra == 0 && SwapFirst) {
        cmsFloat32Number tmp = wIn[0];

        memmove(&wIn[0], &wIn[1], (nChan-1) * sizeof(cmsFloat32Number));
        wIn[nChan-1] = tmp;
    }

    if (T_PLANAR(info -> InputFormat))
        return accum + sizeof(cmsFloat32Number);
    else
        return accum + (nChan + Extra) * sizeof(cmsFloat32Number);
}
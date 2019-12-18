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
struct TYPE_3__ {int /*<<< orphan*/  InputFormat; } ;
typedef  TYPE_1__ _cmsTRANSFORM ;

/* Variables and functions */
 int /*<<< orphan*/  CHANGE_ENDIAN (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  REVERSE_FLAVOR_16 (int /*<<< orphan*/ ) ; 
 scalar_t__ T_CHANNELS (int /*<<< orphan*/ ) ; 
 scalar_t__ T_DOSWAP (int /*<<< orphan*/ ) ; 
 scalar_t__ T_ENDIAN16 (int /*<<< orphan*/ ) ; 
 scalar_t__ T_EXTRA (int /*<<< orphan*/ ) ; 
 scalar_t__ T_FLAVOR (int /*<<< orphan*/ ) ; 

__attribute__((used)) static
cmsUInt8Number* UnrollPlanarWords(cmsContext ContextID, register _cmsTRANSFORM* info,
                                  register cmsUInt16Number wIn[],
                                  register cmsUInt8Number* accum,
                                  register cmsUInt32Number Stride)
{
    cmsUInt32Number nChan = T_CHANNELS(info -> InputFormat);
    cmsUInt32Number DoSwap= T_DOSWAP(info ->InputFormat);
    cmsUInt32Number Reverse= T_FLAVOR(info ->InputFormat);
    cmsUInt32Number SwapEndian = T_ENDIAN16(info -> InputFormat);
    cmsUInt32Number i;
    cmsUInt8Number* Init = accum;

    if (DoSwap) {
        accum += T_EXTRA(info -> InputFormat) * Stride;
    }

    for (i=0; i < nChan; i++) {

        cmsUInt32Number index = DoSwap ? (nChan - i - 1) : i;
        cmsUInt16Number v = *(cmsUInt16Number*) accum;

        if (SwapEndian)
            v = CHANGE_ENDIAN(v);

        wIn[index] = Reverse ? REVERSE_FLAVOR_16(v) : v;

        accum +=  Stride;
    }

    return (Init + sizeof(cmsUInt16Number));
}
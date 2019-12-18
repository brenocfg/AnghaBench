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
typedef  int /*<<< orphan*/  cmsContext ;
struct TYPE_3__ {int /*<<< orphan*/  InputFormat; } ;
typedef  TYPE_1__ _cmsTRANSFORM ;

/* Variables and functions */
 int /*<<< orphan*/  CHANGE_ENDIAN (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  REVERSE_FLAVOR_16 (int /*<<< orphan*/ ) ; 
 int T_CHANNELS (int /*<<< orphan*/ ) ; 
 int T_DOSWAP (int /*<<< orphan*/ ) ; 
 int T_ENDIAN16 (int /*<<< orphan*/ ) ; 
 int T_EXTRA (int /*<<< orphan*/ ) ; 
 int T_FLAVOR (int /*<<< orphan*/ ) ; 
 int T_SWAPFIRST (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  cmsUNUSED_PARAMETER (int) ; 
 int /*<<< orphan*/  memmove (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int) ; 

__attribute__((used)) static
cmsUInt8Number* UnrollAnyWords(cmsContext ContextID, register _cmsTRANSFORM* info,
                               register cmsUInt16Number wIn[],
                               register cmsUInt8Number* accum,
                               register cmsUInt32Number Stride)
{
   cmsUInt32Number nChan       = T_CHANNELS(info -> InputFormat);
   cmsUInt32Number SwapEndian  = T_ENDIAN16(info -> InputFormat);
   cmsUInt32Number DoSwap      = T_DOSWAP(info ->InputFormat);
   cmsUInt32Number Reverse     = T_FLAVOR(info ->InputFormat);
   cmsUInt32Number SwapFirst   = T_SWAPFIRST(info -> InputFormat);
   cmsUInt32Number Extra       = T_EXTRA(info -> InputFormat);
   cmsUInt32Number ExtraFirst  = DoSwap ^ SwapFirst;
   cmsUInt32Number i;

    if (ExtraFirst) {
        accum += Extra * sizeof(cmsUInt16Number);
    }

    for (i=0; i < nChan; i++) {

        cmsUInt32Number index = DoSwap ? (nChan - i - 1) : i;
        cmsUInt16Number v = *(cmsUInt16Number*) accum;

        if (SwapEndian)
            v = CHANGE_ENDIAN(v);

        wIn[index] = Reverse ? REVERSE_FLAVOR_16(v) : v;

        accum += sizeof(cmsUInt16Number);
    }

    if (!ExtraFirst) {
        accum += Extra * sizeof(cmsUInt16Number);
    }

    if (Extra == 0 && SwapFirst) {

        cmsUInt16Number tmp = wIn[0];

        memmove(&wIn[0], &wIn[1], (nChan-1) * sizeof(cmsUInt16Number));
        wIn[nChan-1] = tmp;
    }

    return accum;

    cmsUNUSED_PARAMETER(Stride);
}
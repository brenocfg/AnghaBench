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
typedef  scalar_t__ cmsUInt16Number ;
typedef  float cmsFloat32Number ;
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
 scalar_t__ _cmsFloat2Half (float) ; 
 int /*<<< orphan*/  memmove (scalar_t__*,scalar_t__*,int) ; 

__attribute__((used)) static
cmsUInt8Number* PackHalfFromFloat(cmsContext ContextID, _cmsTRANSFORM* info,
                                    cmsFloat32Number wOut[],
                                    cmsUInt8Number* output,
                                    cmsUInt32Number Stride)
{
       cmsUInt32Number nChan      = T_CHANNELS(info->OutputFormat);
       cmsUInt32Number DoSwap     = T_DOSWAP(info->OutputFormat);
       cmsUInt32Number Reverse    = T_FLAVOR(info->OutputFormat);
       cmsUInt32Number Extra      = T_EXTRA(info->OutputFormat);
       cmsUInt32Number SwapFirst  = T_SWAPFIRST(info->OutputFormat);
       cmsUInt32Number Planar     = T_PLANAR(info->OutputFormat);
       cmsUInt32Number ExtraFirst = DoSwap ^ SwapFirst;
       cmsFloat32Number maximum = IsInkSpace(info->OutputFormat) ? 100.0F : 1.0F;
       cmsUInt16Number* swap1 = (cmsUInt16Number*)output;
       cmsFloat32Number v = 0;
       cmsUInt32Number i, start = 0;

       Stride /= PixelSize(info->OutputFormat);

       if (ExtraFirst)
              start = Extra;

       for (i = 0; i < nChan; i++) {

           cmsUInt32Number index = DoSwap ? (nChan - i - 1) : i;

              v = wOut[index] * maximum;

              if (Reverse)
                     v = maximum - v;

              if (Planar)
                     ((cmsUInt16Number*)output)[(i + start)* Stride] = _cmsFloat2Half(v);
              else
                     ((cmsUInt16Number*)output)[i + start] = _cmsFloat2Half(v);
       }


       if (Extra == 0 && SwapFirst) {

              memmove(swap1 + 1, swap1, (nChan - 1)* sizeof(cmsUInt16Number));
              *swap1 = (cmsUInt16Number)_cmsFloat2Half(v);
       }

       if (T_PLANAR(info->OutputFormat))
              return output + sizeof(cmsUInt16Number);
       else
              return output + (nChan + Extra)* sizeof(cmsUInt16Number);
}
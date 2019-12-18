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
typedef  int cmsUInt32Number ;

/* Variables and functions */
 int BYTES_SH (int) ; 
 int CHANNELS_SH (int) ; 
 int COLORSPACE_SH (int) ; 
 int ChanCountFromPixelType (int) ; 
 int FLOAT_SH (int) ; 
 int PLANAR_SH (int) ; 
 int T_PLANAR (int) ; 

__attribute__((used)) static
cmsUInt32Number ComputeOutputFormatDescriptor(cmsUInt32Number dwInput, int OutColorSpace, int bps)
{
    int IsPlanar  = T_PLANAR(dwInput);
    int Channels  = ChanCountFromPixelType(OutColorSpace);
    int IsFlt = (bps == 0) || (bps == 4);

    return (FLOAT_SH(IsFlt)|COLORSPACE_SH(OutColorSpace)|PLANAR_SH(IsPlanar)|CHANNELS_SH(Channels)|BYTES_SH(bps));
}
#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
typedef  int cmsUInt32Number ;
struct TYPE_2__ {int /*<<< orphan*/  write_Adobe_marker; } ;

/* Variables and functions */
 int BYTES_SH (int) ; 
 int CHANNELS_SH (int) ; 
 int COLORSPACE_SH (int) ; 
 TYPE_1__ Compressor ; 
 int FLAVOR_SH (int) ; 
 int /*<<< orphan*/  FatalError (char*) ; 
 int PLANAR_SH (int) ; 
#define  PT_CMY 134 
#define  PT_CMYK 133 
#define  PT_GRAY 132 
#define  PT_Lab 131 
#define  PT_RGB 130 
#define  PT_YCbCr 129 
#define  PT_YUV 128 
 int T_PLANAR (int) ; 

__attribute__((used)) static
cmsUInt32Number ComputeOutputFormatDescriptor(cmsUInt32Number dwInput, int OutColorSpace)
{
    int IsPlanar  = T_PLANAR(dwInput);
    int Channels  = 0;
    int Flavor    = 0;

    switch (OutColorSpace) {

   case PT_GRAY:
       Channels = 1;
       break;
   case PT_RGB:
   case PT_CMY:
   case PT_Lab:
   case PT_YUV:
   case PT_YCbCr:
       Channels = 3;
       break;

   case PT_CMYK:
       if (Compressor.write_Adobe_marker)   // Adobe keeps CMYK inverted, so change flavor to chocolate
           Flavor = 1;
       Channels = 4;
       break;
   default:
       FatalError("Unsupported output color space");
    }

    return (COLORSPACE_SH(OutColorSpace)|PLANAR_SH(IsPlanar)|CHANNELS_SH(Channels)|BYTES_SH(1)|FLAVOR_SH(Flavor));
}
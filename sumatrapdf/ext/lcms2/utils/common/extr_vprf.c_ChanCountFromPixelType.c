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

/* Variables and functions */
 int /*<<< orphan*/  FatalError (char*,int) ; 
#define  PT_CMY 148 
#define  PT_CMYK 147 
#define  PT_GRAY 146 
#define  PT_Lab 145 
#define  PT_MCH10 144 
#define  PT_MCH11 143 
#define  PT_MCH12 142 
#define  PT_MCH13 141 
#define  PT_MCH14 140 
#define  PT_MCH15 139 
#define  PT_MCH2 138 
#define  PT_MCH3 137 
#define  PT_MCH4 136 
#define  PT_MCH5 135 
#define  PT_MCH6 134 
#define  PT_MCH7 133 
#define  PT_MCH8 132 
#define  PT_MCH9 131 
#define  PT_RGB 130 
#define  PT_YCbCr 129 
#define  PT_YUV 128 

int ChanCountFromPixelType(int ColorChannels)
{
    switch (ColorChannels) {

      case PT_GRAY: return 1;

      case PT_RGB:
      case PT_CMY:
      case PT_Lab:
      case PT_YUV:
      case PT_YCbCr: return 3;

      case PT_CMYK: return 4 ;
      case PT_MCH2: return 2 ;
      case PT_MCH3: return 3 ;
      case PT_MCH4: return 4 ;
      case PT_MCH5: return 5 ;
      case PT_MCH6: return 6 ;
      case PT_MCH7: return 7 ;
      case PT_MCH8: return 8 ;
      case PT_MCH9: return 9 ;
      case PT_MCH10: return 10;
      case PT_MCH11: return 11;
      case PT_MCH12: return 12;
      case PT_MCH13: return 12;
      case PT_MCH14: return 14;
      case PT_MCH15: return 15;

      default:

          FatalError("Unsupported color space of %d channels", ColorChannels);
          return -1;
    }
}
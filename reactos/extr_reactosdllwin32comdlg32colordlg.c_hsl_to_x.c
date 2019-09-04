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
 int min (int,int) ; 

__attribute__((used)) static int hsl_to_x(int hue, int sat, int lum)
{
 int res = 0, maxrgb;

 /* l below 120 */
 maxrgb = (256 * min(120,lum)) / 120;  /* 0 .. 256 */
 if (hue < 80)
  res = 0;
 else
  if (hue < 120)
  {
   res = (hue - 80) * maxrgb;           /* 0...10240 */
   res /= 40;                        /* 0...256 */
  }
  else
   if (hue < 200)
    res = maxrgb;
   else
    {
     res= (240 - hue) * maxrgb;
     res /= 40;
    }
 res = res - maxrgb / 2;                 /* -128...128 */

 /* saturation */
 res = maxrgb / 2 + (sat * res) / 240;    /* 0..256 */

 /* lum above 120 */
 if (lum > 120 && res < 256)
  res += ((lum - 120) * (256 - res)) / 120;

 return min(res, 255);
}
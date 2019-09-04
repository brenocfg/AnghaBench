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
typedef  int uint8 ;
typedef  int uint16 ;

/* Variables and functions */

void set_pixel2(int x, int y, int pixel, uint8* data, int width, int bpp)
{
  if (bpp == 8)
    data[y * width + x] = pixel;
  else if (bpp == 16)
    ((uint16*)data)[y * width + x] = pixel;
}
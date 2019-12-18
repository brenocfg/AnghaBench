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

int get_pixel2(int x, int y, uint8* data, int width, int bpp)
{
  if (bpp == 8)
    return data[y * width + x];
  else if (bpp == 16)
    return ((uint16*)data)[y * width + x];
  else
    return 0;
}
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
typedef  int BOOL ;

/* Variables and functions */
 int False ; 

BOOL is_pixel_on(uint8* data, int x, int y, int width, int bpp)
{
  int start;
  int shift;

  if (bpp == 1)
  {
    width = (width + 7) / 8;
    start = (y * width) + x / 8;
    shift = x % 8;
    return (data[start] & (0x80 >> shift)) != 0;
  }
  else if (bpp == 8)
  {
    return data[y * width + x] != 0;
  }
  else if (bpp == 24)
  {
    return data[(y * 3) * width + (x * 3)] != 0 &&
           data[(y * 3) * width + (x * 3) + 1] != 0 &&
           data[(y * 3) * width + (x * 3) + 2] != 0;
  }
  else
    return False;
}
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
typedef  int uint16 ;

/* Variables and functions */
 int g_height ; 
 int g_server_Bpp ; 
 int g_width ; 
 int* sdata ; 
 int vga_getpixel (int,int) ; 

int get_pixel(int x, int y)
{
  if (x >= 0 && x < g_width && y >= 0 && y < g_height)
  {
    if (sdata != 0)
    {
      if (g_server_Bpp == 1)
        return sdata[y * g_width + x];
      else if (g_server_Bpp == 2)
        return ((uint16*)sdata)[y * g_width + x];
      else
        return 0;
    }
    else
      return vga_getpixel(x, y);
  }
  else
    return 0;
}
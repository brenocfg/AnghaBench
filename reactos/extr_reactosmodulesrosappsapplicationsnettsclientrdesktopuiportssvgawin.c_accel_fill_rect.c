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
 int /*<<< orphan*/  ACCEL_FILLBOX ; 
 int /*<<< orphan*/  ACCEL_SETFGCOLOR ; 
 int /*<<< orphan*/  copy_mem (int*,int*,int) ; 
 int g_server_Bpp ; 
 int /*<<< orphan*/  g_server_bpp ; 
 int g_width ; 
 int* get_ptr (int,int,scalar_t__,int,int /*<<< orphan*/ ) ; 
 scalar_t__ has_fill_box ; 
 scalar_t__ sdata ; 
 int /*<<< orphan*/  vga_accel (int /*<<< orphan*/ ,int,...) ; 
 int /*<<< orphan*/  vga_drawscansegment (int*,int,int,int) ; 
 int /*<<< orphan*/  xfree (int*) ; 
 int* xmalloc (int) ; 

void accel_fill_rect(int x, int y, int cx, int cy, int color)
{
  int i;
  uint8* temp;
  uint8* d;

  if (sdata != 0)
  {
    temp = xmalloc(cx * g_server_Bpp);
    if (g_server_Bpp == 1)
      for (i = 0; i < cx; i++)
        temp[i] = color;
    else if (g_server_Bpp == 2)
      for (i = 0; i < cx; i++)
        ((uint16*)temp)[i] = color;
    d = get_ptr(x, y, sdata, g_width, g_server_bpp);
    for (i = 0; i < cy; i++)
    {
      copy_mem(d, temp, cx * g_server_Bpp);
      d = d + g_width * g_server_Bpp;
    }
    xfree(temp);
  }
  else if (has_fill_box)
  {
    vga_accel(ACCEL_SETFGCOLOR, color);
    vga_accel(ACCEL_FILLBOX, x, y, cx, cy);
  }
  else
  {
    temp = xmalloc(cx * g_server_Bpp);
    if (g_server_Bpp == 1)
      for (i = 0; i < cx; i++)
        temp[i] = color;
    else if (g_server_Bpp == 2)
      for (i = 0; i < cx; i++)
        ((uint16*)temp)[i] = color;
    for (i = 0; i < cy; i++)
      vga_drawscansegment(temp, x, y + i, cx * g_server_Bpp);
    xfree(temp);
  }
}
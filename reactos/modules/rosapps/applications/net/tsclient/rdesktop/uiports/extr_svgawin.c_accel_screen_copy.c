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
typedef  int /*<<< orphan*/  uint8 ;

/* Variables and functions */
 int /*<<< orphan*/  ACCEL_SCREENCOPY ; 
 int /*<<< orphan*/  copy_mem (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  copy_memb (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int) ; 
 int g_server_Bpp ; 
 int /*<<< orphan*/  g_server_bpp ; 
 int g_width ; 
 int /*<<< orphan*/ * get_ptr (int,int,scalar_t__,int,int /*<<< orphan*/ ) ; 
 scalar_t__ has_screen_copy ; 
 scalar_t__ sdata ; 
 int /*<<< orphan*/  vga_accel (int /*<<< orphan*/ ,int,int,int,int,int,int) ; 
 int /*<<< orphan*/  vga_drawscansegment (int /*<<< orphan*/ *,int,int,int) ; 
 int /*<<< orphan*/  vga_getscansegment (int /*<<< orphan*/ *,int,int,int) ; 
 int /*<<< orphan*/  xfree (int /*<<< orphan*/ *) ; 
 scalar_t__ xmalloc (int) ; 

void accel_screen_copy(int x, int y, int cx, int cy, int srcx, int srcy)
{
  uint8* temp;
  uint8* s;
  uint8* d;
  int i;

  if (sdata != 0)
  {
    if (srcy < y)
    { // bottom to top
      s = get_ptr(srcx, (srcy + cy) - 1, sdata, g_width, g_server_bpp);
      d = get_ptr(x, (y + cy) - 1, sdata, g_width, g_server_bpp);
      for (i = 0; i < cy; i++)  // copy down
      {
        copy_mem(d, s, cx * g_server_Bpp);
        s = s - g_width * g_server_Bpp;
        d = d - g_width * g_server_Bpp;
      }
    }
    else if (srcy > y || srcx > x) // copy up or left
    { // top to bottom
      s = get_ptr(srcx, srcy, sdata, g_width, g_server_bpp);
      d = get_ptr(x, y, sdata, g_width, g_server_bpp);
      for (i = 0; i < cy; i++)
      {
        copy_mem(d, s, cx * g_server_Bpp);
        s = s + g_width * g_server_Bpp;
        d = d + g_width * g_server_Bpp;
      }
    }
    else // copy straight right
    {
      s = get_ptr(srcx, srcy, sdata, g_width, g_server_bpp);
      d = get_ptr(x, y, sdata, g_width, g_server_bpp);
      for (i = 0; i < cy; i++)
      {
        copy_memb(d, s, cx * g_server_Bpp);
        s = s + g_width * g_server_Bpp;
        d = d + g_width * g_server_Bpp;
      }
    }
  }
  else if (has_screen_copy)
  {
    vga_accel(ACCEL_SCREENCOPY, srcx, srcy, x, y, cx, cy);
  }
  else
  {
    // slow
    temp = (uint8*)xmalloc(cx * cy * g_server_Bpp);
    for (i = 0; i < cy; i++)
      vga_getscansegment(get_ptr(0, i, temp, cx, g_server_bpp), srcx, srcy + i, cx * g_server_Bpp);
    for (i = 0; i < cy; i++)
      vga_drawscansegment(get_ptr(0, i, temp, cx, g_server_bpp), x, y + i, cx * g_server_Bpp);
    xfree(temp);
  }
}
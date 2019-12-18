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
 int g_draw_mouse ; 
 int g_height ; 
 int g_server_Bpp ; 
 int /*<<< orphan*/  g_server_bpp ; 
 int g_width ; 
 int /*<<< orphan*/ * get_ptr (int,int,int /*<<< orphan*/ ,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mouse_under ; 
 int /*<<< orphan*/  vga_drawscansegment (int /*<<< orphan*/ *,int,int,int) ; 

void draw_cursor_under(int ox, int oy)
{
  int i;
  int j;
  int k;
  uint8* ptr;
  int len;

  if (ox < 0)
    k = -ox;
  else
    k = 0;
  j = g_width - ox;
  if (j > 32)
    j = 32;
  if (j > 0)
  {
    for (i = 0; i < 32; i++)
    {
      ptr = get_ptr(k, i, mouse_under, 32, g_server_bpp);
      len = (j - k) * g_server_Bpp;
      if (ox + k >= 0 && oy + i >= 0 && ox + k < g_width && oy + i < g_height)
        vga_drawscansegment(ptr, ox + k, oy + i, len);
    }
  }
  g_draw_mouse = 1;
}
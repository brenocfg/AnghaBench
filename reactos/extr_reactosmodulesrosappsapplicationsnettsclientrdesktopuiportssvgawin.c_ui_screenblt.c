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

/* Variables and functions */
 int /*<<< orphan*/  False ; 
 int /*<<< orphan*/  accel_screen_copy (int,int,int,int,int,int) ; 
 int /*<<< orphan*/  cache_rect (int,int,int,int,int /*<<< orphan*/ ) ; 
 scalar_t__ contains_mouse (int,int,int,int) ; 
 int /*<<< orphan*/  draw_cache_rects () ; 
 int /*<<< orphan*/  draw_cursor_under (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int g_server_Bpp ; 
 int /*<<< orphan*/  g_server_bpp ; 
 int /*<<< orphan*/  get_pixel (int,int) ; 
 int /*<<< orphan*/  get_pixel2 (int,int,int*,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mousex ; 
 int /*<<< orphan*/  mousey ; 
 int /*<<< orphan*/  set_pixel (int,int,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  set_pixel2 (int,int,int /*<<< orphan*/ ,int*,int,int /*<<< orphan*/ ) ; 
 scalar_t__ warp_coords (int*,int*,int*,int*,int*,int*) ; 
 int /*<<< orphan*/  xfree (int*) ; 
 scalar_t__ xmalloc (int) ; 

void ui_screenblt(uint8 opcode, int x, int y, int cx, int cy,
                  int srcx, int srcy)
{
  int i;
  int j;
  uint8* temp;

  if (x == srcx && y == srcy)
    return;
  if (warp_coords(&x, &y, &cx, &cy, &srcx, &srcy))
  {
    if (contains_mouse(x, y, cx, cy) || contains_mouse(srcx, srcy, cx, cy))
      draw_cursor_under(mousex, mousey);
    if (opcode == 0xc) /* copy */
      accel_screen_copy(x, y, cx, cy, srcx, srcy);
    else
    {
      temp = (uint8*)xmalloc(cx * cy * g_server_Bpp);
      for (i = 0; i < cy; i++)
        for (j = 0; j < cx; j++)
          set_pixel2(j, i, get_pixel(srcx + j, srcy + i), temp, cx, g_server_bpp);
      for (i = 0; i < cy; i++)
        for (j = 0; j < cx; j++)
          set_pixel(x + j, y + i, get_pixel2(j, i, temp, cx, g_server_bpp), opcode);
      xfree(temp);
    }
    cache_rect(x, y, cx, cy, False);
    draw_cache_rects(); // draw them all so screen is not jumpy
  }
}
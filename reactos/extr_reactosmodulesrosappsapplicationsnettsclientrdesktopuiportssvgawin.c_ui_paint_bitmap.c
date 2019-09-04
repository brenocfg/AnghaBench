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
 int /*<<< orphan*/  False ; 
 int /*<<< orphan*/  accel_draw_box (int,int,int,int,int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  cache_rect (int,int,int,int,int /*<<< orphan*/ ) ; 
 scalar_t__ contains_mouse (int,int,int,int) ; 
 int /*<<< orphan*/  draw_cursor_under (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int g_server_Bpp ; 
 int /*<<< orphan*/  mousex ; 
 int /*<<< orphan*/  mousey ; 
 scalar_t__ warp_coords (int*,int*,int*,int*,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 

void ui_paint_bitmap(int x, int y, int cx, int cy,
                     int width, int height, uint8* data)
{
  if (warp_coords(&x, &y, &cx, &cy, NULL, NULL))
  {
    if (contains_mouse(x, y, cx, cy))
      draw_cursor_under(mousex, mousey);
    accel_draw_box(x, y, cx, cy, data, width * g_server_Bpp);
    cache_rect(x, y, cx, cy, False);
  }
}
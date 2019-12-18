#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
typedef  int uint8 ;
struct TYPE_2__ {int width; int /*<<< orphan*/  data; } ;
typedef  TYPE_1__ bitmap ;
typedef  scalar_t__ HBITMAP ;

/* Variables and functions */
 int /*<<< orphan*/  False ; 
 int /*<<< orphan*/  accel_draw_box (int,int,int,int,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  cache_rect (int,int,int,int,int /*<<< orphan*/ ) ; 
 scalar_t__ contains_mouse (int,int,int,int) ; 
 int /*<<< orphan*/  draw_cursor_under (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int g_server_Bpp ; 
 int /*<<< orphan*/  g_server_bpp ; 
 int get_pixel2 (int,int,int /*<<< orphan*/ ,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  get_ptr (int,int,int /*<<< orphan*/ ,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mousex ; 
 int /*<<< orphan*/  mousey ; 
 int /*<<< orphan*/  set_pixel (int,int,int,int) ; 
 scalar_t__ warp_coords (int*,int*,int*,int*,int*,int*) ; 

void ui_memblt(uint8 opcode, int x, int y, int cx, int cy,
               HBITMAP src, int srcx, int srcy)
{
  bitmap* b;
  int i;
  int j;
  int pixel;

  if (warp_coords(&x, &y, &cx, &cy, &srcx, &srcy))
  {
    if (contains_mouse(x, y, cx, cy))
      draw_cursor_under(mousex, mousey);
    b = (bitmap*)src;
    if (opcode == 0xc)
      accel_draw_box(x, y, cx, cy, get_ptr(srcx, srcy, b->data, b->width, g_server_bpp),
                     b->width * g_server_Bpp);
    else
    {
      for (i = 0; i < cy; i++)
      {
        for (j = 0; j < cx; j++)
        {
          pixel = get_pixel2(srcx + j, srcy + i, b->data, b->width, g_server_bpp);
          set_pixel(x + j, y + i, pixel, opcode);
        }
      }
    }
    cache_rect(x, y, cx, cy, False);
  }
}
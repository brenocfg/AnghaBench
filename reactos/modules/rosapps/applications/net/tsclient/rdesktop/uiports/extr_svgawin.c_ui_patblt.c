#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  uint8 ;
struct TYPE_3__ {int style; int /*<<< orphan*/  yorigin; int /*<<< orphan*/  xorigin; int /*<<< orphan*/ * pattern; } ;
typedef  TYPE_1__ BRUSH ;

/* Variables and functions */
 int /*<<< orphan*/  False ; 
 int /*<<< orphan*/  cache_rect (int,int,int,int,int /*<<< orphan*/ ) ; 
 scalar_t__ contains_mouse (int,int,int,int) ; 
 int /*<<< orphan*/  draw_cursor_under (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  fill_rect (int,int,int,int,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  is_pixel_on (int /*<<< orphan*/ *,int,int,int,int) ; 
 int /*<<< orphan*/  mousex ; 
 int /*<<< orphan*/  mousey ; 
 int /*<<< orphan*/  set_pixel (int,int,int,int /*<<< orphan*/ ) ; 
 scalar_t__ warp_coords (int*,int*,int*,int*,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 

void ui_patblt(uint8 opcode, int x, int y, int cx, int cy,
               BRUSH * brush, int bgcolour, int fgcolour)
{
  int i;
  int j;
  uint8 ipattern[8];

  if (warp_coords(&x, &y, &cx, &cy, NULL, NULL))
  {
    if (contains_mouse(x, y, cx, cy))
      draw_cursor_under(mousex, mousey);
    switch (brush->style)
    {
      case 0:
        fill_rect(x, y, cx, cy, fgcolour, opcode);
        break;
      case 3:
        for (i = 0; i < 8; i++)
          ipattern[i] = ~brush->pattern[7 - i];
        for (i = 0; i < cy; i++)
          for (j = 0; j < cx; j++)
            if (is_pixel_on(ipattern, (x + j + brush->xorigin) % 8,
                              (y + i + brush->yorigin) % 8, 8, 1))
              set_pixel(x + j, y + i, fgcolour, opcode);
            else
              set_pixel(x + j, y + i, bgcolour, opcode);
        break;
    }
    cache_rect(x, y, cx, cy, False);
  }
}
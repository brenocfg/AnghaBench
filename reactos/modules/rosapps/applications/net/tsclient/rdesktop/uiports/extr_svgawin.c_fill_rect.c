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

/* Variables and functions */
 int /*<<< orphan*/  accel_fill_rect (int,int,int,int,int) ; 
 int /*<<< orphan*/  set_pixel (int,int,int,int) ; 
 scalar_t__ warp_coords (int*,int*,int*,int*,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 

void fill_rect(int x, int y, int cx, int cy, int colour, int opcode)
{
  int i;
  int j;

  if (warp_coords(&x, &y, &cx, &cy, NULL, NULL))
  {
    if (opcode == 0xc)
      accel_fill_rect(x, y, cx, cy, colour);
    else if (opcode == 0xf)
      accel_fill_rect(x, y, cx, cy, -1);
    else if (opcode == 0x0)
      accel_fill_rect(x, y, cx, cy, 0);
    else
    {
      for (i = 0; i < cy; i++)
        for (j = 0; j < cx; j++)
          set_pixel(x + j, y + i, colour, opcode);
    }
  }
}
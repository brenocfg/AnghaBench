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
struct TYPE_2__ {int x; int y; int width; int height; } ;

/* Variables and functions */
 TYPE_1__ g_clip ; 

__attribute__((used)) static int warp_coords(int * x, int * y, int * cx, int * cy,
                       int * srcx, int * srcy)
{
  int dx;
  int dy;

  if (g_clip.x > *x)
  {
    dx = g_clip.x - *x;
  }
  else
  {
    dx = 0;
  }
  if (g_clip.y > *y)
  {
    dy = g_clip.y - *y;
  }
  else
  {
    dy = 0;
  }
  if (*x + *cx > g_clip.x + g_clip.width)
  {
    *cx = (*cx - ((*x + *cx) - (g_clip.x + g_clip.width)));
  }
  if (*y + *cy > g_clip.y + g_clip.height)
  {
    *cy = (*cy - ((*y + *cy) - (g_clip.y + g_clip.height)));
  }
  *cx = *cx - dx;
  *cy = *cy - dy;
  if (*cx <= 0)
  {
    return 0;
  }
  if (*cy <= 0)
  {
    return 0;
  }
  *x = *x + dx;
  *y = *y + dy;
  if (srcx != 0)
  {
    *srcx = *srcx + dx;
  }
  if (srcy != 0)
  {
    *srcy = *srcy + dy;
  }
  return 1;
}
#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  uint8 ;
struct TYPE_4__ {int cy; int cx; struct TYPE_4__* next; scalar_t__ y; int /*<<< orphan*/  x; } ;
typedef  TYPE_1__ myrect ;

/* Variables and functions */
 int g_server_Bpp ; 
 int /*<<< orphan*/  g_server_bpp ; 
 int g_width ; 
 int /*<<< orphan*/ * get_ptr (int /*<<< orphan*/ ,scalar_t__,int /*<<< orphan*/ ,int,int /*<<< orphan*/ ) ; 
 TYPE_1__* head_rect ; 
 int /*<<< orphan*/  sdata ; 
 int /*<<< orphan*/  vga_drawscansegment (int /*<<< orphan*/ *,int /*<<< orphan*/ ,scalar_t__,int) ; 
 int /*<<< orphan*/  xfree (TYPE_1__*) ; 

void draw_cache_rects(void)
{
  int i;
  myrect* rect;
  myrect* rect1;
  uint8* p;

  // draw all the rects
  rect = head_rect;
  while (rect != 0)
  {
    p = get_ptr(rect->x, rect->y, sdata, g_width, g_server_bpp);
    for (i = 0; i < rect->cy; i++)
    {
      vga_drawscansegment(p, rect->x, rect->y + i, rect->cx * g_server_Bpp);
      p = p + g_width * g_server_Bpp;
    }
    rect1 = rect;
    rect = rect->next;
    xfree(rect1);
  }
  head_rect = 0;
}
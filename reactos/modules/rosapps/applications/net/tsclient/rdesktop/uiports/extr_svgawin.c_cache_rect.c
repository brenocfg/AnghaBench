#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
struct TYPE_6__ {int x; int y; int cx; int cy; struct TYPE_6__* prev; struct TYPE_6__* next; } ;
typedef  TYPE_1__ myrect ;

/* Variables and functions */
 int /*<<< orphan*/  draw_cursor () ; 
 TYPE_1__* head_rect ; 
 scalar_t__ is_contained_by (TYPE_1__*,TYPE_1__*) ; 
 scalar_t__ sdata ; 
 int /*<<< orphan*/  warp_coords (int*,int*,int*,int*,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  xfree (TYPE_1__*) ; 
 scalar_t__ xmalloc (int) ; 

void cache_rect(int x, int y, int cx, int cy, int do_warp)
{
  myrect* rect;
  myrect* walk_rect;

  if (sdata == 0)
  {
    draw_cursor();
    return;
  }
  if (do_warp)
    if (!warp_coords(&x, &y, &cx, &cy, NULL, NULL))
      return;
  rect = (myrect*)xmalloc(sizeof(myrect));
  rect->x = x;
  rect->y = y;
  rect->cx = cx;
  rect->cy = cy;
  rect->next = 0;
  rect->prev = 0;
  if (head_rect == 0)
    head_rect = rect;
  else
  {
    walk_rect = 0;
    do
    {
      if (walk_rect == 0)
        walk_rect = head_rect;
      else
        walk_rect = walk_rect->next;
      if (is_contained_by(rect, walk_rect))
      {
        xfree(rect);
        return;
      }
    }
    while (walk_rect->next != 0);
    walk_rect->next = rect;
    rect->prev = walk_rect;
  }
}
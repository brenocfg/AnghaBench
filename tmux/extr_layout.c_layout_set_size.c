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
typedef  void* u_int ;
struct layout_cell {void* yoff; void* xoff; void* sy; void* sx; } ;

/* Variables and functions */

void
layout_set_size(struct layout_cell *lc, u_int sx, u_int sy, u_int xoff,
    u_int yoff)
{
	lc->sx = sx;
	lc->sy = sy;

	lc->xoff = xoff;
	lc->yoff = yoff;
}
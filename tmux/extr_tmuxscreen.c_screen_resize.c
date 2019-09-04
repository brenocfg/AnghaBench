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
typedef  int u_int ;
struct screen {TYPE_1__* grid; } ;
struct TYPE_2__ {int sx; } ;

/* Variables and functions */
 int /*<<< orphan*/  screen_reflow (struct screen*,int) ; 
 int /*<<< orphan*/  screen_reset_tabs (struct screen*) ; 
 int /*<<< orphan*/  screen_resize_y (struct screen*,int) ; 
 int screen_size_x (struct screen*) ; 
 int screen_size_y (struct screen*) ; 

void
screen_resize(struct screen *s, u_int sx, u_int sy, int reflow)
{
	if (sx < 1)
		sx = 1;
	if (sy < 1)
		sy = 1;

	if (sx != screen_size_x(s)) {
		s->grid->sx = sx;
		screen_reset_tabs(s);
	} else
		reflow = 0;

	if (sy != screen_size_y(s))
		screen_resize_y(s, sy);

	if (reflow)
		screen_reflow(s, sx);
}
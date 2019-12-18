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
typedef  scalar_t__ u_int ;
struct screen_write_ctx {struct screen* s; } ;
struct screen {scalar_t__ cx; scalar_t__ cy; TYPE_1__* grid; } ;
struct grid_line {int flags; } ;
struct TYPE_2__ {scalar_t__ hsize; } ;

/* Variables and functions */
 int GRID_LINE_WRAPPED ; 
 struct grid_line* grid_get_line (TYPE_1__*,scalar_t__) ; 
 scalar_t__ screen_size_x (struct screen*) ; 
 int /*<<< orphan*/  screen_write_set_cursor (struct screen_write_ctx*,scalar_t__,scalar_t__) ; 

void
screen_write_backspace(struct screen_write_ctx *ctx)
{
	struct screen		*s = ctx->s;
	struct grid_line	*gl;
	u_int			 cx = s->cx, cy = s->cy;

	if (cx == 0) {
		if (cy == 0)
			return;
		gl = grid_get_line(s->grid, s->grid->hsize + cy - 1);
		if (gl->flags & GRID_LINE_WRAPPED) {
			cy--;
			cx = screen_size_x(s) - 1;
		}
	} else
		cx--;

	screen_write_set_cursor(ctx, cx, cy);
}
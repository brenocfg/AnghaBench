#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
typedef  scalar_t__ u_int ;
struct screen_write_ctx {struct screen* s; } ;
struct screen {scalar_t__ cy; scalar_t__ cx; struct grid* grid; } ;
struct TYPE_3__ {scalar_t__ width; } ;
struct grid_cell {TYPE_1__ data; } ;
struct grid {scalar_t__ hsize; scalar_t__ sy; } ;
struct TYPE_4__ {scalar_t__ cellsize; } ;

/* Variables and functions */
 int /*<<< orphan*/  grid_get_cell (struct grid*,scalar_t__,scalar_t__,struct grid_cell*) ; 
 TYPE_2__* grid_get_line (struct grid*,scalar_t__) ; 
 int /*<<< orphan*/  grid_view_set_cell (struct grid*,scalar_t__,scalar_t__,struct grid_cell*) ; 

void
screen_write_fast_copy(struct screen_write_ctx *ctx, struct screen *src,
    u_int px, u_int py, u_int nx, u_int ny)
{
	struct screen		*s = ctx->s;
	struct grid		*gd = src->grid;
	struct grid_cell	 gc;
	u_int		 	 xx, yy, cx, cy;

	if (nx == 0 || ny == 0)
		return;

	cy = s->cy;
	for (yy = py; yy < py + ny; yy++) {
		if (yy >= gd->hsize + gd->sy)
			break;
		cx = s->cx;
		for (xx = px; xx < px + nx; xx++) {
			if (xx >= grid_get_line(gd, yy)->cellsize)
				break;
			grid_get_cell(gd, xx, yy, &gc);
			if (xx + gc.data.width > px + nx)
				break;
			grid_view_set_cell(ctx->s->grid, cx, cy, &gc);
			cx++;
		}
		cy++;
	}
}
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
typedef  scalar_t__ u_int ;
struct screen_write_ctx {scalar_t__ bg; int /*<<< orphan*/  scrolled; struct screen* s; } ;
struct screen {scalar_t__ rlower; scalar_t__ rupper; struct grid* grid; } ;
struct grid {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  grid_view_scroll_region_up (struct grid*,scalar_t__,scalar_t__,scalar_t__) ; 
 int /*<<< orphan*/  screen_write_collect_flush (struct screen_write_ctx*,int) ; 
 int /*<<< orphan*/  screen_write_collect_scroll (struct screen_write_ctx*) ; 

void
screen_write_scrollup(struct screen_write_ctx *ctx, u_int lines, u_int bg)
{
	struct screen	*s = ctx->s;
	struct grid	*gd = s->grid;
	u_int		 i;

	if (lines == 0)
		lines = 1;
	else if (lines > s->rlower - s->rupper + 1)
		lines = s->rlower - s->rupper + 1;

	if (bg != ctx->bg) {
		screen_write_collect_flush(ctx, 1);
		ctx->bg = bg;
	}

	for (i = 0; i < lines; i++) {
		grid_view_scroll_region_up(gd, s->rupper, s->rlower, bg);
		screen_write_collect_scroll(ctx);
	}
	ctx->scrolled += lines;
}
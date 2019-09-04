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
struct tty_ctx {scalar_t__ num; scalar_t__ bg; } ;
struct screen_write_ctx {struct screen* s; } ;
struct screen {scalar_t__ cy; scalar_t__ rupper; scalar_t__ rlower; struct grid* grid; } ;
struct grid {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  grid_view_insert_lines (struct grid*,scalar_t__,scalar_t__,scalar_t__) ; 
 int /*<<< orphan*/  grid_view_insert_lines_region (struct grid*,scalar_t__,scalar_t__,scalar_t__,scalar_t__) ; 
 scalar_t__ screen_size_y (struct screen*) ; 
 int /*<<< orphan*/  screen_write_collect_flush (struct screen_write_ctx*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  screen_write_initctx (struct screen_write_ctx*,struct tty_ctx*) ; 
 int /*<<< orphan*/  tty_cmd_insertline ; 
 int /*<<< orphan*/  tty_write (int /*<<< orphan*/ ,struct tty_ctx*) ; 

void
screen_write_insertline(struct screen_write_ctx *ctx, u_int ny, u_int bg)
{
	struct screen	*s = ctx->s;
	struct grid	*gd = s->grid;
	struct tty_ctx	 ttyctx;

	if (ny == 0)
		ny = 1;

	if (s->cy < s->rupper || s->cy > s->rlower) {
		if (ny > screen_size_y(s) - s->cy)
			ny = screen_size_y(s) - s->cy;
		if (ny == 0)
			return;

		screen_write_initctx(ctx, &ttyctx);
		ttyctx.bg = bg;

		grid_view_insert_lines(gd, s->cy, ny, bg);

		screen_write_collect_flush(ctx, 0);
		ttyctx.num = ny;
		tty_write(tty_cmd_insertline, &ttyctx);
		return;
	}

	if (ny > s->rlower + 1 - s->cy)
		ny = s->rlower + 1 - s->cy;
	if (ny == 0)
		return;

	screen_write_initctx(ctx, &ttyctx);
	ttyctx.bg = bg;

	if (s->cy < s->rupper || s->cy > s->rlower)
		grid_view_insert_lines(gd, s->cy, ny, bg);
	else
		grid_view_insert_lines_region(gd, s->rlower, s->cy, ny, bg);

	screen_write_collect_flush(ctx, 0);
	ttyctx.num = ny;
	tty_write(tty_cmd_insertline, &ttyctx);
}
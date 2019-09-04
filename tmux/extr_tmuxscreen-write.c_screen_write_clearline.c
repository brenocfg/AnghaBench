#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  u_int ;
struct tty_ctx {int /*<<< orphan*/  bg; } ;
struct screen_write_ctx {struct screen* s; } ;
struct screen {scalar_t__ cy; TYPE_1__* grid; } ;
struct grid_line {scalar_t__ cellsize; } ;
struct TYPE_3__ {scalar_t__ hsize; } ;

/* Variables and functions */
 scalar_t__ COLOUR_DEFAULT (int /*<<< orphan*/ ) ; 
 struct grid_line* grid_get_line (TYPE_1__*,scalar_t__) ; 
 int /*<<< orphan*/  grid_view_clear (TYPE_1__*,int /*<<< orphan*/ ,scalar_t__,int /*<<< orphan*/ ,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  screen_size_x (struct screen*) ; 
 int /*<<< orphan*/  screen_write_collect_clear (struct screen_write_ctx*,scalar_t__,int) ; 
 int /*<<< orphan*/  screen_write_collect_flush (struct screen_write_ctx*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  screen_write_initctx (struct screen_write_ctx*,struct tty_ctx*) ; 
 int /*<<< orphan*/  tty_cmd_clearline ; 
 int /*<<< orphan*/  tty_write (int /*<<< orphan*/ ,struct tty_ctx*) ; 

void
screen_write_clearline(struct screen_write_ctx *ctx, u_int bg)
{
	struct screen		*s = ctx->s;
	struct grid_line	*gl;
	struct tty_ctx		 ttyctx;
	u_int			 sx = screen_size_x(s);

	gl = grid_get_line(s->grid, s->grid->hsize + s->cy);
	if (gl->cellsize == 0 && COLOUR_DEFAULT(bg))
		return;

	screen_write_initctx(ctx, &ttyctx);
	ttyctx.bg = bg;

	grid_view_clear(s->grid, 0, s->cy, sx, 1, bg);

	screen_write_collect_clear(ctx, s->cy, 1);
	screen_write_collect_flush(ctx, 0);
	tty_write(tty_cmd_clearline, &ttyctx);
}
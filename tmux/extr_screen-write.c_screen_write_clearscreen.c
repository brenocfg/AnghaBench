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
struct screen {TYPE_1__* grid; } ;
struct TYPE_3__ {int flags; } ;

/* Variables and functions */
 int GRID_HISTORY ; 
 int /*<<< orphan*/  grid_view_clear (TYPE_1__*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  grid_view_clear_history (TYPE_1__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  screen_size_x (struct screen*) ; 
 int /*<<< orphan*/  screen_size_y (struct screen*) ; 
 int /*<<< orphan*/  screen_write_collect_clear (struct screen_write_ctx*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  screen_write_initctx (struct screen_write_ctx*,struct tty_ctx*) ; 
 int /*<<< orphan*/  tty_cmd_clearscreen ; 
 int /*<<< orphan*/  tty_write (int /*<<< orphan*/ ,struct tty_ctx*) ; 

void
screen_write_clearscreen(struct screen_write_ctx *ctx, u_int bg)
{
	struct screen	*s = ctx->s;
	struct tty_ctx	 ttyctx;
	u_int		 sx = screen_size_x(s), sy = screen_size_y(s);

	screen_write_initctx(ctx, &ttyctx);
	ttyctx.bg = bg;

	/* Scroll into history if it is enabled. */
	if (s->grid->flags & GRID_HISTORY)
		grid_view_clear_history(s->grid, bg);
	else
		grid_view_clear(s->grid, 0, 0, sx, sy, bg);

	screen_write_collect_clear(ctx, 0, sy);
	tty_write(tty_cmd_clearscreen, &ttyctx);
}
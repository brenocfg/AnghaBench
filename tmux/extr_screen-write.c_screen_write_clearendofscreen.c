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
typedef  int u_int ;
struct tty_ctx {int bg; } ;
struct screen_write_ctx {struct screen* s; } ;
struct screen {scalar_t__ cx; scalar_t__ cy; struct grid* grid; } ;
struct grid {int flags; } ;

/* Variables and functions */
 int GRID_HISTORY ; 
 int /*<<< orphan*/  grid_view_clear (struct grid*,int,scalar_t__,int,int,int) ; 
 int /*<<< orphan*/  grid_view_clear_history (struct grid*,int) ; 
 int screen_size_x (struct screen*) ; 
 int screen_size_y (struct screen*) ; 
 int /*<<< orphan*/  screen_write_collect_clear (struct screen_write_ctx*,int,int) ; 
 int /*<<< orphan*/  screen_write_collect_flush (struct screen_write_ctx*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  screen_write_initctx (struct screen_write_ctx*,struct tty_ctx*) ; 
 int /*<<< orphan*/  tty_cmd_clearendofscreen ; 
 int /*<<< orphan*/  tty_write (int /*<<< orphan*/ ,struct tty_ctx*) ; 

void
screen_write_clearendofscreen(struct screen_write_ctx *ctx, u_int bg)
{
	struct screen	*s = ctx->s;
	struct grid	*gd = s->grid;
	struct tty_ctx	 ttyctx;
	u_int		 sx = screen_size_x(s), sy = screen_size_y(s);

	screen_write_initctx(ctx, &ttyctx);
	ttyctx.bg = bg;

	/* Scroll into history if it is enabled and clearing entire screen. */
	if (s->cx == 0 && s->cy == 0 && (gd->flags & GRID_HISTORY))
		grid_view_clear_history(gd, bg);
	else {
		if (s->cx <= sx - 1)
			grid_view_clear(gd, s->cx, s->cy, sx - s->cx, 1, bg);
		grid_view_clear(gd, 0, s->cy + 1, sx, sy - (s->cy + 1), bg);
	}

	screen_write_collect_clear(ctx, s->cy + 1, sy - (s->cy + 1));
	screen_write_collect_flush(ctx, 0);
	tty_write(tty_cmd_clearendofscreen, &ttyctx);
}
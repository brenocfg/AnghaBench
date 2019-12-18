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
struct screen {scalar_t__ cx; int /*<<< orphan*/  cy; int /*<<< orphan*/  grid; } ;

/* Variables and functions */
 int /*<<< orphan*/  grid_view_clear (int /*<<< orphan*/ ,int,int /*<<< orphan*/ ,scalar_t__,int,scalar_t__) ; 
 int screen_size_x (struct screen*) ; 
 int /*<<< orphan*/  screen_write_collect_flush (struct screen_write_ctx*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  screen_write_initctx (struct screen_write_ctx*,struct tty_ctx*) ; 
 int /*<<< orphan*/  tty_cmd_clearcharacter ; 
 int /*<<< orphan*/  tty_write (int /*<<< orphan*/ ,struct tty_ctx*) ; 

void
screen_write_clearcharacter(struct screen_write_ctx *ctx, u_int nx, u_int bg)
{
	struct screen	*s = ctx->s;
	struct tty_ctx	 ttyctx;

	if (nx == 0)
		nx = 1;

	if (nx > screen_size_x(s) - s->cx)
		nx = screen_size_x(s) - s->cx;
	if (nx == 0)
		return;

	if (s->cx > screen_size_x(s) - 1)
		return;

	screen_write_initctx(ctx, &ttyctx);
	ttyctx.bg = bg;

	grid_view_clear(s->grid, s->cx, s->cy, nx, 1, bg);

	screen_write_collect_flush(ctx, 0);
	ttyctx.num = nx;
	tty_write(tty_cmd_clearcharacter, &ttyctx);
}
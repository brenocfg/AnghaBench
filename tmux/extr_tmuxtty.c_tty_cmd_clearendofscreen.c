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
struct window_pane {int /*<<< orphan*/  screen; } ;
struct tty_ctx {int /*<<< orphan*/  bg; scalar_t__ ocy; scalar_t__ ocx; struct window_pane* wp; } ;
struct tty {int dummy; } ;

/* Variables and functions */
 scalar_t__ screen_size_x (int /*<<< orphan*/ ) ; 
 scalar_t__ screen_size_y (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  tty_clear_pane_area (struct tty*,struct tty_ctx const*,scalar_t__,scalar_t__,scalar_t__,scalar_t__,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  tty_clear_pane_line (struct tty*,struct tty_ctx const*,scalar_t__,scalar_t__,scalar_t__,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  tty_default_attributes (struct tty*,struct window_pane*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  tty_margin_off (struct tty*) ; 
 int /*<<< orphan*/  tty_region_pane (struct tty*,struct tty_ctx const*,int /*<<< orphan*/ ,scalar_t__) ; 

void
tty_cmd_clearendofscreen(struct tty *tty, const struct tty_ctx *ctx)
{
	struct window_pane	*wp = ctx->wp;
	u_int			 px, py, nx, ny;

	tty_default_attributes(tty, wp, ctx->bg);

	tty_region_pane(tty, ctx, 0, screen_size_y(wp->screen) - 1);
	tty_margin_off(tty);

	px = 0;
	nx = screen_size_x(wp->screen);
	py = ctx->ocy + 1;
	ny = screen_size_y(wp->screen) - ctx->ocy - 1;

	tty_clear_pane_area(tty, ctx, py, ny, px, nx, ctx->bg);

	px = ctx->ocx;
	nx = screen_size_x(wp->screen) - ctx->ocx;
	py = ctx->ocy;

	tty_clear_pane_line(tty, ctx, py, px, nx, ctx->bg);
}
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
struct tty_ctx {int /*<<< orphan*/  bg; scalar_t__ ocx; int /*<<< orphan*/  ocy; struct window_pane* wp; } ;
struct tty {int dummy; } ;

/* Variables and functions */
 scalar_t__ screen_size_x (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  tty_clear_pane_line (struct tty*,struct tty_ctx const*,int /*<<< orphan*/ ,scalar_t__,scalar_t__,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  tty_default_attributes (struct tty*,struct window_pane*,int /*<<< orphan*/ ) ; 

void
tty_cmd_clearendofline(struct tty *tty, const struct tty_ctx *ctx)
{
	struct window_pane	*wp = ctx->wp;
	u_int			 nx;

	tty_default_attributes(tty, wp, ctx->bg);

	nx = screen_size_x(wp->screen) - ctx->ocx;
	tty_clear_pane_line(tty, ctx, ctx->ocy, ctx->ocx, nx, ctx->bg);
}
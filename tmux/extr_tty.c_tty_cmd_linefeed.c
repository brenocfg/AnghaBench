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
struct window_pane {int sx; int sy; } ;
struct tty_ctx {scalar_t__ ocy; scalar_t__ orlower; scalar_t__ xoff; scalar_t__ ocx; scalar_t__ yoff; int /*<<< orphan*/  orupper; int /*<<< orphan*/  bg; scalar_t__ bigger; struct window_pane* wp; } ;
struct tty {scalar_t__ rright; int /*<<< orphan*/  term; } ;

/* Variables and functions */
 int /*<<< orphan*/  TTYC_CSR ; 
 int /*<<< orphan*/  tty_cursor (struct tty*,scalar_t__,scalar_t__) ; 
 int /*<<< orphan*/  tty_cursor_pane (struct tty*,struct tty_ctx const*,scalar_t__,scalar_t__) ; 
 int /*<<< orphan*/  tty_default_attributes (struct tty*,struct window_pane*,int /*<<< orphan*/ ) ; 
 scalar_t__ tty_fake_bce (struct tty*,struct window_pane*,int) ; 
 int /*<<< orphan*/  tty_margin_pane (struct tty*,struct tty_ctx const*) ; 
 int /*<<< orphan*/  tty_pane_full_width (struct tty*,struct tty_ctx const*) ; 
 int /*<<< orphan*/  tty_putc (struct tty*,char) ; 
 int /*<<< orphan*/  tty_redraw_region (struct tty*,struct tty_ctx const*) ; 
 int /*<<< orphan*/  tty_region_pane (struct tty*,struct tty_ctx const*,int /*<<< orphan*/ ,scalar_t__) ; 
 int /*<<< orphan*/  tty_term_has (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  tty_use_margin (struct tty*) ; 

void
tty_cmd_linefeed(struct tty *tty, const struct tty_ctx *ctx)
{
	struct window_pane	*wp = ctx->wp;

	if (ctx->ocy != ctx->orlower)
		return;

	if (ctx->bigger ||
	    (!tty_pane_full_width(tty, ctx) && !tty_use_margin(tty)) ||
	    tty_fake_bce(tty, wp, 8) ||
	    !tty_term_has(tty->term, TTYC_CSR) ||
	    wp->sx == 1 ||
	    wp->sy == 1) {
		tty_redraw_region(tty, ctx);
		return;
	}

	tty_default_attributes(tty, wp, ctx->bg);

	tty_region_pane(tty, ctx, ctx->orupper, ctx->orlower);
	tty_margin_pane(tty, ctx);

	/*
	 * If we want to wrap a pane while using margins, the cursor needs to
	 * be exactly on the right of the region. If the cursor is entirely off
	 * the edge - move it back to the right. Some terminals are funny about
	 * this and insert extra spaces, so only use the right if margins are
	 * enabled.
	 */
	if (ctx->xoff + ctx->ocx > tty->rright) {
		if (!tty_use_margin(tty))
			tty_cursor(tty, 0, ctx->yoff + ctx->ocy);
		else
			tty_cursor(tty, tty->rright, ctx->yoff + ctx->ocy);
	} else
		tty_cursor_pane(tty, ctx, ctx->ocx, ctx->ocy);

	tty_putc(tty, '\n');
}
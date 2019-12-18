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
struct tty_ctx {scalar_t__ ocy; scalar_t__ orupper; int /*<<< orphan*/  ocx; int /*<<< orphan*/  orlower; int /*<<< orphan*/  bg; struct window_pane* wp; scalar_t__ bigger; } ;
struct tty {int /*<<< orphan*/  term; } ;

/* Variables and functions */
 int /*<<< orphan*/  TTYC_CSR ; 
 int /*<<< orphan*/  TTYC_RI ; 
 int /*<<< orphan*/  TTYC_RIN ; 
 int /*<<< orphan*/  tty_cursor_pane (struct tty*,struct tty_ctx const*,int /*<<< orphan*/ ,scalar_t__) ; 
 int /*<<< orphan*/  tty_default_attributes (struct tty*,struct window_pane*,int /*<<< orphan*/ ) ; 
 scalar_t__ tty_fake_bce (struct tty*,struct window_pane*,int) ; 
 int /*<<< orphan*/  tty_margin_pane (struct tty*,struct tty_ctx const*) ; 
 int /*<<< orphan*/  tty_pane_full_width (struct tty*,struct tty_ctx const*) ; 
 int /*<<< orphan*/  tty_putcode (struct tty*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  tty_putcode1 (struct tty*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  tty_redraw_region (struct tty*,struct tty_ctx const*) ; 
 int /*<<< orphan*/  tty_region_pane (struct tty*,struct tty_ctx const*,scalar_t__,int /*<<< orphan*/ ) ; 
 scalar_t__ tty_term_has (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  tty_use_margin (struct tty*) ; 

void
tty_cmd_reverseindex(struct tty *tty, const struct tty_ctx *ctx)
{
	struct window_pane	*wp = ctx->wp;

	if (ctx->ocy != ctx->orupper)
		return;

	if (ctx->bigger ||
	    (!tty_pane_full_width(tty, ctx) && !tty_use_margin(tty)) ||
	    tty_fake_bce(tty, wp, 8) ||
	    !tty_term_has(tty->term, TTYC_CSR) ||
	    (!tty_term_has(tty->term, TTYC_RI) &&
	    !tty_term_has(tty->term, TTYC_RIN)) ||
	    ctx->wp->sx == 1 ||
	    ctx->wp->sy == 1) {
		tty_redraw_region(tty, ctx);
		return;
	}

	tty_default_attributes(tty, wp, ctx->bg);

	tty_region_pane(tty, ctx, ctx->orupper, ctx->orlower);
	tty_margin_pane(tty, ctx);
	tty_cursor_pane(tty, ctx, ctx->ocx, ctx->orupper);

	if (tty_term_has(tty->term, TTYC_RI))
		tty_putcode(tty, TTYC_RI);
	else
		tty_putcode1(tty, TTYC_RIN, 1);
}
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
struct window_pane {int sx; int sy; } ;
struct tty_ctx {int num; int /*<<< orphan*/  orlower; int /*<<< orphan*/  orupper; int /*<<< orphan*/  bg; scalar_t__ bigger; struct window_pane* wp; } ;
struct tty {int /*<<< orphan*/  cy; int /*<<< orphan*/  rlower; int /*<<< orphan*/  rright; int /*<<< orphan*/  term; } ;

/* Variables and functions */
 int /*<<< orphan*/  TTYC_CSR ; 
 int /*<<< orphan*/  TTYC_INDN ; 
 int /*<<< orphan*/  tty_cursor (struct tty*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  tty_default_attributes (struct tty*,struct window_pane*,int /*<<< orphan*/ ) ; 
 scalar_t__ tty_fake_bce (struct tty*,struct window_pane*,int) ; 
 int /*<<< orphan*/  tty_margin_pane (struct tty*,struct tty_ctx const*) ; 
 int /*<<< orphan*/  tty_pane_full_width (struct tty*,struct tty_ctx const*) ; 
 int /*<<< orphan*/  tty_putc (struct tty*,char) ; 
 int /*<<< orphan*/  tty_putcode1 (struct tty*,int /*<<< orphan*/ ,scalar_t__) ; 
 int /*<<< orphan*/  tty_redraw_region (struct tty*,struct tty_ctx const*) ; 
 int /*<<< orphan*/  tty_region_pane (struct tty*,struct tty_ctx const*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  tty_term_has (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  tty_use_margin (struct tty*) ; 

void
tty_cmd_scrollup(struct tty *tty, const struct tty_ctx *ctx)
{
	struct window_pane	*wp = ctx->wp;
	u_int			 i;

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

	if (ctx->num == 1 || !tty_term_has(tty->term, TTYC_INDN)) {
		if (!tty_use_margin(tty))
			tty_cursor(tty, 0, tty->rlower);
		else
			tty_cursor(tty, tty->rright, tty->rlower);
		for (i = 0; i < ctx->num; i++)
			tty_putc(tty, '\n');
	} else {
		tty_cursor(tty, 0, tty->cy);
		tty_putcode1(tty, TTYC_INDN, ctx->num);
	}
}
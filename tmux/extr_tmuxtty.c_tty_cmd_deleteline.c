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
struct tty_ctx {int /*<<< orphan*/  num; int /*<<< orphan*/  ocy; int /*<<< orphan*/  ocx; int /*<<< orphan*/  orlower; int /*<<< orphan*/  orupper; int /*<<< orphan*/  bg; TYPE_1__* wp; scalar_t__ bigger; } ;
struct tty {int /*<<< orphan*/  cy; int /*<<< orphan*/  cx; int /*<<< orphan*/  term; } ;
struct TYPE_3__ {int sx; int sy; } ;

/* Variables and functions */
 int /*<<< orphan*/  TTYC_CSR ; 
 int /*<<< orphan*/  TTYC_DL ; 
 int /*<<< orphan*/  TTYC_DL1 ; 
 int /*<<< orphan*/  UINT_MAX ; 
 int /*<<< orphan*/  tty_cursor_pane (struct tty*,struct tty_ctx const*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  tty_default_attributes (struct tty*,TYPE_1__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  tty_emulate_repeat (struct tty*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ tty_fake_bce (struct tty*,TYPE_1__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  tty_margin_off (struct tty*) ; 
 int /*<<< orphan*/  tty_pane_full_width (struct tty*,struct tty_ctx const*) ; 
 int /*<<< orphan*/  tty_redraw_region (struct tty*,struct tty_ctx const*) ; 
 int /*<<< orphan*/  tty_region_pane (struct tty*,struct tty_ctx const*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  tty_term_has (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

void
tty_cmd_deleteline(struct tty *tty, const struct tty_ctx *ctx)
{
	if (ctx->bigger ||
	    !tty_pane_full_width(tty, ctx) ||
	    tty_fake_bce(tty, ctx->wp, ctx->bg) ||
	    !tty_term_has(tty->term, TTYC_CSR) ||
	    !tty_term_has(tty->term, TTYC_DL1) ||
	    ctx->wp->sx == 1 ||
	    ctx->wp->sy == 1) {
		tty_redraw_region(tty, ctx);
		return;
	}

	tty_default_attributes(tty, ctx->wp, ctx->bg);

	tty_region_pane(tty, ctx, ctx->orupper, ctx->orlower);
	tty_margin_off(tty);
	tty_cursor_pane(tty, ctx, ctx->ocx, ctx->ocy);

	tty_emulate_repeat(tty, TTYC_DL, TTYC_DL1, ctx->num);
	tty->cx = tty->cy = UINT_MAX;
}
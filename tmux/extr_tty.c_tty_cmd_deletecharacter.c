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
struct window_pane {int dummy; } ;
struct tty_ctx {int /*<<< orphan*/  num; int /*<<< orphan*/  ocy; int /*<<< orphan*/  ocx; int /*<<< orphan*/  bg; scalar_t__ bigger; struct window_pane* wp; } ;
struct tty {int /*<<< orphan*/  term; } ;

/* Variables and functions */
 int /*<<< orphan*/  TTYC_DCH ; 
 int /*<<< orphan*/  TTYC_DCH1 ; 
 int /*<<< orphan*/  tty_cursor_pane (struct tty*,struct tty_ctx const*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  tty_default_attributes (struct tty*,struct window_pane*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  tty_draw_pane (struct tty*,struct tty_ctx const*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  tty_emulate_repeat (struct tty*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ tty_fake_bce (struct tty*,struct window_pane*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  tty_pane_full_width (struct tty*,struct tty_ctx const*) ; 
 int /*<<< orphan*/  tty_term_has (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

void
tty_cmd_deletecharacter(struct tty *tty, const struct tty_ctx *ctx)
{
	struct window_pane	*wp = ctx->wp;

	if (ctx->bigger ||
	    !tty_pane_full_width(tty, ctx) ||
	    tty_fake_bce(tty, wp, ctx->bg) ||
	    (!tty_term_has(tty->term, TTYC_DCH) &&
	    !tty_term_has(tty->term, TTYC_DCH1))) {
		tty_draw_pane(tty, ctx, ctx->ocy);
		return;
	}

	tty_default_attributes(tty, wp, ctx->bg);

	tty_cursor_pane(tty, ctx, ctx->ocx, ctx->ocy);

	tty_emulate_repeat(tty, TTYC_DCH, TTYC_DCH1, ctx->num);
}
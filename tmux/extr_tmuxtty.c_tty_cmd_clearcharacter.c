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
struct tty_ctx {int /*<<< orphan*/  num; int /*<<< orphan*/  wp; int /*<<< orphan*/  ocy; int /*<<< orphan*/  ocx; int /*<<< orphan*/  bg; scalar_t__ bigger; } ;
struct tty {int /*<<< orphan*/  term; } ;

/* Variables and functions */
 int /*<<< orphan*/  TTYC_ECH ; 
 int /*<<< orphan*/  tty_cursor_pane (struct tty*,struct tty_ctx const*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  tty_default_attributes (struct tty*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  tty_draw_pane (struct tty*,struct tty_ctx const*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  tty_fake_bce (struct tty*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  tty_putcode1 (struct tty*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  tty_repeat_space (struct tty*,int /*<<< orphan*/ ) ; 
 scalar_t__ tty_term_has (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

void
tty_cmd_clearcharacter(struct tty *tty, const struct tty_ctx *ctx)
{
	if (ctx->bigger) {
		tty_draw_pane(tty, ctx, ctx->ocy);
		return;
	}

	tty_default_attributes(tty, ctx->wp, ctx->bg);

	tty_cursor_pane(tty, ctx, ctx->ocx, ctx->ocy);

	if (tty_term_has(tty->term, TTYC_ECH) &&
	    !tty_fake_bce(tty, ctx->wp, 8))
		tty_putcode1(tty, TTYC_ECH, ctx->num);
	else
		tty_repeat_space(tty, ctx->num);
}
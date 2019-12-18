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
struct tty_ctx {int /*<<< orphan*/  bg; scalar_t__ ocx; int /*<<< orphan*/  ocy; struct window_pane* wp; } ;
struct tty {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  tty_clear_pane_line (struct tty*,struct tty_ctx const*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,scalar_t__,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  tty_default_attributes (struct tty*,struct window_pane*,int /*<<< orphan*/ ) ; 

void
tty_cmd_clearstartofline(struct tty *tty, const struct tty_ctx *ctx)
{
	struct window_pane	*wp = ctx->wp;

	tty_default_attributes(tty, wp, ctx->bg);

	tty_clear_pane_line(tty, ctx, ctx->ocy, 0, ctx->ocx + 1, ctx->bg);
}
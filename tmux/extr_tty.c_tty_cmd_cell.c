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
struct tty_ctx {int ocx; scalar_t__ ocy; int xoff; int ox; scalar_t__ orlower; int /*<<< orphan*/  wp; int /*<<< orphan*/  cell; int /*<<< orphan*/  orupper; } ;
struct tty {int sx; } ;

/* Variables and functions */
 int /*<<< orphan*/  tty_cell (struct tty*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  tty_cursor_pane_unless_wrap (struct tty*,struct tty_ctx const*,int,scalar_t__) ; 
 int /*<<< orphan*/  tty_is_visible (struct tty*,struct tty_ctx const*,int,scalar_t__,int,int) ; 
 int /*<<< orphan*/  tty_margin_off (struct tty*) ; 
 scalar_t__ tty_pane_full_width (struct tty*,struct tty_ctx const*) ; 
 int /*<<< orphan*/  tty_region_pane (struct tty*,struct tty_ctx const*,int /*<<< orphan*/ ,scalar_t__) ; 

void
tty_cmd_cell(struct tty *tty, const struct tty_ctx *ctx)
{
	if (!tty_is_visible(tty, ctx, ctx->ocx, ctx->ocy, 1, 1))
		return;

	if (ctx->xoff + ctx->ocx - ctx->ox > tty->sx - 1 &&
	    ctx->ocy == ctx->orlower &&
	    tty_pane_full_width(tty, ctx))
		tty_region_pane(tty, ctx, ctx->orupper, ctx->orlower);

	tty_margin_off(tty);
	tty_cursor_pane_unless_wrap(tty, ctx, ctx->ocx, ctx->ocy);

	tty_cell(tty, ctx->cell, ctx->wp);
}
#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct window_pane {int /*<<< orphan*/  flags; } ;
struct tty_ctx {scalar_t__ ocx; scalar_t__ ocy; scalar_t__ num; scalar_t__ xoff; scalar_t__ ox; scalar_t__ sx; scalar_t__ yoff; int /*<<< orphan*/  ptr; struct window_pane* wp; int /*<<< orphan*/  cell; int /*<<< orphan*/  wrapped; scalar_t__ bigger; } ;
struct tty {scalar_t__ cy; scalar_t__ cx; scalar_t__ sx; scalar_t__ rlower; TYPE_1__* term; } ;
struct TYPE_2__ {int flags; } ;

/* Variables and functions */
 int /*<<< orphan*/  PANE_REDRAW ; 
 int TERM_EARLYWRAP ; 
 int /*<<< orphan*/  tty_attributes (struct tty*,int /*<<< orphan*/ ,struct window_pane*) ; 
 int /*<<< orphan*/  tty_cursor_pane_unless_wrap (struct tty*,struct tty_ctx const*,scalar_t__,scalar_t__) ; 
 int /*<<< orphan*/  tty_draw_pane (struct tty*,struct tty_ctx const*,scalar_t__) ; 
 int /*<<< orphan*/  tty_is_visible (struct tty*,struct tty_ctx const*,scalar_t__,scalar_t__,scalar_t__,int) ; 
 int /*<<< orphan*/  tty_margin_off (struct tty*) ; 
 int /*<<< orphan*/  tty_pane_full_width (struct tty*,struct tty_ctx const*) ; 
 int /*<<< orphan*/  tty_putn (struct tty*,int /*<<< orphan*/ ,scalar_t__,scalar_t__) ; 

void
tty_cmd_cells(struct tty *tty, const struct tty_ctx *ctx)
{
	struct window_pane	*wp = ctx->wp;

	if (!tty_is_visible(tty, ctx, ctx->ocx, ctx->ocy, ctx->num, 1))
		return;

	if (ctx->bigger &&
	    (ctx->xoff + ctx->ocx < ctx->ox ||
	    ctx->xoff + ctx->ocx + ctx->num > ctx->ox + ctx->sx)) {
		if (!ctx->wrapped ||
		    !tty_pane_full_width(tty, ctx) ||
		    (tty->term->flags & TERM_EARLYWRAP) ||
		    ctx->xoff + ctx->ocx != 0 ||
		    ctx->yoff + ctx->ocy != tty->cy + 1 ||
		    tty->cx < tty->sx ||
		    tty->cy == tty->rlower)
			tty_draw_pane(tty, ctx, ctx->ocy);
		else
			wp->flags |= PANE_REDRAW;
		return;
	}

	tty_margin_off(tty);
	tty_cursor_pane_unless_wrap(tty, ctx, ctx->ocx, ctx->ocy);

	tty_attributes(tty, ctx->cell, ctx->wp);
	tty_putn(tty, ctx->ptr, ctx->num, ctx->num);
}
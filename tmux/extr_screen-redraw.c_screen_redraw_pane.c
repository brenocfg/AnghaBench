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
struct screen_redraw_ctx {int dummy; } ;
struct client {int /*<<< orphan*/  tty; int /*<<< orphan*/ * overlay_draw; } ;

/* Variables and functions */
 int /*<<< orphan*/  screen_redraw_draw_pane (struct screen_redraw_ctx*,struct window_pane*) ; 
 int /*<<< orphan*/  screen_redraw_set_context (struct client*,struct screen_redraw_ctx*) ; 
 int /*<<< orphan*/  tty_reset (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  window_pane_visible (struct window_pane*) ; 

void
screen_redraw_pane(struct client *c, struct window_pane *wp)
{
	struct screen_redraw_ctx	 ctx;

	if (c->overlay_draw != NULL || !window_pane_visible(wp))
		return;

	screen_redraw_set_context(c, &ctx);

	screen_redraw_draw_pane(&ctx, wp);
	tty_reset(&c->tty);
}
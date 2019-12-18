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
struct TYPE_2__ {int /*<<< orphan*/  bg; int /*<<< orphan*/  fg; } ;
struct style {TYPE_1__ gc; } ;
struct window_pane {int /*<<< orphan*/  flags; struct style cached_active_style; struct style cached_style; } ;
struct window {struct window_pane* active; } ;

/* Variables and functions */
 int /*<<< orphan*/  PANE_REDRAW ; 
 int /*<<< orphan*/  style_equal (struct style*,struct style*) ; 
 int window_pane_get_palette (struct window_pane*,int /*<<< orphan*/ ) ; 

void
window_redraw_active_switch(struct window *w, struct window_pane *wp)
{
	struct style	*sy1, *sy2;
	int		 c1, c2;

	if (wp == w->active)
		return;

	for (;;) {
		/*
		 * If the active and inactive styles or palettes are different,
		 * need to redraw the panes.
		 */
		sy1 = &wp->cached_style;
		sy2 = &wp->cached_active_style;
		if (!style_equal(sy1, sy2))
			wp->flags |= PANE_REDRAW;
		else {
			c1 = window_pane_get_palette(wp, sy1->gc.fg);
			c2 = window_pane_get_palette(wp, sy2->gc.fg);
			if (c1 != c2)
				wp->flags |= PANE_REDRAW;
			else {
				c1 = window_pane_get_palette(wp, sy1->gc.bg);
				c2 = window_pane_get_palette(wp, sy2->gc.bg);
				if (c1 != c2)
					wp->flags |= PANE_REDRAW;
			}
		}
		if (wp == w->active)
			break;
		wp = w->active;
	}
}
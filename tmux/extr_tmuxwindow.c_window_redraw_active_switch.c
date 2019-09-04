#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct TYPE_3__ {int /*<<< orphan*/  bg; int /*<<< orphan*/  fg; } ;
struct TYPE_4__ {TYPE_1__ gc; } ;
struct window_pane {int /*<<< orphan*/  flags; TYPE_2__ style; } ;
struct window {struct window_pane* active; int /*<<< orphan*/  options; } ;
struct style {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  PANE_REDRAW ; 
 struct style* options_get_style (int /*<<< orphan*/ ,char*) ; 
 scalar_t__ style_equal (struct style*,struct style*) ; 
 scalar_t__ style_is_default (TYPE_2__*) ; 
 int window_pane_get_palette (struct window_pane*,int /*<<< orphan*/ ) ; 

void
window_redraw_active_switch(struct window *w, struct window_pane *wp)
{
	struct style	*sy;

	if (wp == w->active)
		return;

	/*
	 * If window-style and window-active-style are the same, we don't need
	 * to redraw panes when switching active panes.
	 */
	sy = options_get_style(w->options, "window-active-style");
	if (style_equal(sy, options_get_style(w->options, "window-style")))
		return;

	/*
	 * If the now active or inactive pane do not have a custom style or if
	 * the palette is different, they need to be redrawn.
	 */
	if (window_pane_get_palette(w->active, w->active->style.gc.fg) != -1 ||
	    window_pane_get_palette(w->active, w->active->style.gc.bg) != -1 ||
	    style_is_default(&w->active->style))
		w->active->flags |= PANE_REDRAW;
	if (window_pane_get_palette(wp, wp->style.gc.fg) != -1 ||
	    window_pane_get_palette(wp, wp->style.gc.bg) != -1 ||
	    style_is_default(&wp->style))
		wp->flags |= PANE_REDRAW;
}
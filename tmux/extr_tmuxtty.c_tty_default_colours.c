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
struct TYPE_2__ {int fg; int bg; } ;
struct style {TYPE_1__ gc; } ;
struct window_pane {struct style style; struct window* window; } ;
struct window {int flags; struct window_pane* active; struct style style; struct style active_style; struct options* options; } ;
struct options {int dummy; } ;
struct grid_cell {int fg; int bg; } ;

/* Variables and functions */
 int WINDOW_STYLECHANGED ; 
 struct style* options_get_style (struct options*,char*) ; 
 int /*<<< orphan*/  style_copy (struct style*,struct style*) ; 
 int window_pane_get_palette (struct window_pane*,int) ; 

__attribute__((used)) static void
tty_default_colours(struct grid_cell *gc, struct window_pane *wp)
{
	struct window		*w = wp->window;
	struct options		*oo = w->options;
	struct style		*active, *pane, *window;
	int			 c;

	if (w->flags & WINDOW_STYLECHANGED) {
		w->flags &= ~WINDOW_STYLECHANGED;
		active = options_get_style(oo, "window-active-style");
		style_copy(&w->active_style, active);
		window = options_get_style(oo, "window-style");
		style_copy(&w->style, window);
	} else {
		active = &w->active_style;
		window = &w->style;
	}
	pane = &wp->style;

	if (gc->fg == 8) {
		if (pane->gc.fg != 8)
			gc->fg = pane->gc.fg;
		else if (wp == w->active && active->gc.fg != 8)
			gc->fg = active->gc.fg;
		else
			gc->fg = window->gc.fg;

		if (gc->fg != 8) {
			c = window_pane_get_palette(wp, gc->fg);
			if (c != -1)
				gc->fg = c;
		}
	}

	if (gc->bg == 8) {
		if (pane->gc.bg != 8)
			gc->bg = pane->gc.bg;
		else if (wp == w->active && active->gc.bg != 8)
			gc->bg = active->gc.bg;
		else
			gc->bg = window->gc.bg;

		if (gc->bg != 8) {
			c = window_pane_get_palette(wp, gc->bg);
			if (c != -1)
				gc->bg = c;
		}
	}
}
#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_3__ ;
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct winlink {struct window* window; } ;
struct window_pane {int flags; int /*<<< orphan*/  window; int /*<<< orphan*/  base; int /*<<< orphan*/  options; } ;
struct window {struct window_pane* active; struct window_pane* last; } ;
struct style {int dummy; } ;
struct session {int dummy; } ;
struct options_entry {int dummy; } ;
struct TYPE_5__ {struct window_pane* wp; struct session* s; struct winlink* wl; } ;
struct cmdq_item {TYPE_2__ target; TYPE_1__* shared; } ;
struct cmd_find_state {int dummy; } ;
struct cmd {struct args* args; int /*<<< orphan*/ * entry; } ;
struct client {int dummy; } ;
struct args {int dummy; } ;
typedef  enum cmd_retval { ____Placeholder_cmd_retval } cmd_retval ;
struct TYPE_6__ {struct window_pane* wp; } ;
struct TYPE_4__ {struct cmd_find_state current; } ;

/* Variables and functions */
 int CMD_RETURN_ERROR ; 
 int CMD_RETURN_NORMAL ; 
 int PANE_INPUTOFF ; 
 int PANE_REDRAW ; 
 int PANE_STYLECHANGED ; 
 struct window_pane* TAILQ_NEXT (struct window_pane*,int /*<<< orphan*/ ) ; 
 struct window_pane* TAILQ_PREV (struct window_pane*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 char* args_get (struct args*,char) ; 
 int args_has (struct args*,char) ; 
 struct client* cmd_find_client (struct cmdq_item*,int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  cmd_find_from_winlink (struct cmd_find_state*,struct winlink*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  cmd_find_from_winlink_pane (struct cmd_find_state*,struct winlink*,struct window_pane*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  cmd_last_pane_entry ; 
 int /*<<< orphan*/  cmd_select_pane_redraw (struct window*) ; 
 int /*<<< orphan*/  cmdq_error (struct cmdq_item*,char*,...) ; 
 int /*<<< orphan*/  cmdq_insert_hook (struct session*,struct cmdq_item*,struct cmd_find_state*,char*) ; 
 int /*<<< orphan*/  cmdq_print (struct cmdq_item*,char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  entry ; 
 char* format_single (struct cmdq_item*,char*,struct client*,struct session*,struct winlink*,struct window_pane*) ; 
 int /*<<< orphan*/  free (char*) ; 
 TYPE_3__ marked_pane ; 
 struct style* options_get_style (int /*<<< orphan*/ ,char*) ; 
 struct options_entry* options_set_style (int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ,char const*) ; 
 int /*<<< orphan*/  screen_set_title (int /*<<< orphan*/ *,char*) ; 
 int /*<<< orphan*/  server_clear_marked () ; 
 scalar_t__ server_is_marked (struct session*,struct winlink*,struct window_pane*) ; 
 int /*<<< orphan*/  server_redraw_window (struct window*) ; 
 int /*<<< orphan*/  server_redraw_window_borders (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  server_set_marked (struct session*,struct winlink*,struct window_pane*) ; 
 int /*<<< orphan*/  server_status_window (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  style_tostring (struct style*) ; 
 int window_count_panes (struct window*) ; 
 struct window_pane* window_pane_find_down (struct window_pane*) ; 
 struct window_pane* window_pane_find_left (struct window_pane*) ; 
 struct window_pane* window_pane_find_right (struct window_pane*) ; 
 struct window_pane* window_pane_find_up (struct window_pane*) ; 
 int /*<<< orphan*/  window_pane_visible (struct window_pane*) ; 
 int /*<<< orphan*/  window_panes ; 
 scalar_t__ window_pop_zoom (struct window*) ; 
 scalar_t__ window_push_zoom (struct window*,int) ; 
 int /*<<< orphan*/  window_redraw_active_switch (struct window*,struct window_pane*) ; 
 scalar_t__ window_set_active_pane (struct window*,struct window_pane*,int) ; 

__attribute__((used)) static enum cmd_retval
cmd_select_pane_exec(struct cmd *self, struct cmdq_item *item)
{
	struct args		*args = self->args;
	struct cmd_find_state	*current = &item->shared->current;
	struct client		*c = cmd_find_client(item, NULL, 1);
	struct winlink		*wl = item->target.wl;
	struct window		*w = wl->window;
	struct session		*s = item->target.s;
	struct window_pane	*wp = item->target.wp, *lastwp, *markedwp;
	char			*pane_title;
	const char		*style;
	struct style		*sy;
	struct options_entry	*o;

	if (self->entry == &cmd_last_pane_entry || args_has(args, 'l')) {
		lastwp = w->last;
		if (lastwp == NULL && window_count_panes(w) == 2) {
			lastwp = TAILQ_PREV(w->active, window_panes, entry);
			if (lastwp == NULL)
				lastwp = TAILQ_NEXT(w->active, entry);
		}
		if (lastwp == NULL) {
			cmdq_error(item, "no last pane");
			return (CMD_RETURN_ERROR);
		}
		if (args_has(self->args, 'e'))
			lastwp->flags &= ~PANE_INPUTOFF;
		else if (args_has(self->args, 'd'))
			lastwp->flags |= PANE_INPUTOFF;
		else {
			if (window_push_zoom(w, args_has(self->args, 'Z')))
				server_redraw_window(w);
			window_redraw_active_switch(w, lastwp);
			if (window_set_active_pane(w, lastwp, 1)) {
				cmd_find_from_winlink(current, wl, 0);
				cmd_select_pane_redraw(w);
			}
			if (window_pop_zoom(w))
				server_redraw_window(w);
		}
		return (CMD_RETURN_NORMAL);
	}

	if (args_has(args, 'm') || args_has(args, 'M')) {
		if (args_has(args, 'm') && !window_pane_visible(wp))
			return (CMD_RETURN_NORMAL);
		lastwp = marked_pane.wp;

		if (args_has(args, 'M') || server_is_marked(s, wl, wp))
			server_clear_marked();
		else
			server_set_marked(s, wl, wp);
		markedwp = marked_pane.wp;

		if (lastwp != NULL) {
			server_redraw_window_borders(lastwp->window);
			server_status_window(lastwp->window);
		}
		if (markedwp != NULL) {
			server_redraw_window_borders(markedwp->window);
			server_status_window(markedwp->window);
		}
		return (CMD_RETURN_NORMAL);
	}

	if (args_has(self->args, 'P') || args_has(self->args, 'g')) {
		if ((style = args_get(args, 'P')) != NULL) {
			o = options_set_style(wp->options, "window-style", 0,
			    style);
			if (o == NULL) {
				cmdq_error(item, "bad style: %s", style);
				return (CMD_RETURN_ERROR);
			}
			options_set_style(wp->options, "window-active-style", 0,
			    style);
			wp->flags |= (PANE_REDRAW|PANE_STYLECHANGED);
		}
		if (args_has(self->args, 'g')) {
			sy = options_get_style(wp->options, "window-style");
			cmdq_print(item, "%s", style_tostring(sy));
		}
		return (CMD_RETURN_NORMAL);
	}

	if (args_has(self->args, 'L')) {
		window_push_zoom(w, 1);
		wp = window_pane_find_left(wp);
		window_pop_zoom(w);
	} else if (args_has(self->args, 'R')) {
		window_push_zoom(w, 1);
		wp = window_pane_find_right(wp);
		window_pop_zoom(w);
	} else if (args_has(self->args, 'U')) {
		window_push_zoom(w, 1);
		wp = window_pane_find_up(wp);
		window_pop_zoom(w);
	} else if (args_has(self->args, 'D')) {
		window_push_zoom(w, 1);
		wp = window_pane_find_down(wp);
		window_pop_zoom(w);
	}
	if (wp == NULL)
		return (CMD_RETURN_NORMAL);

	if (args_has(self->args, 'e')) {
		wp->flags &= ~PANE_INPUTOFF;
		return (CMD_RETURN_NORMAL);
	}
	if (args_has(self->args, 'd')) {
		wp->flags |= PANE_INPUTOFF;
		return (CMD_RETURN_NORMAL);
	}

	if (args_has(self->args, 'T')) {
		pane_title = format_single(item, args_get(self->args, 'T'),
		    c, s, wl, wp);
		screen_set_title(&wp->base, pane_title);
		server_status_window(wp->window);
		free(pane_title);
		return (CMD_RETURN_NORMAL);
	}

	if (wp == w->active)
		return (CMD_RETURN_NORMAL);
	if (window_push_zoom(w, args_has(self->args, 'Z')))
		server_redraw_window(w);
	window_redraw_active_switch(w, wp);
	if (window_set_active_pane(w, wp, 1)) {
		cmd_find_from_winlink_pane(current, wl, wp, 0);
		cmdq_insert_hook(s, item, current, "after-select-pane");
		cmd_select_pane_redraw(w);
	}
	if (window_pop_zoom(w))
		server_redraw_window(w);

	return (CMD_RETURN_NORMAL);
}
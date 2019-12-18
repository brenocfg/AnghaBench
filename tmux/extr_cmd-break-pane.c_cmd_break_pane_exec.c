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
struct winlink {int /*<<< orphan*/  idx; struct window* window; } ;
struct window_pane {int /*<<< orphan*/  flags; int /*<<< orphan*/  options; struct window* window; } ;
struct window {int /*<<< orphan*/  options; struct client* latest; struct window_pane* active; int /*<<< orphan*/  panes; int /*<<< orphan*/  sy; int /*<<< orphan*/  sx; } ;
struct session {int /*<<< orphan*/  options; int /*<<< orphan*/  windows; } ;
struct TYPE_6__ {int idx; struct session* s; } ;
struct TYPE_5__ {struct window_pane* wp; struct session* s; struct winlink* wl; } ;
struct cmdq_item {TYPE_3__ target; TYPE_2__ source; TYPE_1__* shared; } ;
struct cmd_find_state {int dummy; } ;
struct cmd {struct args* args; } ;
struct client {int dummy; } ;
struct args {int dummy; } ;
typedef  enum cmd_retval { ____Placeholder_cmd_retval } cmd_retval ;
struct TYPE_4__ {struct cmd_find_state current; } ;

/* Variables and functions */
 char* BREAK_PANE_TEMPLATE ; 
 int CMD_RETURN_ERROR ; 
 int CMD_RETURN_NORMAL ; 
 int /*<<< orphan*/  PANE_CHANGED ; 
 int /*<<< orphan*/  PANE_STYLECHANGED ; 
 int /*<<< orphan*/  TAILQ_INSERT_HEAD (int /*<<< orphan*/ *,struct window_pane*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  TAILQ_REMOVE (int /*<<< orphan*/ *,struct window_pane*,int /*<<< orphan*/ ) ; 
 char* args_get (struct args*,float) ; 
 scalar_t__ args_has (struct args*,char) ; 
 struct client* cmd_find_client (struct cmdq_item*,int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  cmd_find_from_session (struct cmd_find_state*,struct session*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  cmdq_error (struct cmdq_item*,char*,...) ; 
 int /*<<< orphan*/  cmdq_print (struct cmdq_item*,char*,char*) ; 
 char* default_window_name (struct window*) ; 
 int /*<<< orphan*/  entry ; 
 char* format_single (struct cmdq_item*,char const*,struct client*,struct session*,struct winlink*,struct window_pane*) ; 
 int /*<<< orphan*/  free (char*) ; 
 int /*<<< orphan*/  layout_close_pane (struct window_pane*) ; 
 int /*<<< orphan*/  layout_init (struct window*,struct window_pane*) ; 
 int options_get_number (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  options_set_number (int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  options_set_parent (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  server_redraw_session (struct session*) ; 
 int /*<<< orphan*/  server_status_session_group (struct session*) ; 
 int /*<<< orphan*/  server_unzoom_window (struct window*) ; 
 struct winlink* session_attach (struct session*,struct window*,int,char**) ; 
 int /*<<< orphan*/  session_select (struct session*,int /*<<< orphan*/ ) ; 
 int window_count_panes (struct window*) ; 
 struct window* window_create (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  window_lost_pane (struct window*,struct window_pane*) ; 
 int /*<<< orphan*/  window_set_name (struct window*,char*) ; 
 int /*<<< orphan*/ * winlink_find_by_index (int /*<<< orphan*/ *,int) ; 

__attribute__((used)) static enum cmd_retval
cmd_break_pane_exec(struct cmd *self, struct cmdq_item *item)
{
	struct args		*args = self->args;
	struct cmd_find_state	*current = &item->shared->current;
	struct client		*c = cmd_find_client(item, NULL, 1);
	struct winlink		*wl = item->source.wl;
	struct session		*src_s = item->source.s;
	struct session		*dst_s = item->target.s;
	struct window_pane	*wp = item->source.wp;
	struct window		*w = wl->window;
	char			*name, *cause;
	int			 idx = item->target.idx;
	const char		*template;
	char			*cp;

	if (idx != -1 && winlink_find_by_index(&dst_s->windows, idx) != NULL) {
		cmdq_error(item, "index %d already in use", idx);
		return (CMD_RETURN_ERROR);
	}

	if (window_count_panes(w) == 1) {
		cmdq_error(item, "can't break with only one pane");
		return (CMD_RETURN_ERROR);
	}
	server_unzoom_window(w);

	TAILQ_REMOVE(&w->panes, wp, entry);
	window_lost_pane(w, wp);
	layout_close_pane(wp);

	w = wp->window = window_create(w->sx, w->sy);
	options_set_parent(wp->options, w->options);
	wp->flags |= PANE_STYLECHANGED;
	TAILQ_INSERT_HEAD(&w->panes, wp, entry);
	w->active = wp;
	w->latest = c;

	if (!args_has(args, 'n')) {
		name = default_window_name(w);
		window_set_name(w, name);
		free(name);
	} else {
		window_set_name(w, args_get(args, 'n'));
		options_set_number(w->options, "automatic-rename", 0);
	}

	layout_init(w, wp);
	wp->flags |= PANE_CHANGED;

	if (idx == -1)
		idx = -1 - options_get_number(dst_s->options, "base-index");
	wl = session_attach(dst_s, w, idx, &cause); /* can't fail */
	if (!args_has(self->args, 'd')) {
		session_select(dst_s, wl->idx);
		cmd_find_from_session(current, dst_s, 0);
	}

	server_redraw_session(src_s);
	if (src_s != dst_s)
		server_redraw_session(dst_s);
	server_status_session_group(src_s);
	if (src_s != dst_s)
		server_status_session_group(dst_s);

	if (args_has(args, 'P')) {
		if ((template = args_get(args, 'F')) == NULL)
			template = BREAK_PANE_TEMPLATE;
		cp = format_single(item, template, c, dst_s, wl, wp);
		cmdq_print(item, "%s", cp);
		free(cp);
	}
	return (CMD_RETURN_NORMAL);
}
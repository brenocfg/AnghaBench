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
struct winlink {int idx; struct window* window; } ;
struct window_pane {int sy; int sx; int /*<<< orphan*/  flags; int /*<<< orphan*/  options; struct window* window; } ;
struct window {int /*<<< orphan*/  panes; int /*<<< orphan*/  options; } ;
struct session {int dummy; } ;
struct layout_cell {int dummy; } ;
struct TYPE_6__ {struct window_pane* wp; struct winlink* wl; } ;
struct TYPE_5__ {struct window_pane* wp; struct winlink* wl; struct session* s; } ;
struct cmdq_item {TYPE_3__ source; TYPE_2__ target; TYPE_1__* shared; } ;
struct cmd_find_state {int dummy; } ;
struct cmd {int /*<<< orphan*/ * entry; struct args* args; } ;
struct args {int dummy; } ;
typedef  enum layout_type { ____Placeholder_layout_type } layout_type ;
typedef  enum cmd_retval { ____Placeholder_cmd_retval } cmd_retval ;
struct TYPE_4__ {struct cmd_find_state current; } ;

/* Variables and functions */
 int CMD_RETURN_ERROR ; 
 int CMD_RETURN_NORMAL ; 
 int INT_MAX ; 
 int LAYOUT_LEFTRIGHT ; 
 int LAYOUT_TOPBOTTOM ; 
 int /*<<< orphan*/  PANE_STYLECHANGED ; 
 int SPAWN_BEFORE ; 
 int /*<<< orphan*/  TAILQ_INSERT_AFTER (int /*<<< orphan*/ *,struct window_pane*,struct window_pane*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  TAILQ_REMOVE (int /*<<< orphan*/ *,struct window_pane*,int /*<<< orphan*/ ) ; 
 char* args_get (struct args*,char) ; 
 scalar_t__ args_has (struct args*,char) ; 
 int args_strtonum (struct args*,char,int /*<<< orphan*/ ,int,char**) ; 
 int /*<<< orphan*/  cmd_find_from_session (struct cmd_find_state*,struct session*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  cmd_join_pane_entry ; 
 int /*<<< orphan*/  cmdq_error (struct cmdq_item*,char*,...) ; 
 int /*<<< orphan*/  entry ; 
 int /*<<< orphan*/  free (char*) ; 
 int /*<<< orphan*/  layout_assign_pane (struct layout_cell*,struct window_pane*) ; 
 int /*<<< orphan*/  layout_close_pane (struct window_pane*) ; 
 struct layout_cell* layout_split_pane (struct window_pane*,int,int,int) ; 
 int /*<<< orphan*/  notify_window (char*,struct window*) ; 
 int /*<<< orphan*/  options_set_parent (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  recalculate_sizes () ; 
 int /*<<< orphan*/  server_kill_window (struct window*) ; 
 int /*<<< orphan*/  server_redraw_session (struct session*) ; 
 int /*<<< orphan*/  server_redraw_window (struct window*) ; 
 int /*<<< orphan*/  server_status_session (struct session*) ; 
 int /*<<< orphan*/  server_unzoom_window (struct window*) ; 
 int /*<<< orphan*/  session_select (struct session*,int) ; 
 size_t strlen (char const*) ; 
 int strtonum (char*,int /*<<< orphan*/ ,int,char const**) ; 
 scalar_t__ window_count_panes (struct window*) ; 
 int /*<<< orphan*/  window_lost_pane (struct window*,struct window_pane*) ; 
 int /*<<< orphan*/  window_set_active_pane (struct window*,struct window_pane*,int) ; 
 char* xstrdup (char const*) ; 

__attribute__((used)) static enum cmd_retval
cmd_join_pane_exec(struct cmd *self, struct cmdq_item *item)
{
	struct args		*args = self->args;
	struct cmd_find_state	*current = &item->shared->current;
	struct session		*dst_s;
	struct winlink		*src_wl, *dst_wl;
	struct window		*src_w, *dst_w;
	struct window_pane	*src_wp, *dst_wp;
	char			*cause, *copy;
	const char		*errstr, *p;
	size_t			 plen;
	int			 size, percentage, dst_idx, not_same_window;
	int			 flags;
	enum layout_type	 type;
	struct layout_cell	*lc;

	if (self->entry == &cmd_join_pane_entry)
		not_same_window = 1;
	else
		not_same_window = 0;

	dst_s = item->target.s;
	dst_wl = item->target.wl;
	dst_wp = item->target.wp;
	dst_w = dst_wl->window;
	dst_idx = dst_wl->idx;
	server_unzoom_window(dst_w);

	src_wl = item->source.wl;
	src_wp = item->source.wp;
	src_w = src_wl->window;
	server_unzoom_window(src_w);

	if (not_same_window && src_w == dst_w) {
		cmdq_error(item, "can't join a pane to its own window");
		return (CMD_RETURN_ERROR);
	}
	if (!not_same_window && src_wp == dst_wp) {
		cmdq_error(item, "source and target panes must be different");
		return (CMD_RETURN_ERROR);
	}

	type = LAYOUT_TOPBOTTOM;
	if (args_has(args, 'h'))
		type = LAYOUT_LEFTRIGHT;

	size = -1;
	if ((p = args_get(args, 'l')) != NULL) {
		plen = strlen(p);
		if (p[plen - 1] == '%') {
			copy = xstrdup(p);
			copy[plen - 1] = '\0';
			percentage = strtonum(copy, 0, INT_MAX, &errstr);
			free(copy);
			if (errstr != NULL) {
				cmdq_error(item, "percentage %s", errstr);
				return (CMD_RETURN_ERROR);
			}
			if (type == LAYOUT_TOPBOTTOM)
				size = (dst_wp->sy * percentage) / 100;
			else
				size = (dst_wp->sx * percentage) / 100;
		} else {
			size = args_strtonum(args, 'l', 0, INT_MAX, &cause);
			if (cause != NULL) {
				cmdq_error(item, "size %s", cause);
				free(cause);
				return (CMD_RETURN_ERROR);
			}
		}
	} else if (args_has(args, 'p')) {
		percentage = args_strtonum(args, 'p', 0, 100, &cause);
		if (cause != NULL) {
			cmdq_error(item, "percentage %s", cause);
			free(cause);
			return (CMD_RETURN_ERROR);
		}
		if (type == LAYOUT_TOPBOTTOM)
			size = (dst_wp->sy * percentage) / 100;
		else
			size = (dst_wp->sx * percentage) / 100;
	}
	if (args_has(args, 'b'))
		flags = SPAWN_BEFORE;
	else
		flags = 0;
	lc = layout_split_pane(dst_wp, type, size, flags);
	if (lc == NULL) {
		cmdq_error(item, "create pane failed: pane too small");
		return (CMD_RETURN_ERROR);
	}

	layout_close_pane(src_wp);

	window_lost_pane(src_w, src_wp);
	TAILQ_REMOVE(&src_w->panes, src_wp, entry);

	src_wp->window = dst_w;
	options_set_parent(src_wp->options, dst_w->options);
	src_wp->flags |= PANE_STYLECHANGED;
	TAILQ_INSERT_AFTER(&dst_w->panes, dst_wp, src_wp, entry);
	layout_assign_pane(lc, src_wp);

	recalculate_sizes();

	server_redraw_window(src_w);
	server_redraw_window(dst_w);

	if (!args_has(args, 'd')) {
		window_set_active_pane(dst_w, src_wp, 1);
		session_select(dst_s, dst_idx);
		cmd_find_from_session(current, dst_s, 0);
		server_redraw_session(dst_s);
	} else
		server_status_session(dst_s);

	if (window_count_panes(src_w) == 0)
		server_kill_window(src_w);
	else
		notify_window("window-layout-changed", src_w);
	notify_window("window-layout-changed", dst_w);

	return (CMD_RETURN_NORMAL);
}
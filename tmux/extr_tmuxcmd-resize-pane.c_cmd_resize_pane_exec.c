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
typedef  int u_int ;
struct winlink {struct window* window; } ;
struct window_pane {int dummy; } ;
struct window {int flags; } ;
struct session {int dummy; } ;
struct cmdq_shared {int /*<<< orphan*/  mouse; } ;
struct TYPE_3__ {struct session* s; struct winlink* wl; struct window_pane* wp; } ;
struct cmdq_item {TYPE_1__ target; struct client* client; struct cmdq_shared* shared; } ;
struct cmd {struct args* args; } ;
struct TYPE_4__ {int /*<<< orphan*/  (* mouse_drag_update ) (struct client*,int /*<<< orphan*/ *) ;} ;
struct client {TYPE_2__ tty; struct session* session; } ;
struct args {scalar_t__ argc; int /*<<< orphan*/ * argv; } ;
typedef  enum cmd_retval { ____Placeholder_cmd_retval } cmd_retval ;

/* Variables and functions */
 int CMD_RETURN_ERROR ; 
 int CMD_RETURN_NORMAL ; 
 int /*<<< orphan*/  INT_MAX ; 
 int /*<<< orphan*/  LAYOUT_LEFTRIGHT ; 
 int /*<<< orphan*/  LAYOUT_TOPBOTTOM ; 
 int /*<<< orphan*/  PANE_MINIMUM ; 
 int WINDOW_ZOOMED ; 
 scalar_t__ args_has (struct args*,char) ; 
 int args_strtonum (struct args*,char,int /*<<< orphan*/ ,int /*<<< orphan*/ ,char**) ; 
 int /*<<< orphan*/ * cmd_mouse_window (int /*<<< orphan*/ *,struct session**) ; 
 int /*<<< orphan*/  cmd_resize_pane_mouse_update (struct client*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  cmdq_error (struct cmdq_item*,char*,char const*) ; 
 int /*<<< orphan*/  free (char*) ; 
 int /*<<< orphan*/  layout_resize_pane (struct window_pane*,int /*<<< orphan*/ ,int,int) ; 
 int /*<<< orphan*/  layout_resize_pane_to (struct window_pane*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  server_redraw_window (struct window*) ; 
 int /*<<< orphan*/  server_status_window (struct window*) ; 
 int /*<<< orphan*/  server_unzoom_window (struct window*) ; 
 int strtonum (int /*<<< orphan*/ ,int,int /*<<< orphan*/ ,char const**) ; 
 int /*<<< orphan*/  window_unzoom (struct window*) ; 
 int /*<<< orphan*/  window_zoom (struct window_pane*) ; 

__attribute__((used)) static enum cmd_retval
cmd_resize_pane_exec(struct cmd *self, struct cmdq_item *item)
{
	struct args		*args = self->args;
	struct cmdq_shared	*shared = item->shared;
	struct window_pane	*wp = item->target.wp;
	struct winlink		*wl = item->target.wl;
	struct window		*w = wl->window;
	struct client		*c = item->client;
	struct session		*s = item->target.s;
	const char	       	*errstr;
	char			*cause;
	u_int			 adjust;
	int			 x, y;

	if (args_has(args, 'M')) {
		if (cmd_mouse_window(&shared->mouse, &s) == NULL)
			return (CMD_RETURN_NORMAL);
		if (c == NULL || c->session != s)
			return (CMD_RETURN_NORMAL);
		c->tty.mouse_drag_update = cmd_resize_pane_mouse_update;
		cmd_resize_pane_mouse_update(c, &shared->mouse);
		return (CMD_RETURN_NORMAL);
	}

	if (args_has(args, 'Z')) {
		if (w->flags & WINDOW_ZOOMED)
			window_unzoom(w);
		else
			window_zoom(wp);
		server_redraw_window(w);
		server_status_window(w);
		return (CMD_RETURN_NORMAL);
	}
	server_unzoom_window(w);

	if (args->argc == 0)
		adjust = 1;
	else {
		adjust = strtonum(args->argv[0], 1, INT_MAX, &errstr);
		if (errstr != NULL) {
			cmdq_error(item, "adjustment %s", errstr);
			return (CMD_RETURN_ERROR);
		}
	}

	if (args_has(args, 'x')) {
		x = args_strtonum(args, 'x', PANE_MINIMUM, INT_MAX, &cause);
		if (cause != NULL) {
			cmdq_error(item, "width %s", cause);
			free(cause);
			return (CMD_RETURN_ERROR);
		}
		layout_resize_pane_to(wp, LAYOUT_LEFTRIGHT, x);
	}
	if (args_has(args, 'y')) {
		y = args_strtonum(args, 'y', PANE_MINIMUM, INT_MAX, &cause);
		if (cause != NULL) {
			cmdq_error(item, "height %s", cause);
			free(cause);
			return (CMD_RETURN_ERROR);
		}
		layout_resize_pane_to(wp, LAYOUT_TOPBOTTOM, y);
	}

	if (args_has(args, 'L'))
		layout_resize_pane(wp, LAYOUT_LEFTRIGHT, -adjust, 1);
	else if (args_has(args, 'R'))
		layout_resize_pane(wp, LAYOUT_LEFTRIGHT, adjust, 1);
	else if (args_has(args, 'U'))
		layout_resize_pane(wp, LAYOUT_TOPBOTTOM, -adjust, 1);
	else if (args_has(args, 'D'))
		layout_resize_pane(wp, LAYOUT_TOPBOTTOM, adjust, 1);
	server_redraw_window(wl->window);

	return (CMD_RETURN_NORMAL);
}
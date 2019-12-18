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
struct winlink {int dummy; } ;
struct window_pane {int sy; int sx; int /*<<< orphan*/  window; } ;
struct spawn_context {int argc; char** argv; int idx; int flags; int /*<<< orphan*/  environ; void* cwd; int /*<<< orphan*/ * name; struct layout_cell* lc; struct window_pane* wp0; struct winlink* wl; struct session* s; struct cmdq_item* item; } ;
struct session {int dummy; } ;
struct layout_cell {int dummy; } ;
struct TYPE_4__ {struct window_pane* wp; struct winlink* wl; struct session* s; } ;
struct cmdq_item {TYPE_2__ target; TYPE_1__* shared; } ;
struct cmd_find_state {int dummy; } ;
struct cmd {struct args* args; } ;
struct client {int dummy; } ;
struct args_value {int dummy; } ;
struct args {int argc; char** argv; } ;
typedef  enum layout_type { ____Placeholder_layout_type } layout_type ;
typedef  enum cmd_retval { ____Placeholder_cmd_retval } cmd_retval ;
struct TYPE_3__ {struct cmd_find_state current; } ;

/* Variables and functions */
 int CMD_RETURN_ERROR ; 
 int CMD_RETURN_NORMAL ; 
 int CMD_RETURN_WAIT ; 
 int /*<<< orphan*/  INT_MAX ; 
 int LAYOUT_LEFTRIGHT ; 
 int LAYOUT_TOPBOTTOM ; 
 int SPAWN_BEFORE ; 
 int SPAWN_DETACHED ; 
 int SPAWN_EMPTY ; 
 int SPAWN_FULLSIZE ; 
 char* SPLIT_WINDOW_TEMPLATE ; 
 char* args_first_value (struct args*,char,struct args_value**) ; 
 void* args_get (struct args*,float) ; 
 scalar_t__ args_has (struct args*,char) ; 
 char* args_next_value (struct args_value**) ; 
 int args_strtonum (struct args*,char,int /*<<< orphan*/ ,int /*<<< orphan*/ ,char**) ; 
 struct client* cmd_find_client (struct cmdq_item*,int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  cmd_find_from_winlink_pane (struct cmd_find_state*,struct winlink*,struct window_pane*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  cmdq_error (struct cmdq_item*,char*,...) ; 
 int /*<<< orphan*/  cmdq_insert_hook (struct session*,struct cmdq_item*,struct cmd_find_state*,char*) ; 
 int /*<<< orphan*/  cmdq_print (struct cmdq_item*,char*,char*) ; 
 int /*<<< orphan*/  environ_create () ; 
 int /*<<< orphan*/  environ_free (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  environ_put (int /*<<< orphan*/ ,char const*) ; 
 char* format_single (struct cmdq_item*,char const*,struct client*,struct session*,struct winlink*,struct window_pane*) ; 
 int /*<<< orphan*/  free (char*) ; 
 int /*<<< orphan*/  layout_close_pane (struct window_pane*) ; 
 struct layout_cell* layout_split_pane (struct window_pane*,int,int,int) ; 
 int /*<<< orphan*/  memset (struct spawn_context*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  server_redraw_window (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  server_status_session (struct session*) ; 
 int /*<<< orphan*/  server_unzoom_window (int /*<<< orphan*/ ) ; 
 struct window_pane* spawn_pane (struct spawn_context*,char**) ; 
 size_t strlen (char const*) ; 
 int strtonum (char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,char const**) ; 
 scalar_t__ window_pane_start_input (struct window_pane*,struct cmdq_item*,char**) ; 
 int /*<<< orphan*/  window_remove_pane (int /*<<< orphan*/ ,struct window_pane*) ; 
 char* xstrdup (char const*) ; 

__attribute__((used)) static enum cmd_retval
cmd_split_window_exec(struct cmd *self, struct cmdq_item *item)
{
	struct args		*args = self->args;
	struct cmd_find_state	*current = &item->shared->current;
	struct spawn_context	 sc;
	struct client		*c = cmd_find_client(item, NULL, 1);
	struct session		*s = item->target.s;
	struct winlink		*wl = item->target.wl;
	struct window_pane	*wp = item->target.wp, *new_wp;
	enum layout_type	 type;
	struct layout_cell	*lc;
	struct cmd_find_state	 fs;
	int			 size, percentage, flags, input;
	const char		*template, *add, *errstr, *p;
	char			*cause, *cp, *copy;
	size_t			 plen;
	struct args_value	*value;

	if (args_has(args, 'h'))
		type = LAYOUT_LEFTRIGHT;
	else
		type = LAYOUT_TOPBOTTOM;
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
				size = (wp->sy * percentage) / 100;
			else
				size = (wp->sx * percentage) / 100;
		} else {
			size = args_strtonum(args, 'l', 0, INT_MAX, &cause);
			if (cause != NULL) {
				cmdq_error(item, "lines %s", cause);
				free(cause);
				return (CMD_RETURN_ERROR);
			}
		}
	} else if (args_has(args, 'p')) {
		percentage = args_strtonum(args, 'p', 0, INT_MAX, &cause);
		if (cause != NULL) {
			cmdq_error(item, "create pane failed: -p %s", cause);
			free(cause);
			return (CMD_RETURN_ERROR);
		}
		if (type == LAYOUT_TOPBOTTOM)
			size = (wp->sy * percentage) / 100;
		else
			size = (wp->sx * percentage) / 100;
	} else
		size = -1;

	server_unzoom_window(wp->window);
	input = (args_has(args, 'I') && args->argc == 0);

	flags = 0;
	if (args_has(args, 'b'))
		flags |= SPAWN_BEFORE;
	if (args_has(args, 'f'))
		flags |= SPAWN_FULLSIZE;
	if (input || (args->argc == 1 && *args->argv[0] == '\0'))
		flags |= SPAWN_EMPTY;

	lc = layout_split_pane(wp, type, size, flags);
	if (lc == NULL) {
		cmdq_error(item, "no space for new pane");
		return (CMD_RETURN_ERROR);
	}

	memset(&sc, 0, sizeof sc);
	sc.item = item;
	sc.s = s;
	sc.wl = wl;

	sc.wp0 = wp;
	sc.lc = lc;

	sc.name = NULL;
	sc.argc = args->argc;
	sc.argv = args->argv;
	sc.environ = environ_create();

	add = args_first_value(args, 'e', &value);
	while (add != NULL) {
		environ_put(sc.environ, add);
		add = args_next_value(&value);
	}

	sc.idx = -1;
	sc.cwd = args_get(args, 'c');

	sc.flags = flags;
	if (args_has(args, 'd'))
		sc.flags |= SPAWN_DETACHED;

	if ((new_wp = spawn_pane(&sc, &cause)) == NULL) {
		layout_close_pane(new_wp);
		cmdq_error(item, "create pane failed: %s", cause);
		free(cause);
		return (CMD_RETURN_ERROR);
	}
	if (input && window_pane_start_input(new_wp, item, &cause) != 0) {
		layout_close_pane(new_wp);
		window_remove_pane(wp->window, new_wp);
		cmdq_error(item, "%s", cause);
		free(cause);
		return (CMD_RETURN_ERROR);
	}
	if (!args_has(args, 'd'))
		cmd_find_from_winlink_pane(current, wl, new_wp, 0);
	server_redraw_window(wp->window);
	server_status_session(s);

	if (args_has(args, 'P')) {
		if ((template = args_get(args, 'F')) == NULL)
			template = SPLIT_WINDOW_TEMPLATE;
		cp = format_single(item, template, c, s, wl, new_wp);
		cmdq_print(item, "%s", cp);
		free(cp);
	}

	cmd_find_from_winlink_pane(&fs, wl, new_wp, 0);
	cmdq_insert_hook(s, item, &fs, "after-split-window");

	environ_free(sc.environ);
	if (input)
		return (CMD_RETURN_WAIT);
	return (CMD_RETURN_NORMAL);
}
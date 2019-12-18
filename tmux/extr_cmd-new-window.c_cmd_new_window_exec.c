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
struct spawn_context {int idx; int /*<<< orphan*/  environ; int /*<<< orphan*/  flags; void* cwd; int /*<<< orphan*/  argv; int /*<<< orphan*/  argc; void* name; struct client* c; struct session* s; struct cmdq_item* item; } ;
struct session {struct winlink* curw; } ;
struct TYPE_4__ {int idx; struct winlink* wl; struct session* s; } ;
struct cmdq_item {TYPE_2__ target; TYPE_1__* shared; } ;
struct cmd_find_state {int dummy; } ;
struct cmd {struct args* args; } ;
struct client {int dummy; } ;
struct args_value {int dummy; } ;
struct args {int /*<<< orphan*/  argv; int /*<<< orphan*/  argc; } ;
typedef  enum cmd_retval { ____Placeholder_cmd_retval } cmd_retval ;
struct TYPE_3__ {struct cmd_find_state current; } ;

/* Variables and functions */
 int CMD_RETURN_ERROR ; 
 int CMD_RETURN_NORMAL ; 
 char* NEW_WINDOW_TEMPLATE ; 
 int /*<<< orphan*/  SPAWN_DETACHED ; 
 int /*<<< orphan*/  SPAWN_KILL ; 
 char* args_first_value (struct args*,char,struct args_value**) ; 
 void* args_get (struct args*,float) ; 
 scalar_t__ args_has (struct args*,char) ; 
 char* args_next_value (struct args_value**) ; 
 struct client* cmd_find_client (struct cmdq_item*,int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  cmd_find_from_winlink (struct cmd_find_state*,struct winlink*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  cmdq_error (struct cmdq_item*,char*,...) ; 
 int /*<<< orphan*/  cmdq_insert_hook (struct session*,struct cmdq_item*,struct cmd_find_state*,char*) ; 
 int /*<<< orphan*/  cmdq_print (struct cmdq_item*,char*,char*) ; 
 int /*<<< orphan*/  environ_create () ; 
 int /*<<< orphan*/  environ_free (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  environ_put (int /*<<< orphan*/ ,char const*) ; 
 char* format_single (struct cmdq_item*,char const*,struct client*,struct session*,struct winlink*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  free (char*) ; 
 int /*<<< orphan*/  memset (struct spawn_context*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  server_redraw_session_group (struct session*) ; 
 int /*<<< orphan*/  server_status_session_group (struct session*) ; 
 struct winlink* spawn_window (struct spawn_context*,char**) ; 
 int winlink_shuffle_up (struct session*,struct winlink*) ; 

__attribute__((used)) static enum cmd_retval
cmd_new_window_exec(struct cmd *self, struct cmdq_item *item)
{
	struct args		*args = self->args;
	struct cmd_find_state	*current = &item->shared->current;
	struct spawn_context	 sc;
	struct client		*c = cmd_find_client(item, NULL, 1);
	struct session		*s = item->target.s;
	struct winlink		*wl = item->target.wl;
	int			 idx = item->target.idx;
	struct winlink		*new_wl;
	char			*cause = NULL, *cp;
	const char		*template, *add;
	struct cmd_find_state	 fs;
	struct args_value	*value;

	if (args_has(args, 'a') && (idx = winlink_shuffle_up(s, wl)) == -1) {
		cmdq_error(item, "couldn't get a window index");
		return (CMD_RETURN_ERROR);
	}

	memset(&sc, 0, sizeof sc);
	sc.item = item;
	sc.s = s;
	sc.c = c;

	sc.name = args_get(args, 'n');
	sc.argc = args->argc;
	sc.argv = args->argv;
	sc.environ = environ_create();

	add = args_first_value(args, 'e', &value);
	while (add != NULL) {
		environ_put(sc.environ, add);
		add = args_next_value(&value);
	}

	sc.idx = idx;
	sc.cwd = args_get(args, 'c');

	sc.flags = 0;
	if (args_has(args, 'd'))
		sc.flags |= SPAWN_DETACHED;
	if (args_has(args, 'k'))
		sc.flags |= SPAWN_KILL;

	if ((new_wl = spawn_window(&sc, &cause)) == NULL) {
		cmdq_error(item, "create window failed: %s", cause);
		free(cause);
		return (CMD_RETURN_ERROR);
	}
	if (!args_has(args, 'd') || new_wl == s->curw) {
		cmd_find_from_winlink(current, new_wl, 0);
		server_redraw_session_group(s);
	} else
		server_status_session_group(s);

	if (args_has(args, 'P')) {
		if ((template = args_get(args, 'F')) == NULL)
			template = NEW_WINDOW_TEMPLATE;
		cp = format_single(item, template, c, s, new_wl, NULL);
		cmdq_print(item, "%s", cp);
		free(cp);
	}

	cmd_find_from_winlink(&fs, new_wl, 0);
	cmdq_insert_hook(s, item, &fs, "after-new-window");

	environ_free(sc.environ);
	return (CMD_RETURN_NORMAL);
}